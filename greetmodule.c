#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "MotionSensor.h"
#include <Python.h>

static PyObject *
greet_name(PyObject *self, PyObject *args)
{    
    ms_open();
    while(1)
    {
        ms_update();
        printf("yaw = %2.1f\tpitch = %2.1f\troll = %2.1f\n",ypr[YAW], ypr[PITCH],ypr[ROLL]);
    }
    Py_RETURN_NONE;
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


