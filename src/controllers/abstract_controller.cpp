#include "abstract_controller.hpp"

void AbstarctController::handleRequest(std::shared_ptr<Context> ctx)
{
    std::function(void(std::shared_ptr<Context> ctx)) callback;
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
            status = http::status::not_found; // shall correct this code 
            jsonStr = "{\"error\": \"Method not support.\"}";
            return;
    }
    if (callback)
    {
        callback(ctx);
    }
}
