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

#include "source.h"
#include "JobMessage_m.h"

namespace loadbalancing {

Define_Module(Source);

void Source::initialize()
{
    exp_rng.setMean(1);
    timer = new cMessage("timer");

    scheduleAt(simTime(), timer);
}

void Source::handleMessage(cMessage *msg)
{
    if (msg == timer) {
        JobMsg* new_job = new JobMsg("job");
        new_job->setTime_to_execute(exp_rng.draw());
        send(new_job, "out");

        scheduleAt(simTime() + exp_rng.draw(), timer);
    }
}

} //namespace
