#pragma once

#include <string>
#include <filesystem>

class Path {
  public:
    Path(char* arg) {
      str = std::filesystem::weakly_canonical(
          std::filesystem::path(arg)).parent_path();
    }

    ~Path() {}

    std::string append(std::string input) {
      return str.string().append(input);
    }
  private:
    std::filesystem::path str;
};