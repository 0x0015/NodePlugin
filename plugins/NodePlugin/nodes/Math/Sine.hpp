#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeSine : public audioNode{
public:	
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(sin(getInput(0)));
		return(output);
	}
	void renderBody(){
		ImGui::Text("Sine");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeSine(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 1;
		streamNum = 1;
		nodes = n;
		name = "Sine node";
	}
};
