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
    
    
/*    
    
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




*/

// Removes job from memory 
void removeJob(Job &j){
    
    // Counter to keep track of memory locations deleted in array 
	int counter =0;
    
    // Pointer to the memory location of the job in the array 
	int *pointer = (int*)&arr[j.memLocation];

    // Test if job is in memory
    if (j.inMem){
           
        // Compare counter to jobSize
        while (counter != j.jobSize){
           
            // Set memory location to 0
            // Removes jobID# from current array location
            *pointer=0;
            
            // Increment pointer to memory location of the job within the array
            point++;
            
            // Increment counter 
            counter++;
	   }
        // Set pointer to null
        point = NULL;
    }
    
    // Take job out of memory
    j.inMem = false;

}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif