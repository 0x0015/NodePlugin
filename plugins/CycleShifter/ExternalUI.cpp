/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2019 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoUI.hpp"

#include "GUI.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class ExternalExampleUI : public UI
{
public:
    ExternalExampleUI()
        : UI(405, 256)
    {
		done = false;
		GUIthread = startGUIThread(&done);
    }

protected:
   /* --------------------------------------------------------------------------------------------------------
    * DSP/Plugin Callbacks */

   /**
      A parameter has changed on the plugin side.
      This is called by the host to inform the UI about parameter changes.
    */
    void parameterChanged(uint32_t index, float value) override
    {
		
    }
	
	void programLoaded(uint32_t index)override{
		
	}
	
	//void stateChanged(const char* key, const char* value)override{
	//	
	//}
	
	void sampleRateChanged(double samplerate)override{
		
	}
	
	void onDisplay()override{
		
	}

   /* --------------------------------------------------------------------------------------------------------
    * External Window overrides */

   /**
      Manage external process and IPC when UI is requested to be visible.
    */
	/*
    void setVisible(const bool yesNo) override
    {
        if (yesNo)
        {
            //make visable
			if(!GUIThreadRunning){
				GUIthread = startGUIThread(&done);
			}
			done = false;
        }
        else
        {
            //not visable
			done = true;
			GUIthread.join();
        }

        UI::setVisible(yesNo);
    }
*/
    // -------------------------------------------------------------------------------------------------------

private:
    bool done;
	std::thread GUIthread;

   /**
      Set our UI class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ExternalExampleUI)
};

/* ------------------------------------------------------------------------------------------------------------
 * UI entry point, called by DPF to create a new UI instance. */

UI* createUI()
{
    return new ExternalExampleUI();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO