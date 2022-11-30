// for JsonRPCCPP
#include <iostream>
#include "hw5forest.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5home.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

#include "Person.h"
#include "Thing.h"
#include "GPS.h"
#include "ecs36b_Common.h"

using namespace jsonrpc;

class Myhw5Server : public hw5Forest
{
public:
  Myhw5Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value move(const std::string& action,
			   const Json::Value& json_object);
};

Myhw5Server::Myhw5Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Forest(connector, type)
{
  std::cout << "Myhw5Server Object created" << std::endl;
}

// member functions

Json::Value
Myhw5Server::move
(const std::string& action, const Json::Value& json_object)
{
  Json::Value result;
  std::string strJson;

  std::cout << "Move\n";

  if ((json_object.isNull() == true) || (json_object.isObject() == false)) {
      result["status"] = "failed";
      strJson = ( "person parsing error " );
      result["reason"] = strJson;
  }

  Person ridingHood;
  ridingHood.Json2Object(json_object);
  std::cout << "Riding Hood At Grandma Home" << std::endl;
  std::cout << ridingHood.dump2JSON() << std::endl;

  // originally from hw5client.cpp
  // HttpClient httpclient("http://127.0.0.1:7375");
  // hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  // Json::Value myv;

  // try {
  //   myv = myClient.move("move", ridingHood.dump2JSON());
  //   } catch (JsonRpcException &e) {
  //   cerr << e.what() << endl;
  // }
  // std::cout << myv.toStyledString() << std::endl;

  result["status"] = "successful";

  // std::cout << result.toStyledString() << std::endl;

  return result;
}

int main()
{
  HttpServer httpserver(7375);
  Myhw5Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
