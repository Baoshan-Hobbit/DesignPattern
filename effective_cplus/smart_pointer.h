#include <memory>

/*
* 参考文档：
* 1. https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/
*/


namespace smart_pointer {

struct Base {
  Base() = default;
  virtual ~Base() = default; // 必须是 virtual, 否则子类的析构函数不会调用

  int a_ = 2;
};
struct Derived : public Base {
  Derived();
  ~Derived();
};

/*
 * resource 的生命周期由 manager 管理, manager 析构, resource 随之析构
*/
class UniqueResourceManager {
 public:
  UniqueResourceManager(std::unique_ptr<Base> resource) : resource_(std::move(resource)) {}
  Base* get_raw_resource() {
    return resource_.get();
  }

 private:
  std::unique_ptr<Base> resource_;
};

/*
 * resource 的生命周期长于 manager, 可以赋值给其他的 manager, 等引用计数变为 0 时才析构
 * 应用场景：
 * 1. 多个线程之间引用同一个资源，主线程 manager 对象析构，但 resource 仍然存在，可由子线程的 manager 对象继续访问
*/ 
class SharedResourceManager {
 public:
  SharedResourceManager(const std::shared_ptr<Base>& resource) : resource_(resource) {}
  std::shared_ptr<Base> get_resource_ptr() {
    return resource_;
  }
  Base* get_raw_resource() {
    return resource_.get();
  }

 private:
  std::shared_ptr<Base> resource_;
};

// ============ smart pointer as local variable =============
void local_unique_ptr();
// ==========================================================


// ============ smart pointer as function param =============
/* possible null param
 * 因为函数是我实现的，用户只需要调用。我知道传进来的是指向资源的指针，
 * 我不会故意去 delete 它，管理它的生命周期，我只是去使用它。
 * 因为是传入指针，值传递，函数体内的指针是实参指针的拷贝，出了函数体，这个指针就消失了，
 * 我不作死 delete 就没问题
*/
void update_by_pointer(Base* ptr); // may change resource
void read_by_pointer(const Base* ptr); // won't change resource

// not possible null param
void update_by_ref(Base& base);
void read_by_ref(const Base& base);

/*
 * 将所有权转移到函数内部，unique_ptr 只支持移动构造
 */
void sink(std::unique_ptr<Base> ptr);

/*
 * 改变传入 unique_ptr 的所有权
*/
void modify_unique_ownership(std::unique_ptr<Derived>& ptr);
void bad(const std::unique_ptr<Derived>& ptr); // use const Base* or const Base& instead

/*
 * 共享所有权，通过拷贝构造的方式，引用计数 +1
*/
void share_ownership(std::shared_ptr<Base> ptr);

/*
 * 不确定该函数是否会共享所有权，使用 const ref, 不增加引用计数
*/
void maybe_inner_share_ownership(const std::shared_ptr<Derived>& ptr);

/*
 * 改变传入 shared_ptr 的所有权
*/
void modify_shared_ownership(std::shared_ptr<Derived>& ptr);
// ==========================================================


// ============ smart pointer as function return value =============
/*
 * 函数返回一个指针类型的对象，该对象在函数返回之后仍然存在，即生命周期长于函数，不由该函数
 * 管理，因此返回智能指针。若该资源所有权唯一，使用 unique_ptr，否则使用 shared_ptr
*/
std::unique_ptr<Base> get_unique_ptr();
std::shared_ptr<Base> get_shared_ptr();
// ==========================================================


// ============ smart pointer as class member =============

// ==========================================================
} // namespace smart_pointer