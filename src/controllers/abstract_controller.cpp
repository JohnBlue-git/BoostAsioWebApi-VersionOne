#include "abstract_controller.hpp"

bool AbstractController::existsId(const http::request<http::string_body>& req, int* id)
{
  try
  {
    const std::string path(req.target());
    std::smatch matches;
    std::regex pattern(R"(^/[^/]+(?:/[^/]+)?(?:/(\d+))?$)");
    std::regex_match(path, matches, pattern);
    if (matches[1].matched) 
    {
      *id = std::stoi(matches[1]);
      return true;
    }
    return false;
  }
  catch([[maybe_unused]] std::exception e)
  {
    return false;
  }
}

void AbstractController::handleRequest(std::shared_ptr<Context> ctx)
{
    std::function<void(std::shared_ptr<Context> ctx)> callback;
    const http::request<http::string_body>& req = ctx->getRequest();
    switch (req.method())
    {
      case GET:
        callback = method["GET"];
        break;
      case POST:
        callback = method["POST"];
        break;
      case PUT:
        callback = method["PUT"];
        break;
      case PATCH:
        callback = method["PATCH"];
        break;
      case DELETE:
        callback = method["DELETE"];
        break;
      default:
        // shall replace with correct status code
        ctx->setJsonResponse(
          http::status::not_found,
          "{\"error\": \"Method not support.\"}");
        return;
    }
    if (!callback)
    {
      // shall replace with correct status code
      ctx->setJsonResponse(
        http::status::not_found,
        "{\"error\": \"Method not support.\"}");
      return;
    }
    callback(ctx);
}
