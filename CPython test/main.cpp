#include <Python.h>
#include <iostream>
#include <string>

//Gets user input for a string, and returns the string transformed into a const char array pointer

int main(){
	PyObject *pModule, *pName, *pFunc, *pX, *pY, *pResult, *pArgs;
	/*std::string sName, sModule;
	const char *moduleName, *functionName;*/
	int x,y;

	Py_Initialize();
	
	std::cout<<"Write the name of the module: ";
	/*std::getline(std::cin, sModule);
	moduleName = sModule.c_str();*/
	pName = PyString_FromString("moolty");
	pModule = PyImport_Import(pName);
	//Decrease object reference
	Py_DECREF(pName);

	if (pModule != NULL){
		std::cout<<"Success opening the module!\n";
		std::cout<<"Write the name of the function: ";
		/*std::getline(std::cin, sName);
		functionName = sName.c_str();*/
		pFunc = PyObject_GetAttrString(pModule, "multi");

		if (pFunc && PyCallable_Check(pFunc)){
			std::cout<<"The function can be called!\n";
			std::cout<<"Please input 2 integers: ";
			std::cin>>x>>y;
			pArgs = PyTuple_New(2);
			pX = PyInt_FromLong(x);
			pY = PyInt_FromLong(y);
			PyTuple_SetItem(pArgs, 0, pX);
			PyTuple_SetItem(pArgs, 1, pY);
			if (!PyTuple_Check(pArgs))
				std::cout<<"ERROR WITH THE TUPLE";
			if (pX != NULL && pY != NULL){
				std::cout<<"Result should be: "<<PyInt_AsLong(PyTuple_GetItem(pArgs,0))*
					PyInt_AsLong(PyTuple_GetItem(pArgs,1))<<std::endl;
				pResult = PyObject_CallObject(pFunc, pArgs);

				//an alternative is PyObject_CallFunctionObjArgs(*function, ..., NULL) where ... are the *PyObject args

				std::cout << "Result is: "<<PyInt_AsLong(pResult);
				getchar();
			}
			else{
				std::cout<<"Failed to transform values into PyObjects";
			}
		}
		else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", "multi");
        }
	}
	else {
        PyErr_Print();
        fprintf(stderr, "Failed to load module %s\n","moolty");
    }
	
	Py_Finalize();

	getchar();
	return 0;
}