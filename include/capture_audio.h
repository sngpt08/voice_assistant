#include "sox.h"
#include <memory>

namespace capture_audio {

class CaptureAudio {

   public:
     CaptureAudio();
     
    ~CaptureAudio();
     
     bool ConfigureAndCaptureAudioDevice(sox_signalinfo_t param, size_t capture_duration);
     
     short int* getInputSpeechBuffer();
     
     size_t getInputSpeechBufferLength();
        
   private:
     sox_format_t* input;
     sox_format_t* output;
     sox_effects_chain_t* effectsChain;
     sox_signalinfo_t intermediateSignal;
     size_t buffer_size_;
     short int *buffer_;
     
}; // CaptureAudio
}  // namespace capture_audio
