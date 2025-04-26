#pragma once

#include "abstract_controller.hpp"
#include "../services/tarball/tarball_service.hpp"

class TarballController : public AbstractController {
private:
  std::shared_ptr<TarballService> tarballService;

public:
  TarballController(std::shared_ptr<TarballService> service):
    AbstractController(),
    tarballService(service)
  {
    method["GET"] = std::bind(&TarballController::handleGet, this, std::placeholders::_1);
    method["POST"] = std::bind(&TarballController::handlePost, this, std::placeholders::_1);
    method["PUT"] = nullptr;
    method["PATCH"] = nullptr;
    method["DELETE"] = std::bind(&TarballController::handleDelete, this, std::placeholders::_1);
  }
  virtual ~TarballController() {}
public:
  TarballController() = delete;
  TarballController(const TarballController&) = delete;
  TarballController(TarballController&& other) = delete;
public:
  TarballController& operator=(const TarballController&) = delete;
  TarballController& operator=(TarballController&& other) = delete;

private:
  void handleGet(std::shared_ptr<Context> ctx);
  void handlePost(std::shared_ptr<Context> ctx);
  //void handlePut(std::shared_ptr<Context> ctx);
  //void handlePatch(std::shared_ptr<Context> ctx);
  void handleDelete(std::shared_ptr<Context> ctx);
};
