#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Flower {
  Flower() = default;
  Flower(int flavor) : flavor(flavor) {
  }

  ~Flower() {
    std::cout << "destruct Flower" << std::endl;
  }

  int flavor;
};

struct FlowerContainer {
  FlowerContainer() {
    throw std::runtime_error("constructor exception");
  }
  ~FlowerContainer() {
    std::cout << "destruct FlowerContainer" << std::endl;
  }
  Flower* flower_;
};

class FlowerManager {
 public:
  FlowerManager() : flower_(new Flower()) {
  }
  FlowerManager(int flavor) : flower_(new Flower(flavor)) {
  }
  ~FlowerManager() {
    delete flower_;
    std::cout << "destructor" << std::endl;
  }

  FlowerManager(const FlowerManager& other) {
    std::cout << "copy constructor" << std::endl;
    flower_ = new Flower(other.flower_->flavor);
  }
  FlowerManager(FlowerManager&& other) noexcept {
    std::cout << "move constructor" << std::endl;
    flower_ = other.flower_;
    other.flower_ = nullptr;
  }

  /*
  FlowerManager& operator=(const FlowerManager& other) {
    std::cout << "copy assignment" << std::endl;
    if (this != &other) {
      // delete flower_;
      // flower_ = new Flower(other.flower_->flavor);

      Flower* temp = flower_;
      flower_ = new Flower(other.flower_->flavor);
      delete temp;

      // Flower* temp = new Flower(other.flower_->flavor);
      // delete flower_;
      // flower_ = temp;
    }
    return *this;
  }

  FlowerManager& operator=(FlowerManager&& other) noexcept {
    std::cout << "move assignment" << std::endl;
    if (this != &other) {
      delete flower_;
      flower_ = other.flower_;
      other.flower_ = nullptr;
    }
    return *this;
  }
  */

  FlowerManager& operator=(FlowerManager other) {
    std::swap(flower_, other.flower_);
    return *this;
  }

 private:
  Flower* flower_;
};

class MyContainer {
 public:
  MyContainer(size_t num) : ids_(num, 3), favor_id_(5) {
    std::cout << "constructor" << std::endl;
  }

  int get_favor_id() {
    return favor_id_;
  }

  // ~MyContainer() {
  //   std::cout << "destruct my_container" << std::endl;
  // }

  // MyContainer(const MyContainer& other) {
  //   std::cout << "copy constructor" << std::endl;
  // }
  // MyContainer(MyContainer&& other) noexcept {
  //   std::cout << "move constructor" << std::endl;
  // }

  void print() {
    for (int id : ids_) {
      std::cout << id << ",";
    }
    std::cout << std::endl;
  }

 private:
  std::vector<int> ids_;
  int favor_id_;
  char* word_;
};

void processContainer(MyContainer&& mc) {
  // mc.print();
}

void processContainer(const MyContainer& mc) {
}

template <typename T>
void template_func(T&& t) {
}

FlowerManager create_fm() {
  FlowerManager fm;
  // return std::move(fm);
  return fm;
}

// int main() {
// try {
//     FlowerContainer fc;
//     std::cout << (fc.flower_ == nullptr) << std::endl;
// } catch (std::exception& e) {
//     std::cout << "caught exception, msg: " << e.what() << std::endl;
// }

// FlowerManager fm_1;
// FlowerManager fm_2(2);
// FlowerManager fm_3(fm_1);
// fm_3 = fm_2;
// FlowerManager fm_4(std::move(fm_1));
// fm_4 = std::move(fm_2);
// std::cout << "----seperate----" << std::endl;

// MyContainer mc_1(3);
// mc_1.print();

// MyContainer mc_2(mc_1);
// std::cout << "before move, mc_1 favor_id: " << mc_1.get_favor_id() << std::endl;
// MyContainer mc_3(std::move(mc_1));
// std::cout << "after move, mc_1 favor_id: " << mc_1.get_favor_id() << std::endl;
// mc_1.print();

// processContainer(mc_1);
// processContainer(std::move(mc_1));
// template_func(mc_1);
// template_func(std::move(mc_1));

//   auto result = create_fm();

//   return 0;
// }