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
void Svc (long &a, long p[]);
long findByNumber (long jobNumber);
void addToJobTable (Job newJob);
void bookKeep (long time);
void swapper ();
void runJob (long &a, long p[], Job toRun);
void terminateJob (long jobNumber);
void refreshJobTable ();
bool isOnIoQueue (long jobNumber);
void siodisk(long JobNum);

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

void Svc (long &a, long p[]) {
	bookKeep(p[5]);
	//vector<Job>::iterator it = jobTable.begin();
	long currentJobIndex = findByNumber(p[1]);
	switch (a) {
	case '5':
		//take job off ready queue, take job out of jobtable, deallocate memory
		terminateJob (p[1]);
		break;
	case '6':
		//take job off ready queue, add to ioqueue, call appropriate sos function
		requestIo (p[1]);
		break;
	case '7':
		//if job is currently doing IO or is on IO Queue, block
		if (jobTable.at(currentJobIndex).getDoingIo() || isOnIoQueue(p[1]))
			jobTable.at(currentJobIndex).setIsBlocked (true);
		break;
	}
	runJob(a, p, scheduler.scheduleCpu (readyQueue));
	return;
}

void requestIo (long jobNumber) {
	long jobIndex = findByNumber(jobNumber);
	if (ioQueue.empty())
		siodisk (jobNumber);
	else
		ioQueue.push(jobTable.at(jobIndex));
	(jobTable.at(jobIndex)).setDoingIo(true);
}

void terminateJob (long jobNumber) {
	long jobIndex = findByNumber(jobNumber);
	if (jobNumber != -1 && !isOnIoQueue(jobNumber)) {
		(jobTable.at(jobIndex)).setIsTerminated (true);
		//DEALLOCATE MEMORY HERE!!!
	}
	else if (jobNumber != -1)
		(jobTable.at(jobIndex)).setIsTerminated (true);
}

//Returns index of job in the job table
long findByNumber (long jobNumber) {
	//vector<Job>::iterator it = jobTable.begin();
	for (long i = 0; i < jobTable.size(); i++) {
		if ((jobTable.at(i)).getJobNumber() == jobNumber)
			return i;
	}
	return -1;
}

bool isOnIoQueue (long jobNumber) {
	for (vector<Job>::iterator i = ioQueue.begin(); i != ioQueue.end(); i++) {
		if (ioQueue.at(*i) == jobNumber)
			return true;
	}
	return false;
}

void addToJobTable (Job newJob) {
	long index = newJob.getJobNumber();
	vector<Job>::iterator it = jobTable.begin();
	jobTable.insert(it + index, newJob);
}

void bookKeep (long time) {
	if (currentJobRunning != -1) {
		//vector<Job>::iterator it = jobTable.begin();
		long timeSpent = time - (jobTable.at(currentJobRunning)).getCurrentTime();
		(jobTable.at(currentJobRunning)).setCurrentTime((jobTable.at(currentJobRunning)).getCurrentTime() + timeSpent);
		(jobTable.at(currentJobRunning)).setMaxCpu((jobTable.at(currentJobRunning)).getMaxCpu() - timeSpent);
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
		if ((readyQueue.front()).getJobNumber() == toRun.getJobNumber())
			readyQueue.pop();
	}
	return;
}

void refreshJobTable () {
	for (long i = 0; i < jobTable.size(); i++) {
		vector<Job>::iterator it = jobTable.begin();
		if ((jobTable.at(i)).getIsTerminated())
			(jobTable.at(i)).erase(it + i);
	}
}
