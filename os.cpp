/*
 * os.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: sunnyshapir
 */

#include <iostream>
#include <vector>
#include <queue>
#include "Job.h"
#include "cpuScheduler.h"
using namespace std;

//Switch job table to array since need to set max capacity=50? Job jobTable[50];
vector<Job> jobTable;
long memory[100];
long currentJobRunning;
long currentJobIo;
queue<Job> readyQueue;
queue<Job> ioQueue;
cpuScheduler scheduler;

void startup ();
void Crint (long &a, long p[]);
void addToJobTable (Job newJob);
void bookKeep (long time);
void swapper ();
void refreshJobTable ();
void runJob (long &a, long p[], Job toRun);

void startup () {
	currentJobRunning = -1;
	for (long i = 0; i < 100; i++)
		memory[i] = 0;
}

void Crint (long &a, long p[]) {
	bookKeep (p[5]);
	refreshJobTable();
	Job newJob = new Job (p);
	addToJobTable (newJob);
	swapper ();
	readyQueue.push_back(newJob);
	runJob (a, p, scheduler.scheduleCpu (readyQueue));
}

void addToJobTable (Job newJob) {
	long index = newJob.getJobNumber();
	vector<Job>::iterator it = jobTable.begin();
	jobTable.insert(it + index, newJob);
}

void bookKeep (long time) {
	if (currentJobRunning != -1) {
		vector<Job>::iterator it = jobTable.begin();
		long timeSpent = time - jobTable[it + currentJobRunning].getCurrentTime();
		jobTable[it + currentJobRunning].setCurrentTime(jobTable[it + currentJobRunning].getCurrentTime() + timeSpent);
		jobTable[it + currentJobRunning].setMaxCpu(jobTable[it + currentJobRunning].getMaxCpu() - timeSpent);
	}
}

void runJob (long &a, long p[], Job toRun) {
	if (readyQueue.empty() || toRun == NULL)
		a = 1;
	else {
		a = 2;
		p[2] = toRun.getMemoryLocation();
		p[3] = toRun.getJobSize();
		p[4] = 50;
		currentJobRunning = toRun.getJobNumber();
		//take job off of ready queue here? readyQueue.pop();
	}
	return;
}

void refreshJobTable () {
	for (long i = 0; i < jobTable.size(); i++) {
		vector<Job>::iterator it = jobTable.begin();
		if (jobTable[it + i].getIsTerminated())
			jobTable[it + i].erase(it + i);
	}
}
