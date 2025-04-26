#pragma once

#include <fstream>
#include <string>

class TarballService {
private:
  std::string fileName = "../files/data.json";
  std::string tmpFileName = "../files/tmp/data.json";
  std::string tmpTarballName = "../files/tmp/data.tar";

public:
  std::string getFileName();
  std::string getTmpFileName();
  std::string getTmpTarballName();
  bool tmpFile();
  bool createTarball();
  std::string getTarball();
  bool isTarball(const std::string& body);
  bool tmpTarball(const std::string& body);
  bool extarctTarball();
  bool deleteTarball();
};