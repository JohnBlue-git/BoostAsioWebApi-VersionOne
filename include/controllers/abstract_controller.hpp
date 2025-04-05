#pragma once

#include "interface_controller.hpp"

class AbstractController : public IController {
protected:
    std::unordered_map<std::string, std::function<void(std::shared_ptr<Context> ctx)>> method;

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
