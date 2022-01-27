#pragma once

#include "design_pattern/factory_practice/core/scorer_interface.h"
#include "design_pattern/factory_practice/core/config/scorer_config.h"

namespace practice {

class GeneralScorer : public ScorerInterface {
 public:
  GeneralScorer(const ScorerConfig& scorer_config);
  virtual ~GeneralScorer() = default;

  virtual void beginRequest() override;
  virtual void evaluate() override;
  virtual void endRequest() override;
};

}  // namespace practice