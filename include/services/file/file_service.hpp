#pragma once

#include <fstream>
#include <string>

class FileService {
private:
  std::string fileName = "../files/data.json";

public:
  std::string getFile();
  std::string getFileName();
};