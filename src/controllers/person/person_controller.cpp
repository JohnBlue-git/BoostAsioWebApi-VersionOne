#include "person_controller.hpp"

//
// GET
//

void PersonController::handleGetCollection(std::shared_ptr<Context> ctx)
{
  http::status status;
  std::string jsonStr;

  auto persons = personService->getPersons();

#ifdef BOOST_JSON
  boost::json::array jsonArray;
  for (const auto &person : persons) {
    jsonArray.push_back(PersonSerializer::toJson(person));
  }
  jsonStr = boost::json::serialize(jsonArray);
  status = http::status::ok;
#else
  nlohmann::json jsonArray;
  for (const auto &person : persons) {
    jsonArray.push_back(PersonSerializer::toJson(person));
  }
  jsonStr = jsonArray.dump();
  status = http::status::ok;
#endif

  ctx->setJsonResponse(status, jsonStr);
}

void PersonController::handleGetById(std::shared_ptr<Context> ctx, int id)
{
  http::status status;
  std::string jsonStr;

  auto person = personService->getPersonById(id);

  if (person)
  {
    #ifdef BOOST_JSON
    status = http::status::ok;
    jsonStr = boost::json::serialize(PersonSerializer::toJson(person.value()));
#else
    status = http::status::ok;
    jsonStr = PersonSerializer::toJson(person.value()).dump();
#endif
  }
  else
  {
    status = http::status::not_found;
    jsonStr = "{\"error\": \"Person not found.\"}";
  }

  ctx->setJsonResponse(status, jsonStr);
}

void PersonController::handleGet(std::shared_ptr<Context> ctx)
{
  const http::request<http::string_body>& req = ctx->getRequest();

  int id = 0;
  if (true == AbstractController::existsId(req, &id))
  {
    PersonController::handleGetById(ctx, id);
  }
  else
  {
    PersonController::handleGetCollection(ctx);
  }
}

//
// POST
//

void PersonController::handlePost(std::shared_ptr<Context> ctx)
{
  const http::request<http::string_body>& req = ctx->getRequest();

  http::status status;
  std::string jsonStr;

  int id = 0;
  if (true == AbstractController::existsId(req, &id))
  {
    // shall replace with correct status code
    status = http::status::not_found;
    jsonStr = "{\"error\": \"POST should not have request with id.\"}";
  }
  else
  {
#ifdef BOOST_JSON
    auto json = boost::json::parse(req.body());
    auto person = PersonSerializer::fromJson(json.as_object());
#else
    auto json = nlohmann::json::parse(req.body());
    auto person = PersonSerializer::fromJson(json);
#endif
    if (person)
    {
      personService->addPerson(person.value());

      status = http::status::created;
      jsonStr = "{\"success\": \"Person created.\"}";
    }
    else
    {
      status = http::status::bad_request;
      jsonStr = "{\"error\": \"Invalid JSON payload.\"}";
    }
  }

  ctx->setJsonResponse(status, jsonStr);
}

//
// PUT
//

//void PersonController::handlePut(std::shared_ptr<Context> ctx)
//{}

//
// PATCH
//

void PersonController::handlePatch(std::shared_ptr<Context> ctx)
{
  const http::request<http::string_body>& req = ctx->getRequest();

  http::status status;
  std::string jsonStr;

  int id = 0;
  if (true == AbstractController::existsId(req, &id))
  {
    std::optional<std::string> name;
    std::optional<unsigned int> age;

#ifdef BOOST_JSON
    boost::json::value json;
    try
    {
      json = boost::json::parse(req.body());
    }
    catch([[maybe_unused]] std::exception e)
    {
      // [[maybe_unused]]
    }
    if (json.if_contains("name"))
    {
      name = json.at("name").as_string().c_str();
    }
    if (json.if_contains("age"))
    {
      age = json.at("age").as_int64();
    }
#else
    nlohmann::json json;
    try
    {
      json = nlohmann::json::parse(req.body());
    }
    catch([[maybe_unused]] std::exception e)
    {
      // [[maybe_unused]]
    }
    if (json.contains("name"))
    {
      name = json["name"];
    }
    if (json.contains("age"))
    {
      age = json["age"];
    }
#endif

    if (personService->patchPerson(id, name, age))
    {
      status = http::status::ok;
      jsonStr = "{\"success\": \"Person patched.\"}";
    }
    else
    {
      status = http::status::not_found;
      jsonStr = "{\"error\": \"Person not found.\"}";
    }
  }
  else
  {
    status = http::status::bad_request;
    jsonStr = "{\"error\": \"PATCH should have request with id.\"}";
  }

  ctx->setJsonResponse(status, jsonStr);
}

//
// DELETE
//

void PersonController::handleDeleteCollection(std::shared_ptr<Context> ctx)
{
  http::status status;
  std::string jsonStr;

  personService->deletePersons();
  status = http::status::no_content;
  jsonStr = "";

  ctx->setJsonResponse(status, jsonStr);
}

void PersonController::handleDeleteById(std::shared_ptr<Context> ctx, int id)
{
  http::status status;
  std::string jsonStr;

  if (personService->deletePersonById(id))
  {
    status = http::status::no_content;
    jsonStr = "";
  }
  else
  {
    status = http::status::not_found;
    jsonStr = "{\"error\": \"Person not found.\"}";
  }

  ctx->setJsonResponse(status, jsonStr);
}

void PersonController::handleDelete(std::shared_ptr<Context> ctx)
{
  const http::request<http::string_body>& req = ctx->getRequest();

  int id = 0;
  if (true == AbstractController::existsId(req, &id))
  {
    PersonController::handleDeleteById(ctx, id);
  }
  else
  {
    PersonController::handleDeleteCollection(ctx);
  }
}
