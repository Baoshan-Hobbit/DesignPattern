#pragma once

#include "design_pattern/factory_practice/core/macro.h"
#include <memory>

namespace practice {

class FeatureInterface;
using FeaturePtr = std::unique_ptr<FeatureInterface>;

class FeatureConfig;


ALIAS_FUNC_ENTRY(FeaturePtr, FeatureConfig, Feature);

}  // namespace practice