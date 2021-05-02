#include "DS_Mock.h"

extern DS_Mock ds_mock;

int DS_CreateModel(const char* aModelPath, ModelState** retval) {
  return ds_mock.DS_CreateModel(aModelPath,retval);
}
                   
int DS_GetModelSampleRate(const ModelState* aCtx) {
  return ds_mock.DS_GetModelSampleRate(aCtx);
}      

void DS_FreeModel(ModelState* ctx) {
  ds_mock.DS_FreeModel(ctx);
}

int DS_EnableExternalScorer(ModelState* aCtx, const char* aScorerPath) {
  return ds_mock.DS_EnableExternalScorer(aCtx,aScorerPath);
}

int DS_CreateStream(ModelState* aCtx, StreamingState** retval) {
  return ds_mock.DS_CreateStream(aCtx,retval);
}

void DS_FeedAudioContent(StreamingState* aSctx,
                         const short* aBuffer,
                         unsigned int aBufferSize) {
  ds_mock.DS_FeedAudioContent(aSctx,aBuffer,aBufferSize);
}

char* DS_FinishStream(StreamingState* aSctx) {
  return ds_mock.DS_FinishStream(aSctx);
}

void DS_FreeStream(StreamingState* aSctx) {
  ds_mock.DS_FreeStream(aSctx);
}

char* DS_ErrorCodeToErrorMessage(int aErrorCode) {
  return ds_mock.DS_ErrorCodeToErrorMessage(aErrorCode);
}

void DS_FreeString(char* str) {
  ds_mock.DS_FreeString(str);
}
