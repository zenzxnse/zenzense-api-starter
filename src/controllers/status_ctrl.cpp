#include "status_ctrl.h"
#include <drogon/drogon.h>

void StatusCtrl::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr&,
    std::function<void(const drogon::HttpResponsePtr&)>&& cb) {

  Json::Value j(Json::objectValue);
  j["ok"] = true;
  j["endpoint"] = "/status";
  j["message"] = "The server is responding to 127.0.0.1:8080";

  cb(drogon::HttpResponse::newHttpJsonResponse(j));
}