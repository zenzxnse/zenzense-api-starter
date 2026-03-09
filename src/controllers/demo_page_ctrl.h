#pragma once
#include <drogon/HttpSimpleController.h>

class DemoPageCtrl : public drogon::HttpSimpleController<DemoPageCtrl> {
public:
  void asyncHandleHttpRequest(
      const drogon::HttpRequestPtr&,
      std::function<void(const drogon::HttpResponsePtr&)>&& cb) override;

  PATH_LIST_BEGIN
  PATH_ADD("/api/pages/demo", drogon::Get);
  PATH_LIST_END
};