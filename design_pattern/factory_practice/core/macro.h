#pragma once

namespace practice {

#define STRINGIZE_NX(A) #A
#define STRINIZE(A) STRINGIZE_NX(A)

template <typename R, typename... Args>
class FunctionEntry;


#define ALIAS_FUNC_ENTRY(ItemPtr, ItemConfig, ItemType) \
  using ItemType##FuncEntry = FunctionEntry<ItemPtr, const ItemConfig&>

}  // namespace practice