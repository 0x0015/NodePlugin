#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeRandom : public audioNode{
public:	
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	double fRand(double fMin, double fMax)
	{
	    double f = (double)rand() / RAND_MAX;
	    return fMin + f * (fMax - fMin);
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(fRand(-1, 1));
		return(output);
	}
	void renderBody(){
		ImGui::Text("Random");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeRandom(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 0;
		streamNum = 1;
		nodes = n;
		name = "Random node";
	}
};
