#include "demo_page_ctrl.h"
#include <drogon/drogon.h>

void DemoPageCtrl::asyncHandleHttpRequest(
    const drogon::HttpRequestPtr&,
    std::function<void(const drogon::HttpResponsePtr&)>&& cb) {

  Json::Value root(Json::objectValue);
  root["page"] = "demo";
  root["title"] = "Demo page from Drogon";
  root["subtitle"] = "This content came from the C++ backend.";

  Json::Value blocks(Json::arrayValue);

  {
    Json::Value block(Json::objectValue);
    block["type"] = "hero";
    block["title"] = "Backend-driven hero";
    block["subtitle"] = "SvelteKit is rendering this.";
    blocks.append(block);
  }

  {
    Json::Value block(Json::objectValue);
    block["type"] = "card";
    block["text"] = "First modular block";
    blocks.append(block);
  }

  {
    Json::Value block(Json::objectValue);
    block["type"] = "card";
    block["text"] = "Second modular block";
    blocks.append(block);
  }

  root["blocks"] = blocks;

  auto resp = drogon::HttpResponse::newHttpJsonResponse(root);
  resp->addHeader("Access-Control-Allow-Origin", "*"); // fine for local demo
  cb(resp);
}