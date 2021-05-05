#pragma once
#include <iostream>
#include <vector>
#include "../node.hpp"

class audioNodeSquareWave : public audioNode{
public:
	double phase = 0;
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	std::vector<double> streams(){
		std::vector<double> output;
		double fs = 44100;
		double pi2 = 2*3.14159265358979;
		double freq = (getInput(0) * pi2 / fs);
		double currentPhaseSin = sin(phase += freq);
		double outputNum = currentPhaseSin/abs(currentPhaseSin);//I'm lazy so let's just re-use the slow sine code and slop on an absolute value
		while(phase > 3.1415926535){
			phase -= pi2;
		}
		output.push_back(outputNum);
		return(output);
	}
	void renderBody(){
		ImGui::Text("Square Wave");
		
		//std::cout<<code<<std::endl;
	}
	audioNodeSquareWave(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 1;//frequency
		streamNum = 1;
		nodes = n;
		name = "Square Wave node";
	}
};
