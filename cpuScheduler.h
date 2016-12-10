#ifndef CPUSCHEDULER_H_
#define CPUSCHEDULER_H_
#include <iostream>
#include <vector>
#include "Job.h"
using namespace std;

class cpuScheduler {
	public:
/*		long scheduleCpu (vector<Job> jobTable) {
			//First Come, First Served
			for (long i = 0; i < jobTable.size(); i++) {
				if (jobTable[i].getInMem() && !jobTable[i].getDoingIo())
					return i;
			}
			return -1;
		}*/
	//STS: First Come, First Served using ready queue
		long scheduleCpu (queue<Job> readyQueue) {
			queue<Job> ready = readyQueue;
			Job toRun = NULL;
			while (!ready.empty()) {
				if ((ready.front()).getInMem())
					if (!(ready.front()).getIsBlocked() && !(ready.front()).getDoingIo()) {
						toRun = ready.front();
					}
				ready.pop();
			}
			return toRun;
		}

		//LTS: Swapper
};

#endif /* CPUSCHEDULER_H_ */
