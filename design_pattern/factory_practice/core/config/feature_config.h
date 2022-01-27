#pragma once

#include "design_pattern/factory_practice/3rdparty/json.hpp"

namespace practice {

class FeatureConfig {
  using Json = nlohmann::json;

 public:
  FeatureConfig(const std::string& config_str);

  const std::string& get_feature_name() const {
    return feature_name_;
  }

  const std::vector<std::string>& get_depend_table_names() const {
    return depend_table_names_;
  }

 private:
  std::string feature_name_;
  std::vector<std::string> depend_table_names_;
};

}  // namespace practice