#pragma once
#include <iostream>
#include <functional>
#include <thread>
#include <libtcc.h>
//#include <template>
template<typename T, typename T2> class TccGen{
public:
	bool waitForCodeGen = true;
	std::thread codeGenThread;
	bool generated = false;
	bool error = false;
	std::string code;
	TCCState* s;
	T (*func)(T2);
	T defaultValue;
	void generateCodeFunc(){
		/* MUST BE CALLED before any compilation */
		tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
	
		if (tcc_compile_string(s, code.c_str()) == -1){
		     generated = false;
		    error = true;
		    return;
		}
		/* as a test, we add a symbol that the compiled program can use.
		   You may also open a dll with tcc_add_dll() and use symbols from that */
		//tcc_add_symbol(s, "add", add);
		/* relocate the code */
		if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0){
		    generated = false;
		    error = true;
		    return;
		}
	
		/* get entry symbol */
		func = (T(*)(T2))tcc_get_symbol(s, "main");
	    
		if (!func){
		    generated = false;
		    error = true;
		    return;
		}
		error = false;
		generated = true;
	}
	void generateCode(){
		generated = false;
		error = false;
		codeGenThread = std::thread([this] {generateCodeFunc(); });
		if(waitForCodeGen){
			codeGenThread.join();
		}
	}
	T call(T2 arg){
		if(generated && (!error)){
			return(func(arg));
		}
		return(defaultValue);
	}
	TccGen(TCCState* tccState, std::string c, bool wait = true){
		s = tccState;
		code = c;
		waitForCodeGen = wait;
	}
};
