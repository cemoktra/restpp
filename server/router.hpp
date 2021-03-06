#pragma once

#include "interfaces/router.hpp"
#include <memory>
#include <vector>

namespace restpp {
  class route;
  class routetree;

  class router : public interfaces::router_interface {
    public:
      router();

      void get(const std::string& route, route_callback callback) override;
      void post(const std::string& route, route_callback callback) override;

      bool route_request(std::shared_ptr<request> request, std::shared_ptr<response> response) override;

    private:
      std::vector<std::shared_ptr<route>> m_routes;
      std::shared_ptr<routetree> m_root;
  };
}