#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

int LongestSeqBroot(const std::string &sequence) {
  int longest_seq_length{};
  int current_start_idx{};
  for (int i = 0; i < sequence.size(); ++i) {
    for (int j = current_start_idx; j < i; ++j) {
      if (sequence[j] == sequence[i]) {
        longest_seq_length =
            std::max(longest_seq_length, i - current_start_idx);
        current_start_idx = j + 1;
        break;
      }
    }
  }
  longest_seq_length =
      std::max(longest_seq_length,
               static_cast<int>(sequence.size()) - current_start_idx);
  return longest_seq_length;
}

int LongestSeq(const std::string &sequence) {
  std::unordered_map<char, int> char_position_buffer{};
  int current_start_idx{};
  int longest_seq_length{};
  for (int i = 0; i < sequence.length(); ++i) {
    if (char_position_buffer.count(sequence[i]) > 0) {
      int previous_pos = char_position_buffer.at(sequence[i]);
      if (previous_pos >= current_start_idx) {
        longest_seq_length =
            std::max(longest_seq_length, i - current_start_idx);
        current_start_idx = previous_pos + 1;
      }
    }
    char_position_buffer[sequence[i]] = i;
  }
  longest_seq_length =
      std::max(longest_seq_length,
               static_cast<int>(sequence.size()) - current_start_idx);
  return longest_seq_length;
}

int main(int argc, char const *argv[]) {
  std::cout << "Longest seq: " << LongestSeqBroot("") << std::endl;
  std::cout << "Longest seq: " << LongestSeqBroot("aaaaa") << std::endl;
  std::cout << "Longest seq: " << LongestSeqBroot("abcd") << std::endl;
  std::cout << "----------------------------------------------------\n";
  std::cout << "Longest seq: " << LongestSeq("") << std::endl;
  std::cout << "Longest seq: " << LongestSeq("aaaaa") << std::endl;
  std::cout << "Longest seq: " << LongestSeq("abcd") << std::endl;
  return 0;
}
