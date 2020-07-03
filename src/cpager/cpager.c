#include <Python.h>



PyObject *module = NULL;


static PyObject* version(PyObject* self) {
    return Py_BuildValue("s", "v 1.0");
}


static PyObject* run_on_line(PyObject* self) {
    // call whatever you want here
    printf("Call whatever you want here...\n");
    fflush(stdout);
    return Py_BuildValue("");
}


static PyMethodDef methods[]= {
    {"run_on_line", (PyCFunction)run_on_line, METH_NOARGS, "runs on each line"},
    {NULL, NULL, NULL, 0, NULL}
};


static struct PyModuleDef cpagerModule = {
	PyModuleDef_HEAD_INIT,
	"cpager",
	"description",
	-1,
	methods
};


PyMODINIT_FUNC PyInit_cpager(void) {
	module = PyModule_Create(&cpagerModule);
    PyModule_AddStringConstant(module, "version", "0.0.1");
	return module;
}
