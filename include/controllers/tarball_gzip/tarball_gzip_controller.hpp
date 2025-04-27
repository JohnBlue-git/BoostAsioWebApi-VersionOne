#pragma once

#include "abstract_controller.hpp"
#include "../services/tarball_gzip/tarball_gzip_service.hpp"

class TarballGzipController : public AbstractController {
private:
  std::shared_ptr<TarballGzipService> tarballService;

public:
  TarballGzipController(std::shared_ptr<TarballGzipService> service):
    AbstractController(),
    tarballService(service)
  {
    method["GET"] = std::bind(&TarballGzipController::handleGet, this, std::placeholders::_1);
    method["POST"] = std::bind(&TarballGzipController::handlePost, this, std::placeholders::_1);
    method["PUT"] = nullptr;
    method["PATCH"] = nullptr;
    method["DELETE"] = std::bind(&TarballGzipController::handleDelete, this, std::placeholders::_1);
  }
  virtual ~TarballGzipController() {}
public:
  TarballGzipController() = delete;
  TarballGzipController(const TarballGzipController&) = delete;
  TarballGzipController(TarballGzipController&& other) = delete;
public:
  TarballGzipController& operator=(const TarballGzipController&) = delete;
  TarballGzipController& operator=(TarballGzipController&& other) = delete;

private:
  void handleGet(std::shared_ptr<Context> ctx);
  void handlePost(std::shared_ptr<Context> ctx);
  //void handlePut(std::shared_ptr<Context> ctx);
  //void handlePatch(std::shared_ptr<Context> ctx);
  void handleDelete(std::shared_ptr<Context> ctx);
};
