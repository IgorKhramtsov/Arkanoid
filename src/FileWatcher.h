#pragma once
#include <string>
#include <chrono>
#include <functional>
#include <thread>
#include <filesystem>

class FileWatcher
{
public:
  std::string file_path;
  std::filesystem::file_time_type last_modified;
  std::chrono::duration<int, std::milli> delay;

  FileWatcher(std::string fpath_, int del_) : file_path{ fpath_ }, delay{ del_ } {
    last_modified = std::filesystem::last_write_time(file_path);
  }

  void start(const std::function<void ()> &action) {
    auto running = true;
    
    while (running) {
      std::this_thread::sleep_for(delay);

      auto cur_time = std::filesystem::last_write_time(file_path);
      if (last_modified != cur_time) {
        last_modified = cur_time;
        action();
      }

    }
  }


};