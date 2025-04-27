#pragma once

#include <fstream>
#include <string>

class TarballService {
private:
  std::string folder;
  std::string tmpFolder;
  std::string fileName;
  std::string tarballName;

public:
  TarballService()
  {
    folder = "../files";
    tmpFolder = "../files/tmp";
    fileName = "data.json";
    tarballName = "data.tar";
  }

public:
  std::string getFileName();
  std::string getTmpFileName();
  std::string getTmpTarballName();
  bool createTarball();
  std::string getTarball();
  bool isTarball(const std::string& body);
  bool tmpTarball(const std::string& body);
  bool extarctTarball();
  bool deleteTmpFolder();
};