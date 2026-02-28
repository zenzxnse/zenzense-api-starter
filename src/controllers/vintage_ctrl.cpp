#include "vintage_ctrl.h"
#include <drogon/drogon.h>

void VintageCtrl::page(const drogon::HttpRequestPtr&,
                       std::function<void(const drogon::HttpResponsePtr&)>&& cb) {
  // If document_root is "./public", this looks for: public/vintage.html
  auto resp = drogon::HttpResponse::newFileResponse("./public/vintage.html");
  cb(resp);
}