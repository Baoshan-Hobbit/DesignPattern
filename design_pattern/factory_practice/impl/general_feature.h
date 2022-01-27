#pragma once

#include "design_pattern/factory_practice/core/feature_interface.h"
#include "design_pattern/factory_practice/core/config/feature_config.h"

namespace practice {

class GeneralFeature : public FeatureInterface {
 public:
  GeneralFeature(const FeatureConfig& feature_config);
  virtual ~GeneralFeature() = default;

  virtual void beginRequest() override;
  virtual void evaluate() override;
  virtual void endRequest() override;
};

}  // namespace practice