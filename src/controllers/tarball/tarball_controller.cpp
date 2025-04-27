#include "tarball_controller.hpp"

//
// GET
//

void TarballController::handleGet(std::shared_ptr<Context> ctx)
{
  http::status status;
  std::string jsonStr;

  std::ifstream ifs(tarballService->getFileName(),
    std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    status = http::status::internal_server_error;
    jsonStr = "{\"error\": \"Failed to open file " + tarballService->getTmpFileName() + " \"}";
    ctx->setJsonResponse(status, jsonStr);
  }
  if (!tarballService->createTarball()) {
    status = http::status::internal_server_error;
    jsonStr = "{\"error\": \"Error occurred while calling system() with tar\"}";
    ctx->setJsonResponse(status, jsonStr);
    return;
  }
  std::string body = tarballService->getTarball();

  if (body.empty())
  {
    status = http::status::not_found;
    jsonStr = "{\"error\": \"Could not found " + tarballService->getFileName() + " \"}";
    ctx->setJsonResponse(status, jsonStr);
    return;
  }
  status = http::status::ok;
  ctx->setTarballResponse(status, body, "data.tar");
}

//
// POST
//

void TarballController::handlePost(std::shared_ptr<Context> ctx)
{
  http::status status;
  std::string jsonStr;

  const http::request<http::string_body>& req = ctx->getRequest();
  const std::string& body = req.body();

  if (!tarballService->isTarball(body)) {
    status = http::status::unsupported_media_type;
    jsonStr = "{\"error\": \"Unsupported media type, should be .tar\"}";
    ctx->setJsonResponse(status, jsonStr);
    return;
  }
  if (!tarballService->tmpTarball(body)) {
    status = http::status::internal_server_error;
    jsonStr = "{\"error\": \"Failed to open file for writing\"}";
    ctx->setJsonResponse(status, jsonStr);
    return;
  }
  if (!tarballService->extarctTarball()) {
    status = http::status::internal_server_error;
    jsonStr = "{\"error\": \"Error occurred while calling system() with tar\"}";
    ctx->setJsonResponse(status, jsonStr);
    return;
  }
  status = http::status::no_content;
  ctx->setJsonResponse(status, jsonStr);
}

//
// PUT
//

//void TarballController::handlePut(std::shared_ptr<Context> ctx)
//{}

//
// PATCH
//

//void TarballController::handlePatch(std::shared_ptr<Context> ctx)
//{}

//
// DELETE
//

void TarballController::handleDelete(std::shared_ptr<Context> ctx)
{
  http::status status;
  std::string jsonStr;

  if (!tarballService->deleteTmpFolder()) {
    status = http::status::internal_server_error;
    jsonStr = "{\"error\": \"Error occurred while calling system() with rm\"}";
    ctx->setJsonResponse(status, jsonStr);
    return;
  }
  status = http::status::no_content;
  ctx->setJsonResponse(status, jsonStr);
}
