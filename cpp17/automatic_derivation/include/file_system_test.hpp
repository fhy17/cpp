#pragma once
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void fileSystemTest() {
    std::cout << __FUNCTION__ << std::endl;
    auto curr_path = fs::current_path();
    std::cout << "curr_path: " << curr_path << std::endl;
    curr_path += "/data";
    std::error_code ec;
    auto res = fs::create_directory(curr_path, ec);

    if (!res) std::cout << "create directory err: " << ec << std::endl;
}