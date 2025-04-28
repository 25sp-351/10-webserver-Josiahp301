#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"
#include "response.h"


#define UNUSED(x) (void*)x


Response* get_stats_handler(Request* req);
Response* get_static_handler(Request* req);
Response* get_calc_handler(Request* req);
Response* no_resource_handler(Request* req);
Response* internal_error(Request* req);
Response* bad_request_handler(Request* req);

Response* route_request(Request* req);

#endif 