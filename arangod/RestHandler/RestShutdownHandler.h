////////////////////////////////////////////////////////////////////////////////
/// @brief shutdown request handler
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Max Neunhoeffer
/// @author Copyright 2014, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_REST_HANDLER_REST_SHUTDOWN_HANDLER_H
#define ARANGOD_REST_HANDLER_REST_SHUTDOWN_HANDLER_H 1

#include "Basics/Common.h"
#include "ApplicationServer/ApplicationServer.h"
#include "Rest/HttpResponse.h"
#include "RestHandler/RestBaseHandler.h"

namespace triagens {
namespace admin {


////////////////////////////////////////////////////////////////////////////////
/// @brief shutdown request handler
////////////////////////////////////////////////////////////////////////////////

class RestShutdownHandler : public RestBaseHandler {
  
 public:
  ////////////////////////////////////////////////////////////////////////////////
  /// @brief constructor
  ////////////////////////////////////////////////////////////////////////////////

  RestShutdownHandler(rest::HttpRequest*, void* applicationServer);

  
 public:
  ////////////////////////////////////////////////////////////////////////////////
  /// {@inheritDoc}
  ////////////////////////////////////////////////////////////////////////////////

  bool isDirect() const override;

  ////////////////////////////////////////////////////////////////////////////////
  /// @brief initiates the shutdown process
  ////////////////////////////////////////////////////////////////////////////////

  status_t execute() override;

  
 private:
  ////////////////////////////////////////////////////////////////////////////////
  /// @brief application server
  ////////////////////////////////////////////////////////////////////////////////

  triagens::rest::ApplicationServer* _applicationServer;
};
}
}

#endif


