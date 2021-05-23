include Makefile.mk

OBJS = imgui/imgui.cpp.o \
       imgui/imgui_demo.cpp.o \
       imgui/imgui_draw.cpp.o \
       imgui/imgui_tables.cpp.o \
       imgui/imgui_widgets.cpp.o \
       imgui/backends/imgui_impl_sdl.cpp.o \
       imgui/backends/imgui_impl_opengl2.cpp.o \
       #tcc/libtcc.a


all: $(OBJS)

imgui/%.cpp.o: imgui/%.cpp
	echo $(BUILD_CXX_FLAGS)
	$(CXX) $< $(BUILD_CXX_FLAGS) -I. -Wno-unused-parameter $(LINK_OPTS_G) -c -o $@

imgui/backends%.cpp.o: imgui/backends/%.cpp
	echo $(BUILD_CXX_FLAGS)
	$(CXX) $< $(BUILD_CXX_FLAGS) -I. -Wno-unused-parameter $(LINK_OPTS_G) -c -o $@

#ifeq ($(WIN32), true)
#tcc/libtcc.a:
#	cd tcc; ./configure --enable-static --config-mingw32 --extra-cflags=-fPIC --enable-cross --with-libgcc -cc=$(CC); make
#else
#tcc/libtcc.a:
#	cd tcc; ./configure --enable-static --extra-cflags=-fPIC -cc=$(CC); make
#endif

clean:
	rm -f imgui/*.o
	rm -f imgui/backends/*.o
	rm -f imgui-node-editor/*.o
	rm -f *.[od] */*.[od]
	#cd tcc; make clean
