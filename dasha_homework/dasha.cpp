#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

class TagMatcher {
public:
  TagMatcher() : counter_(0), opening_tag_length_(0), opening_tag_(NULL) {}

  TagMatcher(const char *tag) : TagMatcher() {
    opening_tag_ = tag;
    opening_tag_length_ = strlen(tag);
  }

  bool IsTagMatched(char current_char) {
    if (current_char == opening_tag_[counter_]) {
      counter_++;
    } else {
      counter_ = 0;
    }
    if (counter_ == opening_tag_length_) {
      return true;
    }
    return false;
  }

  bool TagEnds(char current_char) {}

  bool LinkEnds(char current_char) {
    if (current_char == '\"') {
      return true;
    }
    return false;
  }

private:
  int counter_;
  const char *opening_tag_;
  size_t opening_tag_length_;
};

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");
  char current_char;
  bool is_link = false;
  int link_counter = 0;
  // "\" so that c++ understands it's a part of the text;
  TagMatcher tag_matcher("<a href=\"");
  while (in.get(current_char)) {
    if (is_link && tag_matcher.LinkEnds(current_char)) {
      link_counter++;
      is_link = false;
      cout << endl;
      continue;
    }
    if (is_link) {
      cout << current_char;
      continue;
    }
    if (!tag_matcher.IsTagMatched(current_char)) {
      is_link = false;
      continue;
    }
    is_link = true;

    // Once we find a quote, we check if the tag gets closed.
    // If it is not closed - print out - malformed html input file.
  }

  cout << link_counter << endl;

  return 0;
}
