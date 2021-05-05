#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class audioNodeInput : public audioNode{
public:
	double value;
	int inputnum = -1;
	void setInput(audioNode* node, int stream, int whichInput){
		
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(value);
		return(output);
	}
	void renderBody(){
		std::string inputText = "Input";
		if(inputnum != -1){
			inputText = inputText + " " + std::to_string(inputnum);
		}
		ImGui::Text(inputText.c_str());
	}
	audioNodeInput(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 0;
		streamNum = 1;
		nodes = n;
		name = "Input";
		deletable = false;
	}
};
