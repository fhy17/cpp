// #include "file_system_test.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <assert.h>

namespace fs = std::filesystem;

int main() {
    // 判断文件夹是否存在
    std::string dir_name("test");
    fs::path url(dir_name);
    if (!fs::exists(url)) {
        std::cout << std::quoted(dir_name) << " is not exist" << std::endl;
    } else {
        std::cout << std::quoted(dir_name) << " is exist" << std::endl;
    }

    // 创建单层目录
    bool okey = fs::create_directory(dir_name);
    std::cout << "create_directory(" << std::quoted(dir_name) << "), result=" << okey << std::endl;

    // 逐级创建多层目录
    std::error_code err;
    std::string sub_dir = dir_name + "/subdir";
    okey = fs::create_directory(sub_dir, err);
    std::cout << "create_directory(" << std::quoted(sub_dir) << "), result=" << okey << std::endl;
    std::cout << "err.value()=" << err.value() << " err.message()=" << err.message() << std::endl;

    // 创建多级目录
    dir_name = "a/b//c/d/";
    okey = fs::create_directories(dir_name, err);
    std::cout << "create_directories(" << std::quoted(dir_name) << "), result=" << okey << std::endl;
    std::cout << "create_directories, err.value()=" << err.value() << " err.message()=" << err.message() << std::endl;

    //<5> 当前文件路径
    fs::path current_path = fs::current_path();                                      // C:\Users\Kandy\Desktop\fs\fs
    std::cout << "currentPath:\t" << current_path << std::endl;                      // 当前路径
    std::cout << "root_directory:\t" << current_path.root_directory() << std::endl;  // 根目录
    std::cout << "relative_path:\t" << current_path.relative_path() << std::endl;    // 相对路径
    std::cout << "root_name:\t" << current_path.root_name() << std::endl;            // 根名
    std::cout << "root_path:\t" << current_path.root_path() << std::endl;            // 根路径

    //<6> 创建文件"from.dat"
    fs::path old_path(fs::current_path() / "from.dat");
    std::fstream file(old_path, std::ios::out | std::ios::trunc);
    if (!file) {
        std::cout << "create file(" << old_path.string() << ") failed!" << std::endl;
    }
    file.close();

    //<7> 获取相对于base的绝对路径
    fs::path abs_path = fs::absolute(old_path /*, fs::current_path()*/);
    std::cout << "abs path=" << abs_path.string()
              << std::endl;  //"C:\Users\Kandy\Desktop\filesystem\filesystem\from.dat"

    //<8> 文件拷贝
    fs::create_directories(fs::current_path() / "to");
    fs::path to_path(fs::current_path() / "to/from0.dat");
    fs::copy(old_path, to_path);

    //<9> 移动文件或重命名
    fs::path new_path(fs::current_path() / "to/to.dat");
    fs::rename(old_path, new_path);

    //<10> 创建文件 "example.dat"
    fs::path _path = fs::current_path() / "example.dat";
    std::cout << "example.dat path:" << std::quoted(_path.string()) << std::endl;
    std::ofstream(_path).put('a');  // create file of size 1
    std::ofstream(_path).close();

    // 文件类型判定
    assert(fs::file_type::regular == fs::status(_path).type());

    //<11> 获取文件大小
    auto size = fs::file_size(_path);
    std::cout << "file_size=" << size << std::endl;

    //<12> 获取文件最后修改时间
    auto time = fs::last_write_time(_path);
    std::cout << "last_write_time=" << time.time_since_epoch().count() << std::endl;

    //<13> 删除文件
    okey = fs::remove(_path);
    std::cout << "remove(" << std::quoted(_path.string()) << ")" << okey << std::endl;

    //<14> 递归删除目录下所有文件,返回被成功删除的文件个数
    uintmax_t count = fs::remove_all(dir_name);  // dirName="a/b//c/d/",会把d目录也删掉
    std::cout << "remove_all(" << std::quoted(dir_name) << ")" << count << std::endl;
    fs::remove_all(fs::current_path().string() + "/" + "to");

    //<15> 在临时文件夹下创建文件夹并删除
    fs::path tmp = fs::temp_directory_path();  //"C:\Users\Kandy\AppData\Local\Temp\"
    std::cout << "temp_directory_path=" << std::quoted(tmp.string()) << std::endl;
    fs::create_directories(tmp / "_abcdef/example");
    std::uintmax_t n = fs::remove_all(tmp / "_abcdef");
    std::cout << "Deleted " << n << " files or directories" << std::endl;
}