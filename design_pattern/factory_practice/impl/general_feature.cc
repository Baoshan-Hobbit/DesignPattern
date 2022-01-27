#include "design_pattern/factory_practice/impl/general_feature.h"
#include "design_pattern/factory_practice/registry.h"
#include <iostream>

namespace practice {

const FunctionEntry& func_entry = Registry<FunctionEntry>::get_instance()
                                                          ->register_func("GeneralFeature")
                                                          .set_func([](const FeatureConfig& feature_config) -> FeaturePtr {
                                                            return std::make_unique<GeneralFeature>(feature_config);
                                                          });

const FunctionEntry& func_entry_2 = Registry<FunctionEntry>::get_instance()
                                                          ->register_func("GeneralFeature2")
                                                          .set_func([](const FeatureConfig& feature_config) -> FeaturePtr {
                                                            return std::make_unique<GeneralFeature>(feature_config);
                                                          });

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