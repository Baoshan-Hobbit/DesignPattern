#include "design_pattern/factory_practice/core/config/scorer_config.h"

namespace practice {

ScorerConfig::ScorerConfig(const std::string& config_str) {
  auto json_params = Json::parse(config_str);
  json_params.at({"generators"}).get_to(generator_names_);
  json_params.at({"functions"}).get_to(function_names_);
}

}  // namespace practice