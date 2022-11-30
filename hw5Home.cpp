#include "Person.h"
#include "Thing.h"
#include "GPS.h"
#include "TIME.h"

#include "ecs36b_Common.h"
#include "ecs36b_JSON.h"

// JSON RPC part
#include "hw5home.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;

int main() {
    
    // Initialize roles, GPS default of (0, 0)
    Person ridingHood;
    ridingHood.setRole("Little Red Riding Hood");
    ridingHood.setDescription("A dear little girl");

    Person grandmother;
    grandmother.setRole("Grandmother");
    grandmother.changeLocation(0, 0.5);

    Person mother;
    mother.setRole("Mother");
    mother.changeLocation(0, 0);

    Person wolf;
    wolf.setRole("Wolf");
    wolf.changeLocation(0, 0.6);
   
    // Intialize things
    Thing cap;
    cap.setItemName("Cap");
    cap.setItemDescription("A little cap of red velvet");

    Thing cake;
    cake.setItemName("cake");
    
    Thing wine;
    wine.setItemName("wine");

    // Record 1: Riding hood wearing cap
    grandmother.placeIntoInventory(cap);
    grandmother.transferThing(&ridingHood, cap);

    // Record 2: Mother gives riding hood cake and wine in village
    mother.placeIntoInventory(cake);
    mother.placeIntoInventory(wine);

    mother.transferThing(&ridingHood, cake);
    mother.transferThing(&ridingHood, wine);

    // Record 3: Riding Hood meets wolf in woods

    // Record 4: Grandmother at home right outside woods with three oak trees nearby

    std::cout << "Riding Hood At Home" << std::endl;
    std::cout << ridingHood.dump2JSON() << std::endl;

    // object mobility
  HttpClient httpclient("http://127.0.0.1:7374");
  hw5Home myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  // move
  try {
    myv = myClient.move("move", ridingHood.dump2JSON());
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << "Move response for forest:" << std::endl;
  std::cout << myv.toStyledString() << std::endl;

  exit(-2);
    
    return 0;
}