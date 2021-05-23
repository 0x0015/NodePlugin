#pragma once
#include <iostream>
#include <vector>
#include <tuple>
//#include "../TccGen.hpp"
#include "imgui.h"
#include "../json.hpp"
using json = nlohmann::json;

class audioNode{
public:
	bool toDelete = false;
	std::vector<audioNode*>* nodes;
	int inputNum = 0;
	std::vector<std::tuple<audioNode*, int, int>> inputs;//other node, the output stream number, the input stream number of this node
	int streamNum = 0;
	int nodeId;
	bool displayActive = true;
	ImVec2 windowPos;
	ImVec2 windowSize;
	bool hovered = false;
	std::string name;
	bool deletable = true;
	json serializeBasicInfo(){
		json j;
		j["name"] = name;
		j["nodeId"] = nodeId;
		//j["inputs"] = {};
		for(int i=0;i<inputs.size();i++){
			json inputsj;
			inputsj["audioNode"] = std::get<0>(inputs[i])->nodeId;
			inputsj["outputStream"] = std::get<1>(inputs[i]);
			inputsj["inputStream"] = std::get<2>(inputs[i]);
			j["inputs"].push_back(inputsj);
		}
		return(j);
	}
	virtual json serialize(){
		return(serializeBasicInfo());
	}
	double getInput(int input){
		double output=0;
		for(int i=0;i<inputs.size();i++){
			if(std::get<2>(inputs[i]) == input){
				output+=(std::get<0>(inputs[i]))->streams()[std::get<1>(inputs[i])];
			}
		}
		return(output);
	}
	 void setInput(audioNode* node, int stream, int whichInput){
		return;
	}
	virtual std::vector<double> streams(){
		return(std::vector<double>());
	};
	virtual void renderBody(){
		ImGui::Dummy(ImVec2(80.0f, 45.0f));
	}
	void goToMouse(){
		
	}
	void render(){
		//display the actual node
		displayActive = true;
		if(displayActive){
		ImGui::Begin((name + "##" + std::to_string(nodeId)).c_str(), &displayActive);
			renderBody();
			windowPos = ImGui::GetWindowPos();
			windowSize = ImGui::GetWindowSize();
			hovered = ImGui::IsWindowHovered();
			if(deletable){
			if (ImGui::BeginPopupContextWindow())
			    {
			        if (ImGui::Selectable("Delete"))
			        {
					inputs.clear();
					std::cout<<"deleting node"<<std::endl;
					for(int i=0;i<nodes->size();i++){
						for(int i2=0;i2<(*nodes)[i]->inputs.size();i2++){
							if(std::get<0>((*nodes)[i]->inputs[i2])->nodeId == nodeId){
								(*nodes)[i]->inputs.erase((*nodes)[i]->inputs.begin() + i2);
								i2--;
							}
						}
					}
					toDelete = true;
			        }
		        ImGui::EndPopup();
		    }
			}
		ImGui::End();
		
		//display the links
		auto drawList = ImGui::GetBackgroundDrawList();
		ImVec2 winpos1 = windowPos;
		ImVec2 winsize1 = windowSize;
		for(int i=0;i<inputs.size();i++){
			
			int stream1 = std::get<2>(inputs[i]);
			int inputnum1 = inputNum;
			int stream2 = std::get<1>(inputs[i]);
			int streamnum2 = std::get<0>(inputs[i])->streamNum;
			ImVec2 winpos2 = std::get<0>(inputs[i])->windowPos;
			ImVec2 winsize2 = std::get<0>(inputs[i])->windowSize;
			ImVec2 curvePos1 = ImVec2(winpos1.x, winpos1.y + (((float)stream1+1) * (winsize1.y/((float)inputnum1+1))));
			ImVec2 curvePos2 = ImVec2(winpos2.x+winsize2.x, winpos2.y + (((float)stream2+1) * (winsize2.y/((float)streamnum2+1))));

			
			drawList->AddBezierCurve(curvePos1, curvePos1 + ImVec2(-50, 0), curvePos2 + ImVec2(50,0), curvePos2, IM_COL32(200, 200, 100, 255), 3.0f);
		}
		for(int i=0;i<inputNum;i++){
			ImVec2 inputPosition = ImVec2(winpos1.x, winpos1.y + (((float)i+1) * (winsize1.y/((float)inputNum+1))));
			drawList->AddCircleFilled(inputPosition, 5.0f, IM_COL32(100,200,200,255));
		}
		
		for(int i=0;i<streamNum;i++){
			ImVec2 inputPosition = ImVec2(winpos1.x + winsize1.x, winpos1.y + (((float)i+1) * (winsize1.y/((float)streamNum+1))));
			drawList->AddCircleFilled(inputPosition, 5.0f, IM_COL32(100,200,200,255));
		}
		}
	}
	audioNode(){

	}
	audioNode(std::vector<audioNode*>* n, int id){
		nodeId = id;
		nodes = n;
		name = "Dummy Node";
	}
};
