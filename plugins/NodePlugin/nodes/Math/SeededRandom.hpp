#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeSeededRandom : public audioNode{
public:	
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	double fSRand(double seed, double fMin, double fMax)
	{
	    srand(seed);
	    double f = (double)rand() / RAND_MAX;
	    return fMin + f * (fMax - fMin);
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(fSRand(getInput(0), -1, 1));
		return(output);
	}
	void renderBody(){
		ImGui::Text("Seeded Random");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeSeededRandom(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 1;
		streamNum = 1;
		nodes = n;
		name = "Seeded Random node";
	}
};
