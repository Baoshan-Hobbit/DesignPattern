#include "design_pattern/factory_practice/manager.h"
#include <stdexcept>
#include "design_pattern/factory_practice/registry.h"

namespace practice {

FeatureManager::FeatureManager(const std::vector<FeatureConfig>& feature_configs) {
  using FeatureFuncEntry = FunctionEntry<FeaturePtr, const FeatureConfig&>;
  for (const auto& feature_config : feature_configs) {
    const std::string& feature_name = feature_config.get_feature_name();
    auto creator_ptr = Registry<FeatureFuncEntry>::get_instance()->find(feature_name);
    if (feature_table_.count(feature_name)) {
      throw std::runtime_error("[init] conf: Duplicated feature name config!");
    }
    if (creator_ptr) {
      feature_table_[feature_name] = (*creator_ptr)(feature_config);
    }
  }
}

FeatureInterface* FeatureManager::find(const std::string& feature_name) {
  auto iter = feature_table_.find(feature_name);
  if (iter != feature_table_.end()) {
    return iter->second.get();
  }
  return nullptr;
}

}  // namespace practice