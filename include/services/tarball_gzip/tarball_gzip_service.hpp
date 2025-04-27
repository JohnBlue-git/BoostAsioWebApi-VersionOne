#pragma once

#include <fstream>
#include <string>

class TarballGzipService {
private:
  std::string folder;
  std::string tmpFolder;
  std::string fileName;
  std::string tarballName;

public:
  TarballGzipService()
  {
    folder = "../files";
    tmpFolder = "../files/tmp";
    fileName = "data.json";
    tarballName = "data.tar.gz";
  }

public:
  std::string getFileName();
  std::string getTmpFileName();
  std::string getTmpTarballName();
  bool createTarball();
  std::string getTarball();
  bool isTarball();
  bool tmpTarball(const std::string& body);
  bool extarctTarball();
  bool deleteTmpFolder();
};