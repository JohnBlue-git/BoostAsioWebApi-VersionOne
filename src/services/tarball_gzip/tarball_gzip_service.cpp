#include "tarball_gzip_service.hpp"

std::string TarballGzipService::getFileName()
{
  return this->folder + "/" + this->fileName;
}

std::string TarballGzipService::getTmpFileName()
{
  return this->tmpFolder + "/" + this->fileName;
}

std::string TarballGzipService::getTmpTarballName()
{
  return this->tmpFolder + "/" + this->tarballName;
}

bool TarballGzipService::createTarball()
{
  std::string cmdStr = "tar -cpvzf " + this->getTmpTarballName() + " -C " + this->folder + " " + this->fileName;
  int ret = std::system(cmdStr.c_str());
  // ret == 0 ? true : false;
  return WIFEXITED(ret);
}

bool TarballGzipService::isTarball()
{
  //std::string cmdStr = "file " + this->getTmpTarballName() + " | grep -q gzip && echo 0 || echo 1";
  std::string cmdStr = "file " + this->getTmpTarballName() + " | grep -q gzip";
  int ret = std::system(cmdStr.c_str());
  // WEXITSTATUS extracts the actual return code (0 = found, 1 = not found)
  return WIFEXITED(ret) && WEXITSTATUS(ret) == 0;
}

bool TarballGzipService::tmpTarball(const std::string& body)
{
  std::ofstream ofs(this->getTmpTarballName(),
      std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
  if (!ofs.is_open()) {
      return false;
  }
  ofs << body;
  ofs.close();
  return true;
}

bool TarballGzipService::extarctTarball()
{
  std::string cmdStr = "tar -xpvzf " + this->getTmpTarballName() + " -C " + this->tmpFolder;
  int ret = std::system(cmdStr.c_str());
  return ret == -1 ? false : true;
}

std::string TarballGzipService::getTarball()
{
  std::ifstream ifs(this->getTmpTarballName(),
    std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    return "";
  }
  return std::string(std::istreambuf_iterator<char>{ifs}, {});
}

bool TarballGzipService::deleteTmpFolder()
{
  int ret = std::system("rm -rf ../files/tmp/*");
  // ret == 0 ? true : false;
  return WIFEXITED(ret);
}