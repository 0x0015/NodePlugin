#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = CycleShifter

# --------------------------------------------------------------
# Files to build

FILES_DSP = PluginCycleShifter.cpp

FILES_UI  = ExternalUI.cpp
	#ArtworkCycleShifter.cpp \
	#UICycleShifter.cpp

# --------------------------------------------------------------
# Do some magic
UI_TYPE = external
include ../../dpf/Makefile.plugins.mk

PKG_CONFIG ?= pkg-config

BUILD_CXX_FLAGS := -I../../common/imgui $(BUILD_CXX_FLAGS)

BUILD_CXX_FLAGS := ../../common/imgui/*.cpp.o $(BUILD_CXX_FLAGS)
BUILD_CXX_FLAGS := ../../common/imgui/backends/*.cpp.o $(BUILD_CXX_FLAGS)


# --------------------------------------------------------------
# Link dependencies

LINK_OPTS += -lm -ldl
ifeq ($(LINUX), true)
#LINK_OPTS += -L../../common/SDL2/x86_64-linux/lib
LINK_OPTS += $(shell $(PKG_CONFIG) --libs sdl2) 
LINK_OPTS += $(shell $(PKG_CONFIG) --libs gl)
endif

ifeq ($(WIN32),true)
BUILD_CXX_FLAGS += -I../../common/SDL2/x86_64-w64-mingw32/include
LINK_OPTS += -L../../common/SDL2/x86_64-w64-mingw32/lib -l:libSDL2.a -l:libSDL2main.a -l:libSDL2_test.a
#LINK_OPTS += -L../../common/win_opengl -l:libopengl32.a
#lINK_OPTS += -L/usr/x86_64-w64-mingw32/lib
LINK_OPTS += -L../../dpf/build -l:libdgl-opengl.a
#LINK_OPTS += -l:libdgl.a
LINK_OPTS += -static -static-libgcc -static-libstdc++ -lhid
LINK_OPTS += -lmingw32 -mwindows  -Wl,--no-undefined -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lglu32 -lopengl32 
#LINK_OPTS += $(DGL_LIBS)
#LINK_OPTS += $(OBJS_opengl)
endif


# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(LINUX),true)
ifeq ($(HAVE_DGL),true)
ifeq ($(HAVE_JACK),true)
TARGETS += jack
endif
endif
endif

ifeq ($(HAVE_DGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
