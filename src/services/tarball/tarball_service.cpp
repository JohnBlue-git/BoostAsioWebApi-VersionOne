#include "tarball_service.hpp"

std::string TarballService::getFileName()
{
  return this->fileName;
}

std::string TarballService::getTmpFileName()
{
  return this->tmpFileName;
}

std::string TarballService::getTmpTarballName()
{
  return this->tmpTarballName;
}

bool TarballService::tmpFile()
{
  std::ifstream ifs(this->getFileName(),
    std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    return false;
  }
  std::ofstream ofs(this->getTmpFileName(),
      std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
  if (!ofs.is_open()) {
      return false;
  }
  ofs << std::string(std::istreambuf_iterator<char>{ifs}, {});
  ofs.close();
  ifs.close();
  return true;
}

bool TarballService::createTarball()
{
  std::string cmdStr = "tar -cpvf " + this->getTmpTarballName() + " " + this->getTmpFileName();
  int ret = std::system(cmdStr.c_str());
  return ret == -1 ? false : true;
}

bool TarballService::isTarball(const std::string& body)
{
  // The minimum size of a tar file is 512 bytes because this is the size of a single tar header block.
  if (body.size() < 512) {
    return false;
  }
  // For POSIX tar files, the magic number is the string "ustar" located at byte offset 257 in the tar header.
  std::string magic = body.substr(257, 5); // This extracts 5 bytes starting at offset 257
  return (magic == "ustar"); // Check for 'ustar' magic number in tar header at the correct position
}

bool TarballService::tmpTarball(const std::string& body)
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

bool TarballService::extarctTarball()
{
  std::string cmdStr = "tar -xpvf " + this->getTmpFileName() + " -C " + this->getTmpTarballName();
  int ret = std::system(cmdStr.c_str());
  return ret == -1 ? false : true;
}

std::string TarballService::getTarball()
{
  std::ifstream ifs(this->getTmpTarballName(),
    std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    return "";
  }
  return std::string(std::istreambuf_iterator<char>{ifs}, {});
}

bool TarballService::deleteTarball()
{
  int ret = std::system("rm -rf ../files/tmp/*");
  return ret == -1 ? false : true;
}