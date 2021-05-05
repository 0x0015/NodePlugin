#pragma once
#include <iostream>
#include <vector>
#include "node.hpp"

class audioNodedSliderValue : public audioNode{
public:
	float value;
	void setInput(audioNode* node, int stream, int whichInput){
		
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back((double)value);
		return(output);
	}
	void renderBody(){
		//ImGui::InputDouble("Value", &value);
		//ImGui::
		//ImGui::SliderFloat("Value", &value, max, min);
		ImGui::DragFloat2("Value", &value);//no drag double sadly
		
	}
	audioNodedSliderValue(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 0;
		streamNum = 1;
		nodes = n;
		name = "Value Slider";
	}
};
