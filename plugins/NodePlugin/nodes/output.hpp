#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class audioNodeOutput : public audioNode{
public:
	int outputnum = -1;
	void setInput(audioNode* node, int stream, int whichInput){
		
	}
	std::vector<double> streams(){
		return(std::vector<double>());
	}
	double computeOutput(){
		return(getInput(0));
	}
	void renderBody(){
		std::string outputText = "Output";
		if(outputnum != -1){
			outputText = outputText + " " + std::to_string(outputnum);
		}
		ImGui::Text(outputText.c_str());
		//ImGui::Text("Output");
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
