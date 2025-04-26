#include "file_controller.hpp"

//
// GET
//

void FileController::handleGet(std::shared_ptr<Context> ctx)
{
  http::status status;
  std::string jsonStr;
  
  std::string body = fileService->getFile();

  if (body.empty())
  {
    status = http::status::not_found;
    jsonStr = "{\"error\": \"Could not found " + fileService->getFileName() + " \"}";
    ctx->setJsonResponse(status, jsonStr);
    return;
  }
  status = http::status::ok;
  ctx->setFileResponse(status, body, "file.json");
}

//
// POST
//

//void FileController::handlePost(std::shared_ptr<Context> ctx)
//{}

//
// PUT
//

//void FileController::handlePut(std::shared_ptr<Context> ctx)
//{}

//
// PATCH
//

//void FileController::handlePatch(std::shared_ptr<Context> ctx)
//{}

//
// DELETE
//

//void FileController::handleDelete(std::shared_ptr<Context> ctx)
//{}
