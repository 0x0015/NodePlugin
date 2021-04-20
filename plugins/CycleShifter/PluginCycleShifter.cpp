#include "PluginCycleShifter.hpp"
//#include "GUI.hpp"
#include <iostream>
#include "TccGen.hpp"
START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

DistrhoPluginCycleShifter::DistrhoPluginCycleShifter()
    : Plugin(kParameterCount, 1, 0), // 1 program, 0 states
      fInputVolume(1.0f),
      OutIndex(0),
      InCount(0),
      ReadWrite(false),
      EnvOld(0.0f)
{
	inputNode = new audioNodeInput(&nodes, 0);
	outputNode = new audioNodeOutput(&nodes, 1);
	nodes.push_back(inputNode);
	nodes.push_back(outputNode);
}

// -----------------------------------------------------------------------
// Init

void DistrhoPluginCycleShifter::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints      = kParameterIsAutomable;
    parameter.ranges.min = -90.0f;
    parameter.ranges.max = 30.0f;

    parameter.name       = "Input Vol";
    parameter.symbol     = "ipvolume";
    parameter.ranges.def = -0.0f;
    parameter.unit = "db";
    
}

void DistrhoPluginCycleShifter::initProgramName(uint32_t index, String& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float DistrhoPluginCycleShifter::getParameterValue(uint32_t index) const
{
    switch(index)
    {
    case kParameterInputVolume:
        return fInputVolume;
    default:
        return 0.0f;
    }
}

void DistrhoPluginCycleShifter::setParameterValue(uint32_t index, float value)
{
    switch(index)
    {
    case kParameterInputVolume:
        fInputVolume = value;
        break;
    }
}

void DistrhoPluginCycleShifter::loadProgram(uint32_t index)
{
    if (index != 0)
        return;

    fInputVolume    = 1.0f;
}

// -----------------------------------------------------------------------
// Process

void DistrhoPluginCycleShifter::activate()
{
    //std::memset(CycleBuffer, 0, sizeof(float)*BUFFER_SIZE);
    OutIndex = 0;
    InCount = 0;
    ReadWrite = false;
    EnvOld = 0.0f;
    GUIdone = false;
    GUIthread = startThread(&GUIdone, &nodes);
}

void DistrhoPluginCycleShifter::deactivate(){
	GUIdone = true;
	GUIthread.join();
}

void DistrhoPluginCycleShifter::run(const float** inputs, float** outputs, uint32_t frames)
{
   // const float* in  =  inputs[0];
   // /**/  float* out = outputs[0];

   // for (uint32_t i=0; i<frames; ++i)
   //     *out++ = DoProcess(*in++);

    // get the left and right audio inputs
    const float* in  =  inputs[0];
    float* out = outputs[0];

    for (uint32_t i=0; i<frames; ++i){
	inputNode->value = (double)(*in++);
	*out++ = (float)outputNode->computeOutput();
        //*out++ = *in++;
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
    return new DistrhoPluginCycleShifter();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
