#include "PluginNodePlugin.hpp"
//#include "GUI.hpp"
#include <iostream>
#include "TccGen.hpp"
START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistrhoPluginNodePlugin::DistrhoPluginNodePlugin()
    : Plugin(kParameterCount, 1, 0), // 1 program, 0 states
      fInputVolume(1.0f),
      OutIndex(0),
      InCount(0),
      ReadWrite(false),
      EnvOld(0.0f)
{
	inputNode1 = new audioNodeInput(&nodes, 0);
	inputNode1->inputnum = 1;
	outputNode1 = new audioNodeOutput(&nodes, 1);
	outputNode1->outputnum = 1;
	nodes.push_back(inputNode1);
	nodes.push_back(outputNode1);
	inputNode2 = new audioNodeInput(&nodes, 2);
	inputNode2->inputnum = 2;
	outputNode2 = new audioNodeOutput(&nodes, 3);
	outputNode2->outputnum = 2;
	nodes.push_back(inputNode2);
	nodes.push_back(outputNode2);
}

// -----------------------------------------------------------------------
// Init

void DistrhoPluginNodePlugin::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints      = kParameterIsAutomable;
    parameter.ranges.min = -90.0f;
    parameter.ranges.max = 30.0f;

    parameter.name       = "Input Vol";
    parameter.symbol     = "ipvolume";
    parameter.ranges.def = -0.0f;
    parameter.unit = "db";
    
}

void DistrhoPluginNodePlugin::initProgramName(uint32_t index, String& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float DistrhoPluginNodePlugin::getParameterValue(uint32_t index) const
{
    switch(index)
    {
    case kParameterInputVolume:
        return fInputVolume;
    default:
        return 0.0f;
    }
}

void DistrhoPluginNodePlugin::setParameterValue(uint32_t index, float value)
{
    switch(index)
    {
    case kParameterInputVolume:
        fInputVolume = value;
        break;
    }
}

void DistrhoPluginNodePlugin::loadProgram(uint32_t index)
{
    if (index != 0)
        return;

    fInputVolume    = 1.0f;
}

// -----------------------------------------------------------------------
// Process

void DistrhoPluginNodePlugin::activate()
{
    //std::memset(CycleBuffer, 0, sizeof(float)*BUFFER_SIZE);
    OutIndex = 0;
    InCount = 0;
    ReadWrite = false;
    EnvOld = 0.0f;
    GUIdone = false;
    GUIthread = startThread(&GUIdone, &nodes);
}

void DistrhoPluginNodePlugin::deactivate(){
	GUIdone = true;
	GUIthread.join();
}

void DistrhoPluginNodePlugin::run(const float** inputs, float** outputs, uint32_t frames)
{
   // const float* in  =  inputs[0];
   // /**/  float* out = outputs[0];

   // for (uint32_t i=0; i<frames; ++i)
   //     *out++ = DoProcess(*in++);

    // get the left and right audio inputs
    const float* in1  =  inputs[0];
    float* out1 = outputs[0];
    const float* in2  =  inputs[1];
    float* out2 = outputs[1];

    for (uint32_t i=0; i<frames; ++i){
	double input1 = (double)(*in1++);
	
	inputNode1->value = input1;
	double computedValue1 = outputNode1->computeOutput();
	float output1 = (float)computedValue1;
	*out1++ = output1;

    	double input2 = (double)(*in2++);
	
	inputNode2->value = input2;
	double computedValue2 = outputNode2->computeOutput();
	float output2 = (float)computedValue2;
	*out2++ = output2;
    }
    return;

    //const float* inpL = inputs[0];
    //const float* const inpR = inputs[1];

    // get the left and right audio outputs
    //float* outL = outputs[0];
    //float* const outR = outputs[1];

    // apply gain against all samples
    /*
    float a = exp(-6.283185307179586476925286766559f / (20.0f * 0.001f * 44100));
    float b = 1.0f - a;
    float z = 0.0f;
    z = (fInputVolume * b) + (z * a);
    const float* in  =  inputs[0];
    float* out = outputs[0];

    for (uint32_t i=0; i<frames; ++i){
        *out++ = (*in++) * z;
    }
    return;
    */

}


Plugin* createPlugin()
{
    return new DistrhoPluginNodePlugin();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
