include Makefile.mk

OBJS = imgui/imgui.cpp.o \
       imgui/imgui_demo.cpp.o \
       imgui/imgui_draw.cpp.o \
       imgui/imgui_tables.cpp.o \
       imgui/imgui_widgets.cpp.o \
       imgui/backends/imgui_impl_sdl.cpp.o \
       imgui/backends/imgui_impl_opengl2.cpp.o


all: $(OBJS)

imgui/%.cpp.o: imgui/%.cpp
	echo $(BUILD_CXX_FLAGS)
	$(CXX) $< $(BUILD_CXX_FLAGS) -I. -Wno-unused-parameter $(LINK_OPTS_G) -c -o $@

clean:
	rm -f imgui/*.o
	rm -f imgui/backends/*.o
	rm -f *.[od] */*.[od]
