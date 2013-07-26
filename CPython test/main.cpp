#include <Python.h>
#include <iostream>
#include <string>

//Gets user input for a string, and returns the string transformed into a const char array pointer
const char* cinToChar(){
	std::string input;
	std::getline(std::cin, input);
	return input.c_str();
}

int main(){
	PyObject *pModule, *pName, *pFunc, *pX, *pY, *pResult;
	const char *moduleName, *functionName;

	Py_Initialize();

	std::cout<<"Write the name of the module: ";
	moduleName = cinToChar();
	pName = PyString_FromString(moduleName);
	pModule = PyImport_Import(pName);
	//Decrease object reference
	//Py_DECREF(pName);

	if (pModule != NULL){
		std::cout<<"Success opening the module!\n";
		std::cout<<"Write the name of the function: ";
		functionName = cinToChar();
		pFunc = PyObject_GetAttrString(pModule, functionName);

		if (pFunc && PyCallable_Check(pFunc)){
			std::cout<<"The function can be called!\n";
			
		}
	}
	else {
        PyErr_Print();
        fprintf(stderr, "Failed to load");
    }

	Py_Finalize();

	getchar();
	return 1;
}