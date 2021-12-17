#include <iostream>
#include <string>

void brute_force_search(const std::string &text, const std::string &pattern) {
  size_t text_len = text.size();
  size_t pat_len = pattern.size();

  if (text_len < pat_len) {
    std::cout << "text length is less than pattern length: " << text_len
              << " vs " << pat_len << std::endl;
    return;
  }

  size_t i = 0;
  while (i <= text_len - pat_len) {
    size_t j = 0;
    while (j < pat_len && text[i + j] == pattern[j]) {
      ++j;
    }
    if (j == pat_len) {
      std::cout << "matched at: " << i << std::endl;
    }
    ++i;
  }
}

int main() {
  std::string text = "abcab";
  std::string pattern = "ab";
  brute_force_search(text, pattern);
  return 0;
}