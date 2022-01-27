#include "design_pattern/factory_practice/impl/general_feature.h"
#include "design_pattern/factory_practice/registry.h"
#include <iostream>

namespace practice {

/*
using FeatureFuncEntry = FunctionEntry<FeaturePtr, const FeatureConfig&>;
const FeatureFuncEntry& func_entry_GeneralFeature = Registry<FeatureFuncEntry>::get_instance()
                                                          ->register_func("GeneralFeature")
                                                          .set_func([](const FeatureConfig& feature_config) -> FeaturePtr {
                                                            return std::make_unique<GeneralFeature>(feature_config);
                                                          });
*/

REGISTER_GLOBAL(FeaturePtr, FeatureConfig, Feature, GeneralFeature);

GeneralFeature::GeneralFeature(const FeatureConfig& feature_config) {
  std::cout << "[general feature] construct" << std::endl;
}

void GeneralFeature::beginRequest() {
  // build context: session-level context or context used by this class
  std::cout << "[general feature] beginRequest" << std::endl;
}

void GeneralFeature::evaluate() {
  // major work is done here
  std::cout << "[general feature] evaluate" << std::endl;
}

void GeneralFeature::endRequest() {
  // optional: 
  // - clear context used by this class, may save memory?
  // - dump metric collected by evaluate
  std::cout << "[general feature] endRequest" << std::endl;
}

}  // namespace practice