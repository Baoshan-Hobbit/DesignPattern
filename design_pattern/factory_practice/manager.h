#pragma once

#include "design_pattern/factory_practice/core/feature_interface.h"
#include "design_pattern/factory_practice/core/config/feature_config.h"
#include <unordered_map>

namespace practice {

class FeatureManager {
 public:
   FeatureManager(const std::vector<FeatureConfig>& feature_configs);
   FeatureInterface* find(const std::string& feature_name);

 private:
  std::unordered_map<std::string, std::unique_ptr<FeatureInterface>> feature_table_;
};

}  // namespace practice