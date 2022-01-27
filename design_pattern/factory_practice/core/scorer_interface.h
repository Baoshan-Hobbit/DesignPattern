#pragma once

#include <memory>

namespace practice {

class ScorerInterface {
 public:
  virtual ~ScorerInterface() = default;

  virtual void beginRequest() = 0;
  virtual void evaluate() = 0;
  virtual void endRequest() = 0;
};

using ScorerPtr = std::unique_ptr<ScorerInterface>;

}  // namespace practice