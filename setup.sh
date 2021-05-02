#!/bin/bash
wget -P ./data/ https://github.com/mozilla/DeepSpeech/releases/download/v0.9.3/deepspeech-0.9.3-models.scorer
if [[ $? -ne 0 ]]; then
    echo "wget failed for deepspeech-0.9.3-models.scorer"
    exit 1; 
fi


wget -P ./data/ https://github.com/mozilla/DeepSpeech/releases/download/v0.9.3/deepspeech-0.9.3-models.pbmm
if [[ $? -ne 0 ]]; then
    echo "wget failed deepspeech-0.9.3-models.pbmm"
    exit 1; 
fi
