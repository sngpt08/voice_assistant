#include "gtest/gtest.h"
#include "voice_assistant.h"
#include "DS_Mock.h"

#include <string>

using namespace voice_assistant;
using ::testing::AtLeast;

DS_Mock ds_mock;

class VoiceAssistantTest: public ::testing::Test  {
public:
  void SetUp() {  
  }

  void TearDown() { 
  }
};


TEST(VoiceAssistantTest, VA_CreateModel_return_success) {
 VoiceAssistant va;
 std::string model_file("model_file");
 EXPECT_CALL(ds_mock,DS_CreateModel(testing::_,testing::_)).Times(1)
                                                           .WillOnce(testing::Return(0));
 VA_RetrunValue retVal = va.VA_CreateModel(model_file.c_str());
 EXPECT_EQ(0,retVal.error_code);
}

TEST(VoiceAssistantTest, VA_CreateModel_return_failure) {
 VoiceAssistant va;
 std::string model_file("model_file");
 std::string message("Error in Creating Model");
 EXPECT_CALL(ds_mock,DS_CreateModel(testing::_,testing::_)).Times(1)
                                                           .WillOnce(testing::Return(1));
 EXPECT_CALL(ds_mock,DS_ErrorCodeToErrorMessage(testing::_)).Times(1)
                                                           .WillOnce(testing::Return(const_cast<char*>(message.c_str())));
 VA_RetrunValue retVal = va.VA_CreateModel(model_file.c_str());
 EXPECT_EQ(1,retVal.error_code);
 EXPECT_EQ(message,retVal.message);
}

TEST(VoiceAssistantTest, VA_EnableExternalScorer_return_success) {
 VoiceAssistant va;
 std::string scorer_file("scorer_file");
 EXPECT_CALL(ds_mock,DS_EnableExternalScorer(testing::_,testing::_)).Times(1)
                                                           .WillOnce(testing::Return(0));
 VA_RetrunValue retVal = va.VA_EnableExternalScorer(scorer_file.c_str());
 EXPECT_EQ(0,retVal.error_code);
}

TEST(VoiceAssistantTest, VA_EnableExternalScorer_return_failure) {
 VoiceAssistant va;
 std::string scorer_file("scorer_file");
 std::string message("Error in enabling external scorer");
 EXPECT_CALL(ds_mock,DS_EnableExternalScorer(testing::_,testing::_)).Times(1)
                                                           .WillOnce(testing::Return(1));
 EXPECT_CALL(ds_mock,DS_ErrorCodeToErrorMessage(testing::_)).Times(1)
                                                           .WillOnce(testing::Return(const_cast<char*>(message.c_str())));
                                                           
 EXPECT_CALL(ds_mock,DS_FreeModel(testing::_)).Times(1);
 VA_RetrunValue retVal = va.VA_EnableExternalScorer(scorer_file.c_str());
 EXPECT_EQ(1,retVal.error_code);
 EXPECT_EQ(message,retVal.message);
}

TEST(VoiceAssistantTest, VA_GetSampleRate) {
 VoiceAssistant va;
 EXPECT_CALL(ds_mock,DS_GetModelSampleRate(testing::_)).Times(1).WillOnce(testing::Return(16000));
 size_t retVal = va.VA_GetSampleRate();
 EXPECT_EQ(16000,retVal);
}

TEST(VoiceAssistantTest, VA_CreateStream_return_success) {
 VoiceAssistant va;
 std::string scorer_file("scorer_file");
 EXPECT_CALL(ds_mock,DS_CreateStream(testing::_,testing::_)).Times(1)
                                                           .WillOnce(testing::Return(0));
 VA_RetrunValue retVal = va.VA_CreateStream();
 EXPECT_EQ(0,retVal.error_code);
}

TEST(VoiceAssistantTest, VA_CreateStream_return_failure) {
 VoiceAssistant va;
 std::string message("Error in creating stream");
 EXPECT_CALL(ds_mock,DS_CreateStream(testing::_,testing::_)).Times(1)
                                                           .WillOnce(testing::Return(1));
 EXPECT_CALL(ds_mock,DS_ErrorCodeToErrorMessage(testing::_)).Times(1)
                                                           .WillOnce(testing::Return(const_cast<char*>(message.c_str())));
                                                           
 EXPECT_CALL(ds_mock,DS_FreeModel(testing::_)).Times(1);
 VA_RetrunValue retVal = va.VA_CreateStream();
 EXPECT_EQ(1,retVal.error_code);
 EXPECT_EQ(message,retVal.message);
}

TEST(VoiceAssistantTest, VA_FeedAudioContent) {
 VoiceAssistant va;
 std::string scorer_file("scorer_file");
 EXPECT_CALL(ds_mock,DS_FeedAudioContent(testing::_,testing::_,testing::_)).Times(1);
 size_t buffer_size = 2;
 short int inputAudioBuffer[2];
 va.VA_FeedAudioContent(inputAudioBuffer,buffer_size);
}

TEST(VoiceAssistantTest, VA_FinishStream) {
 VoiceAssistant va;
 std::string output_text("Hi I am good.");
 EXPECT_CALL(ds_mock,DS_FinishStream(testing::_)).Times(1).WillOnce(testing::Return(const_cast<char*>(output_text.c_str())));
 EXPECT_CALL(ds_mock,DS_FreeString(testing::_)).Times(1);
 std::string retVal = va.VA_FinishStream();
 EXPECT_EQ(retVal,output_text); 
}

