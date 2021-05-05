#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeEqualTo : public audioNode{
public:	
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	std::vector<double> streams(){
		std::vector<double> output;
		double outputNum;
		double diff = abs(getInput(0)-getInput(1));
		if(diff <= getInput(2)){
			outputNum = 1;
		}else{
			outputNum = 0;
		}
		output.push_back(outputNum);
		return(output);
	}
	void renderBody(){
		ImGui::Text("Equality within an epsilon");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeEqualTo(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 3;
		streamNum = 1;
		nodes = n;
		name = "Equal to node";
	}
};
