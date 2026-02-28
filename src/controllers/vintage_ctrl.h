#pragma once
#include <drogon/HttpController.h>

class VintageCtrl : public drogon::HttpController<VintageCtrl> {
public:
  METHOD_LIST_BEGIN
    ADD_METHOD_TO(VintageCtrl::page, "/vintage", drogon::Get);
  METHOD_LIST_END

  void page(const drogon::HttpRequestPtr& req,
            std::function<void(const drogon::HttpResponsePtr&)>&& cb);
};