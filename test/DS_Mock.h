#ifndef DS_MOCK_H
#define DS_MOCK_H

#include "gmock/gmock.h"
#include "deepspeech.h"

class DS_Mock {

public:
  ~DS_Mock() = default;
  MOCK_METHOD2(DS_CreateModel,int (const char*, ModelState** ));
                   
  MOCK_METHOD1(DS_GetModelSampleRate,int(const ModelState* ));

  MOCK_METHOD1(DS_FreeModel,void(ModelState* )); 

  MOCK_METHOD2(DS_EnableExternalScorer,int(ModelState* , const char* ));

  MOCK_METHOD2(DS_CreateStream,int(ModelState* aCtx, StreamingState** ));

  MOCK_METHOD3(DS_FeedAudioContent,void(StreamingState* ,const short* ,unsigned int ));

  MOCK_METHOD1(DS_FinishStream,char*(StreamingState* ));

  MOCK_METHOD1(DS_FreeStream,void(StreamingState*));

  MOCK_METHOD1(DS_ErrorCodeToErrorMessage,char*(int));

  MOCK_METHOD1(DS_FreeString,void(char* str));
};
#endif //DS_MOCK_H
