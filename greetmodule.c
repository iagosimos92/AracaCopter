#include <Python.h>

static PyObject *
greet_name(PyObject *self, PyObject *args)
{    
    printf("Hello\n");

    Py_RETURN_NONE;
}

PyMODINIT_FUNC
initgreet(void)
{
    (void) Py_InitModule("greet", GreetMethods);
}
