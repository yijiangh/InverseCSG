#include "common/arg_parser.h"
#include <iostream>
#include "common/file_helper.h"

namespace common {

ArgParser::ArgParser() {}

void ArgParser::AddStringArgument(const std::string& flag,
  const std::string& default_value) {
  str_args_[flag] = default_value;
}

void ArgParser::AddIntArgument(const std::string& flag,
  const int default_value) {
  int_args_[flag] = default_value;
}

void ArgParser::AddDoubleArgument(const std::string& flag, const int number,
  const double default_value) {
  AddDoubleArgument(flag, Eigen::VectorXd::Constant(number, default_value));
}

void ArgParser::AddDoubleArgument(const std::string& flag,
  const Eigen::VectorXd& default_value) {
  double_args_[flag] = default_value;
}

void ArgParser::AddBoolArgument(const std::string& flag,
  const bool default_value) {
  bool_args_[flag] = default_value;
}

void ArgParser::Parse(const int argc, const char* argv[]) {
  // Skip the 0th and 1st argument because the 0th is the program name, and the
  // 1st is the mode name.
  int ptr = 2;
  while (ptr < argc) {
    const std::string flag(argv[ptr]);
    if (str_args_.find(flag) != str_args_.end()) {
      str_args_[flag] = std::string(argv[ptr + 1]);
      ptr += 2;
    } else if (int_args_.find(flag) != int_args_.end()) {
      int_args_[flag] = std::stoi(std::string(argv[ptr + 1]));
      ptr += 2;
    } else if (double_args_.find(flag) != double_args_.end()) {
      const int number = static_cast<int>(double_args_.at(flag).size());
      Eigen::VectorXd value(number);
      for (int i = 0; i < number; ++i) {
        value(i) = std::stod(std::string(argv[ptr + 1 + i]));
      }
      double_args_[flag] = value;
      ptr += 1 + number;
    } else if (bool_args_.find(flag) != bool_args_.end()) {
      bool_args_[flag] = true;
      ++ptr;
    } else {
      std::cerr << common::RedHead()
        << "common::ArgParser::Parse: unknown argument: " << flag
        << common::RedTail() << std::endl;
      exit(-1);
    }
  }
}

const std::string ArgParser::GetStringArgument(const std::string& flag) const {
  return str_args_.at(flag);
}

const int ArgParser::GetIntArgument(const std::string& flag) const {
  return int_args_.at(flag);
}

const Eigen::VectorXd ArgParser::GetDoubleArgument(const std::string& flag)
  const {
  return double_args_.at(flag);
}

const bool ArgParser::GetBoolArgument(const std::string& flag) const {
  return bool_args_.at(flag);
}

}
