#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class audioNodeInput : public audioNode{
public:
	double value;
	void setInput(audioNode* node, int stream, int whichInput){
		
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(value);
		return(output);
	}
	void renderBody(){
		ImGui::Text("Input");
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
