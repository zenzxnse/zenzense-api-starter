#pragma once
#include <drogon/HttpSimpleController.h>

class StatusCtrl : public drogon::HttpSimpleController<StatusCtrl> {
public:
  void asyncHandleHttpRequest(const drogon::HttpRequestPtr&,
                              std::function<void(const drogon::HttpResponsePtr&)>&& cb) override;

  PATH_LIST_BEGIN
  PATH_ADD("/status", drogon::Get);
  PATH_LIST_END
};