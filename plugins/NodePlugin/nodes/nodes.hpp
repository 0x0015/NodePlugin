#pragma once
#include "node.hpp"
#include "1d1node.hpp"
#include "dValuenode.hpp"
#include "dValuenode2.hpp"
#include "dValueSlidernode.hpp"
#include "output.hpp"
#include "input.hpp"
#include "Math/audioNodeMath.hpp"
#include "waves/audioNodeWaves.hpp"
#include "Logic/audioNodeLogic.hpp"

json serializeNodes(std::vector<audioNode*>* nodes){
	json j;
	for(int i=0;i<nodes->size();i++){
		j.push_back((*nodes)[i]->serialize());
	}
	return(j);
}

void nodeCreationMenu(std::vector<audioNode*>* nodes, int* nodeInc){
	ImGui::Text("Node Creation");
	if(ImGui::BeginMenu("Values")){
		if(ImGui::Selectable("Value")){
			(*nodeInc)++;
			nodes->push_back(new audioNodedValue(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("2 Values")){
			(*nodeInc)++;
			nodes->push_back(new audioNoded2Value(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Value Slider")){
			(*nodeInc)++;
			nodes->push_back(new audioNodedSliderValue(nodes, *nodeInc));
			return;
		}
		ImGui::EndMenu();
	}
	if(ImGui::BeginMenu("Math")){
		if(ImGui::Selectable("Addition")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeAddition(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Subtraction")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeSubtraction(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Multiplication")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeMultiplication(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Division")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeDivision(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Power")){
			(*nodeInc)++;
			nodes->push_back(new audioNodePower(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Modulo")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeModulo(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Absolute Value")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeAbsoluteValue(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Sine")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeSine(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Cosine")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeCosine(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Tangent")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeTangent(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Random")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeRandom(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Random Seeded")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeSeededRandom(nodes, *nodeInc));
			return;
		}	
		ImGui::EndMenu();
	}
	if(ImGui::BeginMenu("Logic")){
		if(ImGui::Selectable("And")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeAnd(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Or")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeOr(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Xor")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeXor(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Not")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeNot(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Greater than")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeGreaterThan(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Less than")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeLessThan(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Equal to")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeEqualTo(nodes, *nodeInc));
			return;
		}
		ImGui::EndMenu();
	}
	if(ImGui::BeginMenu("Waves")){
		if(ImGui::Selectable("Sine Wave")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeSineWave(nodes, *nodeInc));
			return;
		}
		if(ImGui::Selectable("Square Wave")){
			(*nodeInc)++;
			nodes->push_back(new audioNodeSquareWave(nodes, *nodeInc));
			return;
		}
		ImGui::EndMenu();
	}
	if(ImGui::Selectable("C++ node")){
		(*nodeInc)++;
		nodes->push_back(new audioNode1d1(nodes, *nodeInc));
		return;
	}
	if(ImGui::Selectable("Dummy")){
		(*nodeInc)++;
		nodes->push_back(new audioNode(nodes, *nodeInc));
		return;
	}
}
