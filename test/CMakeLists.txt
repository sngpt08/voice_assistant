cmake_minimum_required(VERSION 3.16)

SET(PROJECT_NAME voiceAssistant_gtest)

project(${PROJECT_NAME})

include_directories(../include/
                    ../third_party/gtest/include/
                    )
                    
link_directories(../third_party/gtest/lib)

add_executable(${PROJECT_NAME} 
               main_test.cpp
               voice_assistant_gtest.cpp
               DS_Stub.cpp
               ../src/voice_assistant.cpp)
               
target_link_libraries(${PROJECT_NAME}
                     pthread
                     gmock
                     gtest)
                             
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
