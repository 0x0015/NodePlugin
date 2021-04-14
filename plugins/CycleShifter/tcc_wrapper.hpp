#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libtcc.h>
#include <iostream>

#include <functional>


std::function<int>* compileFunction(std::string code, TCCState* s)
{
    int (*func)(int);

    if (!s) {
        fprintf(stderr, "Could not create tcc state\n");
        exit(1);
    }

    /* if tcclib.h and libtcc1.a are not installed, where can we find them */
    if (argc == 2 && !memcmp(argv[1], "lib_path=",9)){
        tcc_set_lib_path(s, argv[1]+9);
    }

    /* MUST BE CALLED before any compilation */
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

    if (tcc_compile_string(s, code.c_str()) == -1){
        return(1);
    }
    /* as a test, we add a symbol that the compiled program can use.
       You may also open a dll with tcc_add_dll() and use symbols from that */
    //tcc_add_symbol(s, "add", add);
    /* relocate the code */
    if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0){
        return(1);
    }

    /* get entry symbol */
    func = (int(*)(int))tcc_get_symbol(s, "main");
    
    if (!func){
        return(1);
    }

    /* run the code */
    func(32);

    /* delete the state */
    //tcc_get_symbol(s, "main")->(32);

    return(std::function<int>(func));
}
