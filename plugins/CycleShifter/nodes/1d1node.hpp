#pragma once
#include <iostream>
#include <vector>
#include "../TccGen.hpp"
#include "node.hpp"
#include "../TextEditor.hpp"

class audioNode1d1 : public audioNode{
public:
	TccGen<double, double>* codeGenerator;
	std::string code;
	TextEditor editor;
	void setInput(audioNode* node, int stream, int whichInput){
		if(whichInput == 0){
			inputs.push_back(std::make_tuple(node, stream, whichInput));
		}
	}
	std::vector<double> streams(){
		std::vector<double> output;
		output.push_back(codeGenerator->call(getInput(0)));
		return(output);
	}
	void updateCode(std::string c = ""){
		if(c != ""){
			code = c;
		}
		codeGenerator->generateCode();
	}
	void renderBody(){
		if(ImGui::Button("Compile")){
			codeGenerator->generateCode();
		}
		ImGui::SameLine();
		std::string compilerStatus;
		if(codeGenerator->generated){
			compilerStatus = "Compiled!";
		}else{
			if(codeGenerator->error){
				compilerStatus = "Error.";
			}else{
				compilerStatus = "Uncompiled";
			}
		}
		
		ImGui::Text(compilerStatus.c_str());
		auto cpos = editor.GetCursorPosition();
		//editor.SetText(code);
		editor.Render("CodeEditor");
		if(editor.IsTextChanged()){
			code = editor.GetText();
		}
		
		//std::cout<<code<<std::endl;
	}
	audioNode1d1(std::vector<audioNode*>* n, int id){
		nodeId = id;
		inputNum = 1;
		streamNum = 1;
		codeGenerator = new TccGen<double, double>(&code, false);
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::C());
		editor.SetText(code);
		nodes = n;
		name = "C node";
	}
};
