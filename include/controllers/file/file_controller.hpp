#pragma once

#include "abstract_controller.hpp"
#include "../services/file/file_service.hpp"

class FileController : public AbstractController {
private:
  std::shared_ptr<FileService> fileService;

public:
  FileController(std::shared_ptr<FileService> service):
    AbstractController(),
    fileService(service)
  {
    method["GET"] = std::bind(&FileController::handleGet, this, std::placeholders::_1);
    method["POST"] = nullptr;
    method["PUT"] = nullptr;
    method["PATCH"] = nullptr;
    method["DELETE"] = nullptr;
  }
  virtual ~FileController() {}
public:
  FileController() = delete;
  FileController(const FileController&) = delete;
  FileController(FileController&& other) = delete;
public:
  FileController& operator=(const FileController&) = delete;
  FileController& operator=(FileController&& other) = delete;

private:
  void handleGet(std::shared_ptr<Context> ctx);
  //void handlePost(std::shared_ptr<Context> ctx);
  //void handlePut(std::shared_ptr<Context> ctx);
  //void handlePatch(std::shared_ptr<Context> ctx);
  //void handleDelete(std::shared_ptr<Context> ctx);
};
