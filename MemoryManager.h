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
    
    
// Small Error in code ** still working on**
// Jobs are placed into memory but in certain cases 
// the job will not place jobNumber into the last slot of memmory it will consume
    
// Places Job Into Memory
void placeJob(Job &j){

	int counter =0;

    // Store size and jobNumber
	int sizeOfJob = j.jobSize;
	int jId = j.jobNumber;

    // Pointer to beginning of jobs array
	int *n = (int*)&arr[0];

	for (int i=0; i<arrSize-sizeOfJob; i++){

		counter =0;
        
        // If current array position doesnt have jobNumber
		if (arr[i] == 0){
            
			n = (int*)&arr[i];
            
            // Loop to find contiguous memory slots
			while (*n==0 && counter!=sizeOfJob){
				counter++;
				n++;
			}
            
            // If there is enough contiguous memory, place job into array
			if (counter == sizeOfJob){
                
                    std::cout << "Job H"<< j.jobNumber << " may fit, beginning with index " << i << " and ending at " << i + (counter-1) <<endl;

                    // Set memory location of job
                    j.memoryLocation=i;

                    // Set pointer to first memory address locaction  of job
                    n = (int*)&arr[i];

                    // Places jobNumber into contiguous memory slots
                    for (int j=i-1; j <(i+(counter-1));j++){
                        *n = jId;
                        n++;
                    }

                    // Set pointer to null
                    n=NULL;

                    // Print memory Table
                    printMemoryTable();
                    
                    // Set in memory for job to ture
                    j.inMem =true;
                
                    // Break out of loop
                    break;
			
                }  else   {
                    
                    // Go to next iteration of loop
                    continue;
			     }
		      } else {
			         std::cout << "Job with id: " << j.id << " cannot be placed into memory @ " << i <<endl;
			         continue;
		      }
	}
    
    // Set pointer to null
    n=NULL;
}


// There is a small error int this code 
// Jobs 
    
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