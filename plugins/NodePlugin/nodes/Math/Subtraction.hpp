#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeSubtraction : public audioNode{
public:	
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(getInput(0) - getInput(1));
		return(output);
	}
	void renderBody(){
		ImGui::Text("Subtract");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeSubtraction(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 2;
		streamNum = 1;
		nodes = n;
		name = "Subtraction node";
	}
};
