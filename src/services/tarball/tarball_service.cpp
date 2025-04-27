#include "tarball_service.hpp"

std::string TarballService::getFileName()
{
  return this->folder + "/" + this->fileName;
}

std::string TarballService::getTmpFileName()
{
  return this->tmpFolder + "/" + this->fileName;
}

std::string TarballService::getTmpTarballName()
{
  return this->tmpFolder + "/" + this->tarballName;
}

bool TarballService::createTarball()
{
  std::string cmdStr = "tar -cpvf " + this->getTmpTarballName() + " -C " + this->folder + " " + this->fileName;
  int ret = std::system(cmdStr.c_str());
  return ret == 0 ? true : false;
}

// How to check is format .tar
// ref: https://stackoverflow.com/questions/32180215/how-to-check-whether-a-file-is-in-tar-format
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
  std::string cmdStr = "tar -xpvf " + this->getTmpTarballName() + " -C " + this->tmpFolder;
  int ret = std::system(cmdStr.c_str());
  // ret == 0 ? true : false;
  return WIFEXITED(ret);
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

bool TarballService::deleteTmpFolder()
{
  int ret = std::system("rm -rf ../files/tmp/*");
  // ret == 0 ? true : false;
  return WIFEXITED(ret);
}