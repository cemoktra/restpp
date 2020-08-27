#include "router.hpp"
#include "types.hpp"
#include "request.hpp"
#include "response.hpp"
#include "route.hpp"
#include "utils.hpp"

#include <iostream>


namespace restpp {
  void router::get(const std::string& route, route_callback callback)
  {
    m_routes.emplace_back(route::create(request_method::GET, route, callback));
  }

  void router::post(const std::string& route, route_callback callback)
  {
    m_routes.emplace_back(route::create(request_method::POST, route, callback));
  }

  bool router::route_request(std::shared_ptr<request> request, std::shared_ptr<response> response)
  {
    std::shared_ptr<route> full_match;
    std::shared_ptr<route> param_match;

    for (auto route : m_routes) {
      auto result = request->match(route);
      if (!full_match and result == route_match::full_match)
        full_match = route;
      else if (!param_match and result == route_match::param_match)
        param_match = route;      
    }

    if (full_match) {
      full_match->execute(request, response);
      return true;
    }
    else if (param_match) {
      param_match->execute(request, response);
      return true;
    }

    return false;
  }
}