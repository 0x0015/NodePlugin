#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeXor : public audioNode{
public:	
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	std::vector<double> streams(){
		std::vector<double> output;
		double outputNum;
		if(getInput(0) >= 1 != getInput(1) >= 1){
			outputNum = 1;
		}else{
			outputNum = 0;
		}
		output.push_back(outputNum);
		return(output);
	}
	void renderBody(){
		ImGui::Text("Xor");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeXor(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 2;
		streamNum = 1;
		nodes = n;
		name = "Xor node";
	}
};
