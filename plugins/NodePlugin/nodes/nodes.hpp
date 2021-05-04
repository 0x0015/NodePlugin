#pragma once
#include "node.hpp"
#include "1d1node.hpp"
#include "dValuenode.hpp"
#include "dValuenode2.hpp"
#include "output.hpp"
#include "input.hpp"
#include "4Func/audioNode4Func.hpp"

void nodeCreationMenu(std::vector<audioNode*>* nodes, int* nodeInc){
	ImGui::Text("Node Creation");
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
	if(ImGui::Selectable("C node")){
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
