#pragma once

#include "interface_controller.hpp"
#include "abstract_controller.hpp"
#include "../serializers/person_serializer.hpp"
#include "../services/person_service.hpp"

class PersonController : public AbstractController {
private:
  std::shared_ptr<IPersonService> personService;

public:
  PersonController(std::shared_ptr<IPersonService> service):
    AbstractController(),
    personService(service)
  {
    method["GET"] = handleGet;
    method["POST"] = handlePost;
    method["PUT"] = nullptr;
    method["PATCH"] = nullptr;
    method["DELETE"] = handleDelete;
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
  void handlePut(std::shared_ptr<Context> ctx);
  void handlePatch(std::shared_ptr<Context> ctx);
  void handleDelete(std::shared_ptr<Context> ctx);

private:
  void handleGetCollection(std::shared_ptr<Context> ctx);
  void handleGetById(std::shared_ptr<Context> ctx, int id);
};
