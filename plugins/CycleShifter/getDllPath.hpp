#pragma once
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include "windows.h"

std::string getDllPath(std::string dll){
	char path[_MAX_PATH+1]; 
	GetModuleFileNameA(GetModuleHandleA((dll.c_str())), path, sizeof(path)/sizeof(path[0]));
	std::string dllLocation = std::string(path);
	std::string output = "";
	std::string temp = "";
	for(int i=0;i<dllLocation.length();i++){
		if(dllLocation.substr(i, 1) == "\\"){
			output = output + temp;
			temp = "\\";
		}else{
			temp = temp + dllLocation.substr(i, 1);
		}
	}
	return(output + "\\tcc");
}
#else
std::string getDllPath(std::string path){
	return("/usr/lib/tcc");
}
#endif
