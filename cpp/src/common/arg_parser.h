#ifndef _COMMON_ARG_PARSER_H_
#define _COMMON_ARG_PARSER_H_

#include <string>
#include <unordered_map>
#include "Eigen/Dense"

namespace common {

typedef std::unordered_map<std::string, std::string> string_args_type;
typedef std::unordered_map<std::string, int> int_args_type;
typedef std::unordered_map<std::string, Eigen::VectorXd> double_args_type;
typedef std::unordered_map<std::string, bool> bool_args_type;

class ArgParser {
public:
  ArgParser();

  void AddStringArgument(const std::string& flag,
    const std::string& default_value = "");
  void AddIntArgument(const std::string& flag,
    const int default_value = 0);
  void AddDoubleArgument(const std::string& flag, const int number = 1,
    const double default_value = 0.0);
  void AddDoubleArgument(const std::string& flag,
    const Eigen::VectorXd& default_value);
  void AddBoolArgument(const std::string& flag,
    const bool default_value = false);

  void Parse(const int argc, const char* argv[]);

  // Getter.
  const std::string GetStringArgument(const std::string& flag) const;
  const int GetIntArgument(const std::string& flag) const;
  const Eigen::VectorXd GetDoubleArgument(const std::string& flag) const;
  const bool GetBoolArgument(const std::string& flag) const;

private:
  string_args_type str_args_;
  int_args_type int_args_;
  double_args_type double_args_;
  bool_args_type bool_args_;
};

}

#endif
