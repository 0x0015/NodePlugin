#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class audioNoded2Value : public audioNode{
public:
	std::string code;
	double value;
	double value2;
	void setInput(audioNode* node, int stream, int whichInput){
		
	}
	json serialize(){
		json j = serializeBasicInfo();
		j["value"] = value;
		j["value2"] = value2;
		return(j);
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(value);
		output.push_back(value2);
		return(output);
	}
	void renderBody(){
		ImGui::InputDouble("Value", &value);
		ImGui::InputDouble("Value 2", &value2);

	}
	audioNoded2Value(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 0;
		streamNum = 2;
		nodes = n;
		name = "2 Values";
	}
};
