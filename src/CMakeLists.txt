cmake_minimum_required(VERSION 3.16)

SET(PROJECT_NAME voiceAssistant)

project(${PROJECT_NAME})

include_directories(../include
                    ../third_party/deep_speech/include
                    ../third_party/sox/include
                    ../third_party/onnx/include)
                    
link_directories(../third_party/deep_speech/lib
                 ../third_party/sox/lib
                 ../third_party/onnx/lib)

add_executable(${PROJECT_NAME} 
               main.cpp
               voice_assistant.cpp
               capture_audio.cpp)
               
target_link_libraries(${PROJECT_NAME}
                     sox
                     onnxruntime
                     deepspeech)
                             
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
