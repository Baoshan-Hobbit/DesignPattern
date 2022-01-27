#include "design_pattern/factory_practice/impl/general_scorer.h"
#include <iostream>

namespace practice {

GeneralScorer::GeneralScorer(const ScorerConfig& scorer_config) {
  std::cout << "[general scorer] construct" << std::endl;
}

void GeneralScorer::beginRequest() {
  std::cout << "[general scorer] beginRequest" << std::endl;
}

void GeneralScorer::evaluate() {
  std::cout << "[general scorer] evaluate" << std::endl;
}

void GeneralScorer::endRequest() {
  std::cout << "[general scorer] endRequest" << std::endl;
}

}  // namespace practice