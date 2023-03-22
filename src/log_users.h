#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>
#include <filesystem>

#include "observer.h"

class FileLogger : public IObserver {
public:
    FileLogger() = default;

    FileLogger(std::filesystem::path path) :
        _path(path)
    {};

    void UpdateEnd(const std::string& comands) override {
        if(!_cur_file) {
            return;
        }
        (*_cur_file) << comands << std::endl;
    }

    void UpdateStart() override {
        std::time_t t = std::time(nullptr);
        std::string cur_time = std::to_string(t);
        if(!_path.empty()) {
            std::filesystem::create_directories(_path);
        }
        _cur_file = std::make_unique<std::ofstream>(_path.string() + cur_time + ".log");
    }

private:
   std::unique_ptr<std::ofstream> _cur_file;
   std::filesystem::path _path;
};


class OstreamLogger : public IObserver {
public:
    OstreamLogger()
        :_out(std::cout)
    {}

    OstreamLogger(std::ostream& out)
        :_out(out)
    {}

    void UpdateEnd(const std::string& comands) override {
        _out << comands << std::endl;
    }

private:
    std::ostream& _out;
};
