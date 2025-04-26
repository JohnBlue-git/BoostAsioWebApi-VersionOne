#include "context.hpp"

http::request<http::string_body>& Context::getRequest() { return request; }

http::response<http::string_body>& Context::getResponse() { return response; }

void Context::setResponse(const http::status& status, const std::string& body, const std::string& contentType) {
  response.result(status);
  response.set(http::field::content_type, contentType);
  response.body() = body;
  response.prepare_payload(); // Ensure headers like Content-Length are set
}

void Context::setJsonResponse(const http::status& status, const std::string& body) {
  setResponse(status, body, "application/json");
}

void Context::setFileResponse(const http::status& status, const std::string& body, const std::string& file) {
  response.set(http::field::content_disposition, "attachment; filename=\"" + file + "\"");
  setResponse(status, body, "application/octet-stream");
}

//void Context::setJsonRequest( ? , const std::string &body) {}

/*
The line `http::status::not_found` you're referring to looks like it comes from the **Boost.Beast** or **Boost.Asio** C++ library, which defines HTTP status codes using the `http::status` enum.

Here are some other common HTTP status codes you can use from `http::status` in C++ (with Boost.Beast):

### ✅ Commonly Used `http::status` Codes

| Status Code       | Enum Value                    | Description                   |
|-------------------|-------------------------------|-------------------------------|
| `200`             | `http::status::ok`            | Request succeeded             |
| `201`             | `http::status::created`       | Resource created              |
| `204`             | `http::status::no_content`    | Success, no content returned  |
| `301`             | `http::status::moved_permanently` | Permanent redirect       |
| `302`             | `http::status::found`         | Temporary redirect            |
| `400`             | `http::status::bad_request`   | Client error                  |
| `401`             | `http::status::unauthorized`  | Auth required                 |
| `403`             | `http::status::forbidden`     | Auth refused                  |
| `404`             | `http::status::not_found`     | Resource not found            |
| `500`             | `http::status::internal_server_error` | Server error            |
| `503`             | `http::status::service_unavailable` | Server not ready         |

*/
