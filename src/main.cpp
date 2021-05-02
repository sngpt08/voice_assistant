#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include "onnxruntime/core/session/onnxruntime_cxx_api.h"
#include "sox.h"

#include "capture_audio.h"
#include "cmd_line_parser.h"
#include "voice_assistant.h"


int main(int argc, char** argv) {

  /* Parse CMD line argument */
  cmd_line_parser::CmdLineParser cmd_line_parser;
  cmd_line_parser.ParseCmdLineArgument(argc,argv);
  
  /*Create deep speech model */
  voice_assistant::VA_RetrunValue retVal;
  voice_assistant::VoiceAssistant voice_assistant;
  
  retVal = voice_assistant.VA_CreateModel(cmd_line_parser.getInputModelFile());
  if (retVal.error_code != 0) {
    std::cerr<<"Erron in creating deep speech model. Issue Msg: "<<retVal.message<<std::endl;
    exit(EXIT_FAILURE);
  }
  
  retVal = voice_assistant.VA_EnableExternalScorer(cmd_line_parser.getInputScorerFile());
  if (retVal.error_code != 0) {
    std::cerr<<"Erron in creating external scorer. Issue Msg: "<<retVal.message<<std::endl;
    exit(EXIT_FAILURE);
  }
  
  retVal = voice_assistant.VA_CreateStream();
  if (retVal.error_code != 0) {
    std::cerr<<"Erron in creating streaming state. Issue Msg: "<<retVal.message<<std::endl;
    exit(EXIT_FAILURE);
  }
  
  
  /* check if mic input is enabled */
  size_t capture_duration = cmd_line_parser.isMicEnabled();
  if (capture_duration) {
    sox_signalinfo_t param = {static_cast<sox_rate_t>(voice_assistant.VA_GetSampleRate()),
                              1,
                              SOX_DEFAULT_PRECISION,
                              0,
                              NULL};
                              
    std::unique_ptr<capture_audio::CaptureAudio> capture_audio = std::make_unique<capture_audio::CaptureAudio>();
    std::cout<<""<<std::endl;
    std::cout<<"****************************************"<<std::endl;
    std::cout<<"start capturing audio from mic..."<<std::endl;
    capture_audio->ConfigureAndCaptureAudioDevice(param, capture_duration);
    std::cout<<"end of capturing. now start processing of captured speech data."<<std::endl;
    voice_assistant.VA_FeedAudioContent(capture_audio->getInputSpeechBuffer(),capture_audio->getInputSpeechBufferLength());
  } else {
    std::string speech_input_file = cmd_line_parser.getInputSpeechFile();
    if (speech_input_file.empty()) {
      std::cerr<<"Either use mic input with duration greater than 0 or provide the audio file!!!"<<std::endl;
      exit(EXIT_FAILURE);
    } else {
      std::ifstream wav;
      wav.open(speech_input_file, std::ios_base::binary);
      if (wav.is_open()  == false) {
        std::cerr<<"Erron in input speech file !!! Please check file path and name."<<std::endl;
        exit(EXIT_FAILURE);
      }
      wav.seekg(0, std::ios::end);
      int length = wav.tellg();
      wav.seekg(0, std::ios::beg);   
      short int inputAudioBuffer[length];
      wav.read(reinterpret_cast<char*>(inputAudioBuffer),length);
      std::cout<<""<<std::endl;
      std::cout<<"****************************************"<<std::endl;
      std::cout<<"Processing input audio file"<<std::endl;
      voice_assistant.VA_FeedAudioContent(inputAudioBuffer,length);
    }
  }
    
  std::cout<<""<<std::endl;
  std::cout<<"****************************************"<<std::endl;
  std::cout<<"Recognized text is: "<< voice_assistant.VA_FinishStream()<<std::endl;
  std::cout<<"****************************************"<<std::endl;
  std::cout<<""<<std::endl;
  
  
  /* onnxruntime */
  Ort::Env env(ORT_LOGGING_LEVEL_ERROR, "test");
  Ort::SessionOptions session_options;
  session_options.SetIntraOpNumThreads(1);
  session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
  std::cout<<"Using Onnxruntime C++ API"<<std::endl;
  Ort::Session session(env, cmd_line_parser.getInputOnnxModelFile().c_str(), session_options);
  
  
  Ort::AllocatorWithDefaultOptions allocator;

  // print number of model input nodes
  size_t num_input_nodes = session.GetInputCount();
  std::cout<<"Number of inputs "<< num_input_nodes<<std::endl;
  
  return 0;
}

