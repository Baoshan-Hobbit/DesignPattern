#include <iostream>
#include <memory>
#include <string>

#include "effective_cplus/demo.h"
#include "effective_cplus/inheritage.h"
#include "effective_cplus/smart_pointer.h"

#include "design_pattern/factory_practice/impl/general_feature.h"

class Resource {
 public:
  int a_;
};
using ResourcePtr = std::shared_ptr<Resource>;

void set_resource(const ResourcePtr& resource_ptr) {
  resource_ptr->a_ = 5;
}

void test_confused_resource() {
  auto resource_ptr = std::make_shared<Resource>();
  std::cout << resource_ptr->a_ << std::endl;
  set_resource(resource_ptr);
  std::cout << resource_ptr->a_ << std::endl;
}

void test_string() {
  std::u32string str = U"hello中国";
  std::cout << str.c_str() << std::endl;
}

void test_inheritage() {
  std::unique_ptr<Interface> interface_ptr(new Specific());
  interface_ptr->pipeline();
  interface_ptr->common_api_func();
}

void test_smart_pointer() {
  using namespace smart_pointer;

  // local_unique_ptr();

  // auto base_ptr = std::make_unique<Derived>();
  // auto derived_ptr = std::make_unique<Derived>();

  // update_by_pointer(base_ptr.get());
  // read_by_pointer(base_ptr.get());
  // update_by_pointer(nullptr);

  // update_by_ref(*base_ptr);
  // read_by_ref(*base_ptr);

  // sink(std::move(base_ptr));
  // modify_unique_ownership(derived_ptr);
  // bad(derived_ptr);

  // auto shared_base_ptr = std::make_shared<Derived>();
  // auto shared_derived_ptr = std::make_shared<Derived>();

  // share_ownership(shared_base_ptr);
  // maybe_inner_share_ownership(shared_derived_ptr);
  // modify_shared_ownership(shared_derived_ptr);

  auto unique_ptr = get_unique_ptr();
  auto shared_ptr = get_shared_ptr();

  UniqueResourceManager uniq_res_manager{std::move(unique_ptr)};
  smart_pointer::Base* resource = uniq_res_manager.get_raw_resource();

  SharedResourceManager shared_res_manager{shared_ptr};
  std::shared_ptr<smart_pointer::Base> shared_res_ptr = shared_res_manager.get_resource_ptr();
  smart_pointer::Base* another_resource = shared_res_manager.get_raw_resource();
}

void test_config() {
  using namespace practice;
  
  std::string config = R"({
    "feature": "general",
    "depend_tables": ["table_a", "table_b"]
    })";

  FeatureConfig feature_conf(config);
  // std::cout << feature_conf.get_feature_name() << std::endl;
  // std::cout << feature_conf.get_depend_table_names()[0] << std::endl;
  GeneralFeature general_feature(feature_conf);
  general_feature.beginRequest();
  general_feature.evaluate();
  general_feature.endRequest();
}


int main() {
  // test_confused_resource();
  // test_string();
  // print();

  // test_inheritage();

  // test_smart_pointer();
  test_config();

  return 0;
}