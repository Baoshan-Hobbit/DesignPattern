#pragma once

#include <memory>

namespace practice {

class FeatureInterface {
 public:
  virtual ~FeatureInterface() = default;

  virtual void beginRequest() = 0;
  virtual void evaluate() = 0;
  virtual void endRequest() = 0;
};

using FeaturePtr = std::unique_ptr<FeatureInterface>;

}  // namespace practice