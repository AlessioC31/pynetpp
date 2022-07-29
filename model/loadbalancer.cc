//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "loadbalancer.h"
// #include <pybind11/pybind11.h>

// namespace py = pybind11;

namespace loadbalancing {

Define_Module(Loadbalancer);

void Loadbalancer::initialize()
{
    server_idx = 0;
    // TODO - Generated method body
}

void Loadbalancer::handleMessage(cMessage *msg)
{
    send(msg, "out", server_idx);
}

// int Loadbalancer::get_server() {
//     py::object aigympp = py::module_::import("aigympp");
//     py::object get_action = aigympp.attr("get_action");
//     py::object result = get_action();

//     int server = result.cast<int>();

//     return server;
// }

} //namespace
