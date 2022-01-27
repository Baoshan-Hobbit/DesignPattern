#pragma once

#include "design_pattern/factory_practice/3rdparty/json.hpp"

namespace practice {

class ScorerConfig {
  using Json = nlohmann::json;

 public:
  ScorerConfig(const std::string& config_str);

  const std::vector<std::string>& get_generator_names() const {
    return generator_names_;
  }

  const std::vector<std::string>& get_function_names() const {
    return function_names_;
  }

 private:
  // if well defined then no json member needed, or json member needed
  std::vector<std::string> generator_names_;
  std::vector<std::string> function_names_;
};

}  // namespace practice