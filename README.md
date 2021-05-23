# NodePlugin
An experimental node based vst effect.

Todo:<br>
add more waves: triangle, saw<br>
better selection (eg. selecting multiple nodes, selecting connections, etc...)<br>
Fix it to allow it to be saved(when you reload the project in the daw), and if I need to export the entire thing to json, etc... (It currently is not saved, check if a vst parameter can be a string, or only a number and if it's a number save the json(or whatever) file elsewhere and use the number to store the hash to lookup the file later)<br>
find compatability of sdl with actual correct vst graphics interfaces<br>
add more interesting nodes(maybe reverb, fft, compressor, etc...)<br>
<br>
<br>
Done:<br>
get the C code generation:  I did them one better and got C++ code generation working by using mingw to compile dlls which are loaded in runtime thanks to dlsym(thanks http://mingw-w64.org and https://github.com/dlfcn-win32/dlfcn-win32)<br>
