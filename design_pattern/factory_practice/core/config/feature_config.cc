#include "design_pattern/factory_practice/core/config/feature_config.h"

namespace practice {

FeatureConfig::FeatureConfig(const std::string& config_str) {
  auto json_params = Json::parse(config_str);
  json_params.at("feature").get_to(feature_name_);
  json_params.at("depend_tables").get_to(depend_table_names_);
}

}  // namespace practice