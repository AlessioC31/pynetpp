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

#include "server.h"
#include "JobMessage_m.h"

namespace loadbalancing {

Define_Module(Server);

void Server::initialize()
{
    load = 0;
    current_job = nullptr;
}

void Server::update_load() {
    char* metric_name = new char[20];

    sprintf(metric_name, "load_%d", getIndex());
    recordScalar(metric_name, load);
}

void Server::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        // Self message means it's an execution_finished msg

        load -= current_job->getTime_to_execute();
        delete current_job;
        update_load();

        if (!job_queue.empty()) {
            // If we have jobs in the queue

            JobMsg* next_job = job_queue.front();
            job_queue.pop();

            cMessage* timer_msg = new cMessage("execution_finished");
            current_job = next_job;
            scheduleAt(simTime() + next_job->getTime_to_execute(), timer_msg);
        } else {
            current_job = nullptr;
        }

        return;
    }

    JobMsg* new_job = check_and_cast<JobMsg*>(msg);

    if (current_job == nullptr) {
        // If in idle we directly execute the job
        load += new_job->getTime_to_execute();
        cMessage* timer_msg = new cMessage("execution_finished");
        current_job = new_job;
        scheduleAt(simTime() + new_job->getTime_to_execute(), timer_msg);
    } else {
        // we put the job in the queue

        load += new_job->getTime_to_execute();
        job_queue.push(new_job);
    }
    update_load();

}

} //namespace
