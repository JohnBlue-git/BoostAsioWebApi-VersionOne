#include "file_service.hpp"

std::string FileService::getFile()
{
  std::ifstream ifs(this->getFileName(),
    std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    return "";
  }
  return std::string(std::istreambuf_iterator<char>{ifs}, {});
}

std::string FileService::getFileName()
{
  return this->fileName;
}
