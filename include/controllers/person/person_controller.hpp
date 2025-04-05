#pragma once

#include "abstract_controller.hpp"
#include "../serializers/person/person_serializer.hpp"
#include "../services/person/person_service.hpp"

class PersonController : public AbstractController {
private:
  std::shared_ptr<IPersonService> personService;

public:
  PersonController(std::shared_ptr<IPersonService> service):
    AbstractController(),
    personService(service)
  {
    method["GET"] = std::bind(&PersonController::handleGet, this, std::placeholders::_1);
    method["POST"] = std::bind(&PersonController::handlePost, this, std::placeholders::_1);
    method["PUT"] = nullptr;
    method["PATCH"] = std::bind(&PersonController::handlePatch, this, std::placeholders::_1);
    method["DELETE"] = std::bind(&PersonController::handleDelete, this, std::placeholders::_1);
  }
  virtual ~PersonController() {}
public:
  PersonController() = delete;
  PersonController(const PersonController&) = delete;
  PersonController(PersonController&& other) = delete;
public:
  PersonController& operator=(const PersonController&) = delete;
  PersonController& operator=(PersonController&& other) = delete;

private:
  void handleGet(std::shared_ptr<Context> ctx);
  void handlePost(std::shared_ptr<Context> ctx);
  //void handlePut(std::shared_ptr<Context> ctx);
  void handlePatch(std::shared_ptr<Context> ctx);
  void handleDelete(std::shared_ptr<Context> ctx);

private:
  void handleGetCollection(std::shared_ptr<Context> ctx);
  void handleGetById(std::shared_ptr<Context> ctx, int id);
  //
  void handleDeleteCollection(std::shared_ptr<Context> ctx);
  void handleDeleteById(std::shared_ptr<Context> ctx, int id);
};
