#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

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

int main() {
  // try {
  //     FlowerContainer fc;
  //     std::cout << (fc.flower_ == nullptr) << std::endl;
  // } catch (std::exception& e) {
  //     std::cout << "caught exception, msg: " << e.what() << std::endl;
  // }

  FlowerManager fm_1;
  FlowerManager fm_2(2);
  FlowerManager fm_3(fm_1);
  fm_3 = fm_2;
  FlowerManager fm_4(std::move(fm_1));
  fm_4 = std::move(fm_2);

  return 0;
}