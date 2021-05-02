# voice_assistant

This code convert the speech data to text using deep speech lib. You can either use mic or give the audio file by specifying in the cmd line argument.

Instuction to build and use.
1. Execute setup.sh. It will download the deep speech model and scorer file from git hub.

2. Create build dir inside cloned voice_assistant and execute the following cmd.
   cd voice_assistant
   mkdir build
   cmake ..
   make

To use the generated build please execute the following cmd in build dir itself.

./voiceAssistant -m <deepspeech_model_file> -s <deepspeech_scorer_file> --onnx <onnx_model_file> [-audio <audio_input_speech_file> or -usemic <duration>]

For Example:-

#For using mic
./voiceAssistant -m ../data/deepspeech-0.9.3-models.pbmm -s ../data/deepspeech-0.9.3-models.scorer -onnx ../data/distilbert-squad-128.onnx  -usemic 10

#For using audio file
./voiceAssistant -m ../data/deepspeech-0.9.3-models.pbmm -s ../data/deepspeech-0.9.3-models.scorer -onnx ../data/distilbert-squad-128.onnx  -audio ../data/data_smoke_test_new-home-in-the-stars-16k.wav
