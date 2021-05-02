#include <string>

#include "voice_assistant.h"

namespace voice_assistant {

VoiceAssistant::VoiceAssistant() {

}
    
VA_RetrunValue  VoiceAssistant::VA_CreateModel(std::string model_file) {
  VA_RetrunValue retVal;
  retVal.error_code = DS_CreateModel(model_file.c_str(),&model_state);
  if (retVal.error_code != 0) {
    retVal.message = std::string(DS_ErrorCodeToErrorMessage(retVal.error_code));
  }
  return retVal;
}
    
VA_RetrunValue  VoiceAssistant::VA_EnableExternalScorer(std::string scorer_file) {
  VA_RetrunValue retVal;
  retVal.error_code = DS_EnableExternalScorer(model_state,scorer_file.c_str());
  if (retVal.error_code != 0) {
    retVal.message = std::string(DS_ErrorCodeToErrorMessage(retVal.error_code));
    DS_FreeModel(model_state);
  }
  return retVal;
}

size_t VoiceAssistant::VA_GetSampleRate() {
  return DS_GetModelSampleRate(model_state);
}

VA_RetrunValue  VoiceAssistant::VA_CreateStream() {
  VA_RetrunValue retVal;
  retVal.error_code = DS_CreateStream(model_state,&streaming_state);
  if (retVal.error_code != 0) {
    retVal.message = std::string(DS_ErrorCodeToErrorMessage(retVal.error_code));
    DS_FreeModel(model_state);
  }
  return retVal;
}

void VoiceAssistant::VA_FeedAudioContent(short int *inputAudioBuffer,size_t buffer_size) {
  DS_FeedAudioContent(streaming_state,inputAudioBuffer,buffer_size);
}

std::string VoiceAssistant::VA_FinishStream() {
  char* output_text = DS_FinishStream(streaming_state);
  std::string retVal(output_text);
  DS_FreeString(output_text); 
  return retVal;
}

}  // voice_assistant
