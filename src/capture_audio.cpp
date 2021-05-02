#include "capture_audio.h"
#include <memory>

namespace capture_audio {

CaptureAudio::CaptureAudio() {
  sox_init();
}

CaptureAudio::~CaptureAudio() {
  sox_delete_effects_chain(effectsChain);
  sox_close(output);
  sox_close(input);
  sox_quit();
}
     
bool CaptureAudio::ConfigureAndCaptureAudioDevice(sox_signalinfo_t param, size_t capture_duration) {
  input = sox_open_read("default", &param, NULL, "alsa");
  buffer_size_ = capture_duration * input->signal.rate * sizeof(short int) * input->signal.channels;
  buffer_= new short int [buffer_size_];
  output = sox_open_mem_write(buffer_, buffer_size_, &param, NULL, "wav", NULL);
  intermediateSignal = input->signal;     
  effectsChain = sox_create_effects_chain(&input->encoding, NULL);
     
  sox_effect_t *effect;
  effect = sox_create_effect(sox_find_effect("input"));
  char *args[] = {reinterpret_cast<char *>(input)};
  sox_effect_options(effect, 1, args);
  sox_add_effect(effectsChain, effect, &intermediateSignal, &input->signal);

  char * val[2] = {const_cast<char*>("0"),
                const_cast<char*>(std::to_string(capture_duration).c_str())};
  effect = sox_create_effect(sox_find_effect("trim"));
  sox_effect_options(effect, 2, val); 
  sox_add_effect(effectsChain, effect, &intermediateSignal, &input->signal);

  effect = sox_create_effect(sox_find_effect("output"));
  char *args1[] = {reinterpret_cast<char *>(output)};
  sox_effect_options(effect, 1, args1);
  sox_add_effect(effectsChain, effect, &intermediateSignal, &input->signal);

  sox_flow_effects(effectsChain, NULL, NULL);
  return true;
}

short int* CaptureAudio::getInputSpeechBuffer() {
  return buffer_;
}

size_t CaptureAudio::getInputSpeechBufferLength() {
  return buffer_size_;
}

}  // namespace capture_audio
