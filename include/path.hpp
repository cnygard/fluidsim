#pragma once

#include <string>
#include <filesystem>

class Path {
  private:
    Path(char* arg) {
      str = std::filesystem::weakly_canonical(
          std::filesystem::path(arg)).parent_path();
    }

    static Path* path;
    std::filesystem::path str;

  public:
    // NO COPIES
    Path(const Path& obj) = delete;

    // Retrieve path*
    static Path* get(char* arg) {
      if (path == NULL) {
        path = new Path(arg);
      }
      return path;
    }

    std::string append(std::string input) {
      return str.string().append(input);
    }
};
