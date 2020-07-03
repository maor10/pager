#include <Python.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../sockets/socket_recording.h"
#include "../utils.h"


const char *NAME_INT = "INT";
char *my_str = "ABCDE";
PyObject *module = NULL;


static PyObject* write_to_buffer(PyObject* self, PyObject* args) {
	const char *str;
	Py_buffer buffer = {NULL, NULL};
	int len;

	if (!PyArg_ParseTuple(args, "s#w*:read", &str, &len, &buffer)) {
        return NULL;
    }

	// printf("%.*s", 5, str);

    // buffer.buf = str->getbuffer()
    memcpy(buffer.buf, str, len);

exit:
    // /* Cleanup for buffer */
    // if (buffer.obj) {
    //    PyBuffer_Release(&buffer);
    // }
    return PyLong_FromLong(len + 2);
}


static PyObject* version(PyObject* self) {
	return Py_BuildValue("s", "v 1.0");
}
//
//
//static PyObject* get_bind_call_tuple(call_node_t* node) {
//  bind_data_t* bind_data = (bind_data_t*)node->data;
//  int res = *((int*)node->result->result);
//  PyObject* call_data = Py_BuildValue("si",  bind_data->ip, bind_data->port);
//  PyObject* result_data = Py_BuildValue("ii",  node->result->errnumber, res);
//  return Py_BuildValue("iOO",  node->type, call_data, result_data);
//}
//

//static call_node_t* get_bind_call_node(PyObject* bind_call_tuple) {
//
//  if (!PyArg_ParseTuple(item, "iOO", &type, &call_data, &call_res)) {
//    return NULL;
//  }
//  PyArg_ParseTuple(bind_call_tuple, "iOO")
//}

//
//static PyObject* set_calls(PyObject* self, PyObject* args) {
//  PyObject* call;
//  int type;
//  PyObject* call_data;
//  PyObject* call_res;
//  PyObject* call_list;
//  call_node_t* call_node = malloc(sizeof(*call_node));
//  socket_recording_t* recording = initialize_recording();
//
//  if (!PyArg_ParseTuple(args, "O", &call_list)) {
//    return NULL;
//  }
//
//  while ((item = PyIter_Next(iterator))) {ֿ
//    PyArg_ParseTuple(item, "iOO", &type, &call_data, &call_res);
//    switch (type) {
//    case TYPE_BIND:
//
//      break;
//    default:
//      break;
//    }
//    add_call_node();
//    PY_DECREF(call_data);
//    Py_DECREF(call_res);
//  }
//
//  PY_DECREF(call_list);
//  return Py_BuildValue("");
//}
//
//static PyObject* get_socket_calls(PyObject* self) {
//  socket_recording_t* recording = get_recording();
//  call_node_t* node = NULL;
//  PyObject* list = PyList_New(0);
//  PyObject* call;
//  PyObject* call_data = NULL;
//  PyObject* result_data = NULL;
//  if (recording == NULL || recording->head_node == NULL) {
//    return list;
//  } else {
//    node = recording->head_node;
//  }
//
//  do {
//    switch (node->type) {
//    case TYPE_BIND:
//      LOG("Appending bind call\n");
//      PyList_Append(list, get_bind_call_tuple((bind_data_t*)node));
//      LOG("Appended bind call\n");
//      break;
//    default:
//      break;
//    }
//  } while (node = node->next);
//
//  // Py_DECREF(list);
//  return list;
//}


static PyObject* start_recording_socket_calls(PyObject* self) {
  start_recording();
  return Py_BuildValue("");
}

static PyObject* stop_recording_socket_calls(PyObject* self) {
  stop_recording();
  return Py_BuildValue("");
}

static PyObject* save_recording(PyObject* self) {
  save_call_nodes();
  return Py_BuildValue("");
}

static PyObject* load_recording(PyObject* self) {
  load_call_nodes();
  return Py_BuildValue("");
}
static PyObject* py_start_replaying(PyObject* self) {
  start_replaying();
  return Py_BuildValue("");
}

static PyMethodDef methods[]= {
	{"write_to_buffer", (PyCFunction)write_to_buffer, METH_VARARGS, "vvv"},
  {"start_recording_socket_calls", (PyCFunction)start_recording_socket_calls, METH_NOARGS, "get all calls"},
  {"stop_recording_socket_calls", (PyCFunction)stop_recording_socket_calls, METH_NOARGS, "get all calls"},
  
  {"save_recording", (PyCFunction)save_recording, METH_NOARGS, "get all calls"},
  {"load_recording", (PyCFunction)load_recording, METH_NOARGS, "get all calls"},

  {"start_replaying", (PyCFunction)py_start_replaying, METH_NOARGS, "get all calls"},
	{NULL, NULL, NULL, 0, NULL}
};

static struct PyModuleDef _cswatModule = {
	PyModuleDef_HEAD_INIT,
	"_cswat",
	"description",
	-1,
	methods
};

PyMODINIT_FUNC PyInit__cswat(void) {
	module = PyModule_Create(&_cswatModule);

  PyModule_AddStringConstant(module, "version", "1.0.0");
	// if (PyModule_AddIntConstant(m, NAME_INT, 42)) {
 //        return NULL;
 //    }

	PyModule_AddStringConstant(module, "my_str", my_str);
	return module;
}
