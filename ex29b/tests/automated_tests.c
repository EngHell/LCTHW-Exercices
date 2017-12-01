#include <stdio.h>
#include "../src/dbg.h"
#include <dlfcn.h>

int execute_func(const char *func_to_run, const char *data);

typedef int (*lib_function) (const char *data);

int main(int argc, char *argv[]){
		
		check(execute_func("uppercase","hola") == 0, "Couldn't exec the function");

		return 0;

		error:
		return 1;
}

int execute_func(const char *func_to_run, const char *data){
	int rc = 0;
	
	// as for some reason the dll files are being readed from the execution path of the make command
	// then those are in there..
	char *lib_file = "./build/libex29.so";
	void *lib = dlopen(lib_file, RTLD_NOW);
	check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

	lib_function func = dlsym(lib, func_to_run);
	check(func!=NULL,
		"Did not find %s function in the library %s: %s", func_to_run,
		lib_file, dlerror());

	rc = func(data);
	check(rc == 0, "Function %s, return %d for data: %s", func_to_run,
		rc, data);

	rc = dlclose(lib);
	check(rc == 0, "Failed to close %s", lib_file);
	
	return 0;	
	
	error:
	return 1;
}
