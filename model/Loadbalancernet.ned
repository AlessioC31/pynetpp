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

// package loadbalancing.simulations.loadbalancernet;

// import loadbalancing.Server;
// import loadbalancing.Source;
// import loadbalancing.Loadbalancer;
//
// TODO Auto-generated network
//
network Loadbalancernet
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        source: Source;
        loadbalancer: Loadbalancer;
        server[4]: Server;
    connections:
        source.out --> Channel --> loadbalancer.in;
        loadbalancer.out++ --> Channel --> server[0].in;
        loadbalancer.out++ --> Channel --> server[1].in;
        loadbalancer.out++ --> Channel --> server[2].in;
        loadbalancer.out++ --> Channel --> server[3].in;        
}
