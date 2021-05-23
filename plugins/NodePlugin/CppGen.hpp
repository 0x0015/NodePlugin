#pragma once
#include <iostream>
#include <functional>
#include <thread>
#include <dlfcn.h>
#include "getDllPath.hpp"
#include "SimpleCppTextFileHandler/file.hpp"
//#include <libtcc.h>
//#include "getDllPath.hpp"
//#include <template>
template<typename T, typename T2> class CppGen{
public:
	bool waitForCodeGen = true;
	std::thread codeGenThread;
	bool generated = false;
	bool error = false;
	std::string* code = 0;
	//TCCState* s = 0;
	std::string functionName = "main";
	std::string compilerOutput = "";
	std::string compiler = "g++";
	void* dllHandle;
	T (*func)(T2);
	T defaultValue;
	void generateCodeFunc(){
		
		//if(fileExists("DllTemp")){
		//	deleteFile("DllTemp");
		//}
		std::string dllTempFolder = getDllPath("NodePlugin-vst.dll") + "/NodePluginDllTemp";
		createFolder(dllTempFolder);
		std::size_t codeHash = std::hash<std::string>{}(*code);
		std::string hash = std::to_string(codeHash);
		writeFile(dllTempFolder + "/" + hash + ".cpp", *code);
		
		//std::string compiler = "g++";
#if defined(_WIN32) || defined(_WIN64)
		std::string command = compiler + " -shared -g -o " + dllTempFolder + "/" + hash + ".dll -fPIC -static -static-libgcc -static-libstdc++ " + dllTempFolder + "/" + hash + ".cpp 2>&1";
#else

		std::string command = compiler + " -shared -g -o " + dllTempFolder + "/" + hash + ".so -fPIC " + dllTempFolder + "/" + hash + ".cpp 2>&1";
#endif
		//system(command.c_str());
		char buffer[128];
		FILE* pipe = popen(command.c_str(), "r");
		if(!pipe){
			error = true;
			generated = false;
			return;
		}
		compilerOutput = "";
		while(!feof(pipe)){
			if(fgets(buffer, 128, pipe) != NULL){
				compilerOutput += buffer;
			}
		}
		pclose(pipe);
		
		char *derror;
		    //double_ptr GetDouble;
		    //if(dllHandle){
		    //	dlclose(dllHandle);
		    // }
		    // open the *.so
#if defined(_WIN32) || defined(_WIN64)
		    dllHandle = dlopen ((dllTempFolder + "/"+ hash + ".dll").c_str(), RTLD_LAZY);
#else
		    dllHandle = dlopen ((dllTempFolder + "/"+ hash + ".so").c_str(), RTLD_LAZY);
#endif
		    if (!dllHandle) {
		        //fputs (dlerror(), stderr);
			compilerOutput = dlerror();
		        error = true;
			generated = false;
			return;
		    }
		    // get the function address and make it ready for use
		    func = (T(*)(T2)) dlsym(dllHandle, functionName.c_str());
		    if ((derror = dlerror()) != NULL)  {
		        //fputs(derror, stderr);
		        //exit(1);
			compilerOutput = derror;
			error = true;
			generated = false;
			return;
		    }
		    //// call the function in *.so
		    //printf ("%f\n", (*GetDouble)(2.0));
		    //// remember to free the resource
		    //dlclose(handle);
		    
		error = false;
		generated = true;
	}
	void generateCode(){
		generated = false;
		error = false;
		if(codeGenThread.joinable()){
			codeGenThread.join();
		}
		codeGenThread = std::thread([this] {generateCodeFunc(); });
		if(waitForCodeGen){
			codeGenThread.join();
		}
	}
	void generateCode(bool wait, std::string comp = "g++", std::string funcName = "main"){
		waitForCodeGen = wait;
		compiler = comp;
		functionName = funcName;
		generateCode();
	}
	T call(T2 arg){
		if(generated && (!error)){
			return(func(arg));
		}
		return(defaultValue);
	}
	CppGen(std::string* c, bool wait = true, std::string comp = "g++", std::string funcName = "main"){
		//s = tcc_new();
		code = c;
		waitForCodeGen = wait;
		compiler = comp;
		functionName = funcName;
	}
	~CppGen(){
		//tcc_delete(s);
	}
};
