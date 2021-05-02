#ifndef CMD_LINE_PARSER_H
#define CMD_LINE_PARSER_H

#include <string>

namespace cmd_line_parser {

class CmdLineParser {
  
  public:
     
    void ParseCmdLineArgument(int argc,char** argv) {
    
      for (int i=1; i<argc;i=i+2) {
        if (argv[i] == std::string("-m")) {
          model = argv[i+1];
        } else if (argv[i] == std::string("-s")) {
          scorer = argv[i+1];
        } else if (argv[i] == std::string("-onnx")) {
          onnx_model = argv[i+1];
        } else if (argv[i] == std::string("-audio")) {
          audio_file = argv[i+1];
        } else if (argv[i] == std::string("-usemic")) {
          capture_duration = std::stoi(std::string(argv[i+1]));
        }
      }
    }
    
    std::string getInputModelFile() {
      return model;
    }

    std::string getInputScorerFile() {
      return scorer;
    }

    std::string getInputOnnxModelFile() {
      return onnx_model;
    }
    
    std::string getInputSpeechFile() {
      return audio_file;
    }
    
    size_t isMicEnabled() {
      return capture_duration;
    }

  private:
    std::string model;
    std::string scorer;
    std::string onnx_model;
    std::string audio_file;
    size_t capture_duration {0};
};
} //namespace cmd_line_parser
#endif //CMD_LINE_PARSER_H
