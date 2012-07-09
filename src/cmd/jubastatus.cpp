// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#include <pficommon/text/json.h>
#include "commonrpc_client.hpp"
#include "../common/exception.hpp"
#include "../common/cmdline.h"

static const std::string PROGNAME(JUBATUS_APPNAME "status");
static const std::string VERSION(JUBATUS_VERSION);

using namespace std;
using namespace pfi::text::json;
using namespace jubatus::client;

void callgetstatus(const string&, const int, const string&);

int main(int args, char** argv) try {
  cmdline::parser p;
  p.add<string>("server", 's', "server or keeper ip:port", false, "127.0.0.1:9199");
  p.add<string>("name", 'n', "learning machine name", false, "default");
  p.parse_check(args, argv);

  string snpn = p.get<string>("server");
  string name = p.get<string>("name");

  string server;
  int port;

  if (iprevert(snpn, server, port))
    callgetstatus(server, port, name);

  return 0;
} catch (const jubatus::exception::jubatus_exception& e) {
  std::cout << e.diagnostic_information(true) << std::endl;
}

void callgetstatus(const string& server,const int port, const string& name){
    
    commonrpc crpc(server, port, 10);
    std::map<std::string, std::map<std::string, std::string > > stat = crpc.get_status(name);

    json js = to_json(stat);
    std::cout << js << std::endl;
}


