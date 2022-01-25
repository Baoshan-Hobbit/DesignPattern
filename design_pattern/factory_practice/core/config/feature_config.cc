#include "design_pattern/factory_practice/core/config/feature_config.h"

namespace practice {

FeatureConfig::FeatureConfig(const std::string& config) {
  auto json_params = Json::parse(config);
  feature_name_ = json_params.at("feature_name").get_to(feature_name_);
  depend_tables_ = json_params.at("depend_tables").get_to(depend_tables_);
}

}  // namespace practice