#include <Python.h>

static PyObject *
greet_name(PyObject *self, PyObject *args)
{    
    //printf("yaw \n");
    //Py_RETURN_NONE;
    return("yaw");
}

static PyMethodDef GreetMethods[] = {
    {"greet", greet_name, METH_VARARGS, "Greet an entity."},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initgreet(void)
{
    (void) Py_InitModule("greet", GreetMethods);
}


