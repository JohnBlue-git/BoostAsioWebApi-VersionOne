#pragma once

#include "abstract_server.hpp"

class AbstractController : public IController {
public:
    AbstractController() {
        method["GET"] = nullptr;
        method["POST"] = nullptr;
        method["PUT"] = nullptr;
        method["PATCH"] = nullptr;
        method["DELETE"] = nullptr;
    }
    virtual ~AbstractController() {}
public:
    AbstractController(const AbstractController&) = delete;
    AbstractController(AbstractController&& other) = delete;
public:
    AbstractController& operator=(const AbstractController&) = delete;
    AbstractController& operator=(AbstractController&& other) = delete;

public:
    bool existsId(const http::request<http::string_body>& req, int* id) override;
    void handleRequest(std::shared_ptr<Context> ctx) override;
};
