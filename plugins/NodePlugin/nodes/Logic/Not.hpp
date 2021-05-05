#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeNot : public audioNode{
public:	
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	std::vector<double> streams(){
		std::vector<double> output;
		double outputNum;
		if(getInput(0) >= 1){
			outputNum = 0;
		}else{
			outputNum = 1;
		}
		output.push_back(outputNum);
		return(output);
	}
	void renderBody(){
		ImGui::Text("Not");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeNot(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 1;
		streamNum = 1;
		nodes = n;
		name = "Not node";
	}
};
