#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class audioNodeOutput : public audioNode{
public:
	void setInput(audioNode* node, int stream, int whichInput){
		
	}
	std::vector<double> streams(){
		return(std::vector<double>());
	}
	double computeOutput(){
		return(getInput(0));
	}
	void renderBody(){
		ImGui::Text("Output");
	}
	audioNodeOutput(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 1;
		streamNum = 0;
		nodes = n;
		name = "Output";
		deletable = false;
	}
};
