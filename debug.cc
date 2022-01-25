#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>

struct Info {
  std::string term;

  Info() = default;
  ~Info() = default;

  Info(const Info& other) {
    std::cout << "copy constructor" << std::endl;
  }
  Info(Info&& other) = default;
  Info& operator=(const Info& other) = default;
  Info& operator=(Info&& other) = default;
};

struct Context : public std::enable_shared_from_this<Context> {
 public:
  // Context(const std::shared_ptr<Info>& info_ptr): info_ptr_(info_ptr) {}
  Context() = default;
  ~Context() = default;

  std::shared_ptr<Context> get_shared_ptr() {
    return shared_from_this();
  }

  std::shared_ptr<const Context> get_shared_ptr() const {
    return shared_from_this();
  }

  void do_nothing() {
    std::cout << "[tid] " << std::this_thread::get_id() << std::endl;
  }

//  private:
//   std::shared_ptr<Info> info_ptr_;
};

void test_push_back_ref(const Info& info) {
  // lambda param accept reference by only use "&"
  // 如果结构体巨大，需要传 const &, 记得先定义 const & 然后再传给 lambda 表达式
  auto func = [&info]() {
    std::vector<Info> infos;
    infos.push_back(info);
  };
  func();
}

void use_ref_func(Context& ctx) {
  auto another_ptr = ctx.get_shared_ptr();
  auto func = [another_ptr]() {
    auto inner_func = [another_ptr]() {};
    std::thread t2(inner_func);
    t2.detach();
  };
  std::thread t(func);
  t.detach();
}

void test_async_shared_ptr() {
  auto context_ptr = std::make_shared<Context>();
  use_ref_func(*context_ptr);
}


int main() {
  test_async_shared_ptr();
//   Info info;
//   info.term = "hello";
//   test_push_back_ref(info);

//   return 0;
}