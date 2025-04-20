#include "context.hpp"

http::request<http::string_body>& Context::getRequest() { return request; }

http::response<http::string_body>& Context::getResponse() { return response; }

void Context::setJsonResponse(const http::status& status, const std::string& body, std::string contentType) {
  response.result(status);
  response.set(http::field::content_type, contentType);
  response.body() = body;
  response.prepare_payload(); // Ensure headers like Content-Length are set
}

//void Context::setJsonRequest( ? , const std::string &body) {}
