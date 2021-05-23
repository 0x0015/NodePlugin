#pragma once
#include <iostream>
#include <vector>
#include "../CppGen.hpp"
#include "node.hpp"
#include "../TextEditor.hpp"

class audioNode1d1 : public audioNode{
public:
	CppGen<double, double>* codeGenerator;
	std::string code;
	std::string completeCode;
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
			completeCode = "extern \"C\" {double run(double);}\n" + code;
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
		if(codeGenerator->compilerOutput != ""){
			if(ImGui::BeginPopupContextItem("Output")){
				ImGui::Text(codeGenerator->compilerOutput.c_str());
			}
		}
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
#if defined(_WIN32) || defined(_WIN64)
		codeGenerator = new CppGen<double, double>(&completeCode, false, getDllPath("NodePlugin-vst.dll") + "/Mingw-w64/mingw64/bin/g++.exe", "run");
#else
		codeGenerator = new CppGen<double, double>(&completeCode, false, "g++", "run");
#endif
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
		editor.SetText(code);
		nodes = n;
		name = "Cpp node";
	}
};
