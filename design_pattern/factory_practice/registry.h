#pragma once

#include "design_pattern/factory_practice/core/feature_interface.h"
#include "design_pattern/factory_practice/core/config/feature_config.h"
#include <iostream>

namespace practice {

template <typename R, typename... Args>
class FunctionEntry {
  using FuncType = std::function<R(Args...)>;

 public:
  ~FunctionEntry() {
    std::cout << "[func_entry] destructor" << std::endl;
  }
  FunctionEntry& set_func(const FuncType& func) {
    func_ = func;
    return *this;
  }
  const FuncType& get_func() const {
    return func_;
  }

 private:
  FuncType func_;
};

template <typename EntryType>
class Registry {
  using EntryPtr = std::unique_ptr<EntryType>;

 public:
  Registry(const Registry&) = delete;
  Registry& operator=(const Registry&) = delete;
  Registry(Registry&&) = delete;
  Registry& operator=(Registry&&) = delete;

  static Registry* get_instance();
  EntryType& register_func(const std::string& name);
  EntryType* find(const std::string& name);

 private:
  Registry() = default;

 private:
  std::unordered_map<std::string, EntryPtr> func_table_;
};

template <typename EntryType>
Registry<EntryType>* Registry<EntryType>::get_instance() {
  static Registry<EntryType> instance;
  return &instance;
}

template <typename EntryType>
EntryType& Registry<EntryType>::register_func(const std::string& name) {
  func_table_[name] = std::make_unique<EntryType>();
  return *(func_table_[name]);
}

template <typename EntryType>
EntryType* Registry<EntryType>::find(const std::string& name) {
  auto iter = func_table_.find(name);
  if (iter != func_table_.end()) {
    return (iter->second).get();
  }
  return nullptr;
}

#define STRINGIZE_NX(A) #A
#define STRINIZE(A) STRINGIZE_NX(A)

#define REGISTER_GLOBAL(ItemPtr, ItemConfig, ItemType, ItemName) \
  using ItemType##FuncEntry = FunctionEntry<ItemPtr, const ItemConfig&>; \
  const ItemType##FuncEntry& func_entry_##ItemName = Registry<ItemType##FuncEntry>::get_instance() \
                                                            ->register_func(STRINIZE(ItemName)) \
                                                            .set_func([](const ItemConfig& item_config) -> ItemPtr { \
                                                              return std::make_unique<ItemName>(item_config); \
                                                            })
}  // namespace practice