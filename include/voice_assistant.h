#include <string>

#include "deepspeech.h"

namespace voice_assistant {

struct VA_RetrunValue {
  int error_code;
  std::string message;
};

class VoiceAssistant {
  public:
    VoiceAssistant();
    
    VA_RetrunValue VA_CreateModel(std::string model_file);
    
    VA_RetrunValue VA_EnableExternalScorer(std::string scorer_file);
    
    size_t VA_GetSampleRate();
    
    VA_RetrunValue VA_CreateStream();
    
    void VA_FeedAudioContent(short int *inputAudioBuffer,size_t buffer_size);
    
    std::string VA_FinishStream();
    
  private:
    ModelState *model_state;
    StreamingState* streaming_state;
    
}; // VoiceAssistant
}  // voice_assistant
