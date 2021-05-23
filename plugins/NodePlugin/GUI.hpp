// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_sdl_opengl3/ folder**
// See imgui_impl_sdl.cpp for details.
#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <thread>
#include <iostream>
//#include "imnodes.h"
//#include "imnodes_internal.h"
//#include <libtcc.h>
#include "nodes/nodes.hpp"


int mainLoop(bool* done, std::vector<audioNode*>* nodes)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImNodes::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();


    bool show_node_graph = true;


    // Our state
    //bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool mouseDownLastFrame = false;
    bool rightMouseDownLastFrame = false;
    int startingLinkNode = -1;
    int startingLinkStreamNum = -1;

    int nodeNum = 4;
    // Main loop
    //bool done = false;
    while (!(*done))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                *done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                *done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
	
	//ImGui::SetNextWindowPos(ImVec2(0, 0));
        //ImGui::SetNextWindowSize(io.DisplaySize);
        //ImGui::Begin("Content", nullptr,
        //    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        //    ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings |
        //    ImGuiWindowFlags_NoBringToFrontOnFocus);
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui
	//const int hardcoded_node_id = 1;

	//ImNodes::BeginNodeEditor();
	
	for(int i=0;i<nodes->size();i++){
		if((*nodes)[i]->toDelete){
			delete (*nodes)[i];
			nodes->erase(nodes->begin() + i);
			i--;
			continue;
		}
		(*nodes)[i]->render();
	}

	bool clickedOnSomething = false;

	ImVec2 cursorPos = ImGui::GetCursorPos();
	bool itemHovered = false;
	for(int i=0;i<nodes->size();i++){
		if((*nodes)[i]->hovered){
			itemHovered = true;
		}
	}
	int tempMouseX;
	int tempMouseY;
	bool mouseClicked = SDL_GetMouseState(&tempMouseX, &tempMouseY) & SDL_BUTTON(SDL_BUTTON_LEFT);
	bool rightMouseClicked = SDL_GetMouseState(&tempMouseX, &tempMouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT);
	cursorPos = ImVec2(tempMouseX, tempMouseY);

	if(mouseClicked && rightMouseClicked){//if both are clicked it means NOTHING
		mouseClicked = false;
		rightMouseClicked = false;
	}

	//if(!clickedOnSomething && rightMouseClicked && !rightMouseDownLastFrame && startingLinkNode == -1 && !itemHovered){
		//std::cout<<"opening right click menu"<<std::endl;
		if(ImGui::BeginPopupContextVoid()){
			std::cout<<"opened menu"<<std::endl;
			//if(ImGui::Selectable("Yay a menu")){
			//	
			//}
			nodeCreationMenu(nodes, &nodeNum);
			ImGui::EndPopup();
		}
	//}

	if(rightMouseClicked && !rightMouseDownLastFrame && !itemHovered){
		std::cout<<"rightmousedown"<<std::endl;
		for(int i=0;i<(*nodes).size();i++){
			for(int i2=0;i2<(*nodes)[i]->streamNum;i2++){
			ImVec2 winpos1 = (*nodes)[i]->windowPos;
			ImVec2 winsize1 = (*nodes)[i]->windowSize;
			ImVec2 curvePos1 = ImVec2(winpos1.x + winsize1.x, winpos1.y + (((float)i2+1) * (winsize1.y/((float)((*nodes)[i]->streamNum)+1))));
			ImVec2 curvePos2 = cursorPos;
			float mouseDistence = sqrt(((curvePos1.x-cursorPos.x)*(curvePos1.x-cursorPos.x))+((curvePos1.y-cursorPos.y)*(curvePos1.y-cursorPos.y)));

			if(mouseDistence < 15){//remove source link
				clickedOnSomething = true;
				std::cout<<"removing source links"<<std::endl;
				//I think I need to loop through all the connections to find those with this node as the source
				int nodeID = (*nodes)[i]->nodeId;

				for(int x=0;x<(*nodes).size();x++){
					for(int x2=0;x2<(*nodes)[x]->inputs.size();x2++){
						int onodeID = std::get<0>((*nodes)[x]->inputs[x2])->nodeId;
						int onodei2 = std::get<1>((*nodes)[x]->inputs[x2]);
						if(nodeID == onodeID && onodei2 == i2){
							(*nodes)[x]->inputs.erase((*nodes)[x]->inputs.begin()+x2);
							x2--;
						}
					}
				}
			}
			}
			for(int i2=0;i2<(*nodes)[i]->inputNum;i2++){
			ImVec2 winpos1 = (*nodes)[i]->windowPos;
			ImVec2 winsize1 = (*nodes)[i]->windowSize;
			ImVec2 curvePos2 = cursorPos;
			ImVec2 curvePos3 = ImVec2(winpos1.x, winpos1.y + (((float)i2+1) * (winsize1.y/((float)((*nodes)[i]->inputNum)+1))));
			float mouseDistence2 = sqrt(((curvePos3.x-cursorPos.x)*(curvePos3.x-cursorPos.x))+((curvePos3.y-cursorPos.y)*(curvePos3.y-cursorPos.y)));
			if(mouseDistence2 < 15){//remove input link
				clickedOnSomething = true;
				std::cout<<"removing input links"<<std::endl;
				//(*nodes)[i]->inputs.clear();  nope, only clear links to THIS input not all inputs on this node
				for(int x=0;x<(*nodes)[i]->inputs.size();x++){
					if(std::get<2>((*nodes)[i]->inputs[x]) == i2){
						(*nodes)[i]->inputs.erase((*nodes)[i]->inputs.begin() + x);
						x--;
					}
				}
			}
			}
		}
	}


	if(mouseClicked && !mouseDownLastFrame && !itemHovered){
		std::cout<<"mousedown"<<std::endl;
		for(int i=0;i<(*nodes).size();i++){
			for(int i2=0;i2<(*nodes)[i]->streamNum;i2++){
			ImVec2 winpos1 = (*nodes)[i]->windowPos;
			ImVec2 winsize1 = (*nodes)[i]->windowSize;
			ImVec2 curvePos1 = ImVec2(winpos1.x + winsize1.x, winpos1.y + (((float)i2+1) * (winsize1.y/((float)((*nodes)[i]->streamNum)+1))));
			ImVec2 curvePos2 = cursorPos;
			float mouseDistence = sqrt(((curvePos1.x-cursorPos.x)*(curvePos1.x-cursorPos.x))+((curvePos1.y-cursorPos.y)*(curvePos1.y-cursorPos.y)));
			//std::cout<<mouseDistence<<std::endl;
			if(mouseDistence < 15){
				clickedOnSomething = true;
				//std::cout<<"in range"<<std::endl;
				startingLinkNode = i;
				startingLinkStreamNum = i2;
			}
			}
		}
	}
	if(mouseClicked && startingLinkNode != -1){
		auto drawList = ImGui::GetBackgroundDrawList();
		ImVec2 winpos1 = (*nodes)[startingLinkNode]->windowPos;
		ImVec2 winsize1 = (*nodes)[startingLinkNode]->windowSize;
		//ImVec2 curvePos1 = ImVec2(winpos1.x+winsize1.x, winpos1.y);	
		ImVec2 curvePos1 = ImVec2(winpos1.x + winsize1.x, winpos1.y + (((float)startingLinkStreamNum+1) * (winsize1.y/((float)((*nodes)[startingLinkNode]->streamNum)+1))));
		ImVec2 curvePos2 = cursorPos;
		drawList->AddBezierCurve(curvePos1, curvePos1 + ImVec2(50, 0), curvePos2 + ImVec2(-50,0), curvePos2, IM_COL32(200, 200, 100, 255), 3.0f);
	}

	if(!mouseClicked && mouseDownLastFrame && startingLinkNode != -1 && startingLinkStreamNum != -1){

		std::cout<<"mouserelease"<<std::endl;
		for(int i=0;i<(*nodes).size();i++){
			for(int i2=0;i2<(*nodes)[i]->inputNum;i2++){
			ImVec2 winpos1 = (*nodes)[i]->windowPos;
			ImVec2 winsize1 = (*nodes)[i]->windowSize;
			ImVec2 curvePos1 = ImVec2(winpos1.x, winpos1.y + (((float)i2+1) * (winsize1.y/((float)((*nodes)[i]->inputNum)+1))));
			ImVec2 curvePos2 = cursorPos;
			float mouseDistence = sqrt(((curvePos1.x-cursorPos.x)*(curvePos1.x-cursorPos.x))+((curvePos1.y-cursorPos.y)*(curvePos1.y-cursorPos.y)));
			//std::cout<<mouseDistence<<std::endl;
			if(mouseDistence < 15 && startingLinkNode != i){
				std::cout<<"link between ";
				std::cout<<startingLinkNode;
				std::cout<<" stream ";
				std::cout<<startingLinkStreamNum;
				std::cout<<" and ";
				std::cout<<i;
				std::cout<<"(this) input ";
				std::cout<<i2<<std::endl;
				if(startingLinkNode == -1 || startingLinkStreamNum == -1){
					std::cout<<"ERROR found a -1 where there should be an actual number"<<std::endl;
					break;
				}
				//now I need to check if the link already exists, and if it doesn't create the new link
				bool exists = false;
				for(int x=0;x<(*nodes)[i]->inputs.size();x++){
					int nodeid = std::get<0>((*nodes)[i]->inputs[x])->nodeId;
					int onodeid =(*nodes)[startingLinkNode]->nodeId;
					int inputnum = std::get<1>((*nodes)[i]->inputs[x]) ;
					int oinputnum = startingLinkStreamNum;
					int streamnum =  std::get<2>((*nodes)[i]->inputs[x]);
					int ostreamnum = i2;
					std::cout<<nodeid<<onodeid<<inputnum<<oinputnum<<streamnum<<ostreamnum<<std::endl;
					if( nodeid == onodeid && inputnum == oinputnum && streamnum == ostreamnum){
						exists = true;
						break;
					}
				}
				if(exists){
					std::cout<<"link already exists! not creating"<<std::endl;
				}else{
					(*nodes)[i]->inputs.push_back(std::tuple<audioNode*, int, int>((*nodes)[startingLinkNode],startingLinkStreamNum, i2));
				}
			}
			}
		}
		startingLinkNode = -1;
		startingLinkStreamNum = -1;
	}

	

	mouseDownLastFrame = mouseClicked;
	rightMouseDownLastFrame = rightMouseClicked;

	//clean up node ids
	//for(int i=0;i<nodes->size();i++){
	//	(*nodes)[i]->nodeId = i;//reassigning all ids, to prevent confusion
	//}

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    //ImNodes::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
/*
int main(){

	bool done = false;
	//mainLoop(&done);
	std::thread mainLoopThread(mainLoop, &done);
	while(!done){
		//nothing
		std::cout<<"outside of thread"<<std::endl;
	}
	mainLoopThread.join();
	return(0);
}
*/
std::thread startThread(bool* done, std::vector<audioNode*>* nodes){
	return(std::thread(mainLoop, done, nodes));
}
