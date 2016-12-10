#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <iostream>
using namespace std;


class MemoryManager{

public: 
    
    
    int memoryChunk= 100;
    int arrayOfJobs[memoryChunk]; 


    MemoryManager(){
        initJobsArray();
    }
    
    

// Initialize all chunks of memory to 0  
void initJobsArray(){
	for (int i = 0; i < memoryChunk; i++){
		arrayOfJobs[i]=0;
	}
}
    

// Returns the amount of free memory chunks
int getFreeMemory(){
    
	int blocks = 0;
    
	for (int i = 0; i < memoryChunk; i++){
		if (arrayOfJobs[i] == 0){
			blocks++;
		}
	}

	blocks = blocks*1000;
    
    return  memoryBlocks;
}

// Tests if Job will fit into memory
bool jobFit(Job &j){
    if (j.jobSize < getFreeMemory()){
		return true;
	} else {
		return false;
	}
}


    
//Print Memory Management Table
void printMemoryTable(){
	for (int i =0; i <memoryChunk; i++){
		cout << "Place in Memory | " << i << " | Job Number: | " <<  arrayOfJobs[i] << endl;
	}
}
    
////// ------------------ currently working on
// Place job into memory
void placeJob(Job &j){
	// Divides job size by 1000 to find how many memory chunks it will use
	int x = j.jobSize /1000;
    int counter = 0;
    
	// Test if job will fit into memory
	if (jobFit(j)){
        
		for (int i=0; i<memoryChunk; i++){
			if (arrayOfJobs[i] == 0 && x !=0){
				
                arrayOfJobs[i] = j.jobNumber;
				
                j.joblocations.insert(i);
				
                x--;
			}
		}
		set<int>::iterator it;

		cout << "Job " << j.id << " placed into memory at locations: ";
		for (it =j.joblocations.begin() ; it != j.joblocations.end();it++){
				cout << *it << " ";

		}

			cout << endl << getFreeMemory(arr,arrSize) <<endl;
		} else {
			cout << "Could not place job into memory!" <<endl;
		}
}





// ---------------------------------------------
// REMOVES JOB FROM MEMORY
void removeJob(Job &j, int* arr,int arrSize){
	std::cout << "Memory available before job removal: " << getFreeMemory(arr,arrSize) << "k" <<endl;

	// ITERATOR TO GO THROUGH JOB LOCATIONS IN MEMORY MANAGER
	set<int>::iterator it = j.joblocations.begin();

	// SET JOBID OF JOB LOCATIONS IN ARRAY TO 0
	// (REMOVING JOB ID FROM LOCATION IN MEMORY)
	if (j.jobNumber !=0){
		while(it != j.joblocations.end()){
			arr[*it] =0;
			++it;
		}
	} else {
		cout << "Invalid JobID, no job in memory location." <<endl;
	}
	// PRINT OUT JOBID REMOVAL CONFIRMATION
	std::cout << "Job Number" << j.jobNumber << " and size " <<  j.jobSize << "k was successfully removed from memory" << endl;

	// PRINTS OUT FREE MEMORY AVAILABLE AFTER JOB REMOVAL
	std::cout << "You now have " << getFreeMemory(arr,arrSize) << " of free memory available" <<endl;

	// PRINT MEMORY TABLE
	printMemoryTable(arr,arrSize);
}


};

#endif