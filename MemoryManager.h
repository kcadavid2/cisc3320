#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <iostream>
using namespace std;


class MemoryManager{
public: 
    
    // NEED PLACE TO PUT STATIC VARIABLE FOR SIZE OF ARRAY (100)
    // WHERE TO PUT?
    // static int numofJobs = 100;
    
    int arrayOfJobs[/* numofJobs */]; 


// -----------------------------------------
// INTIALIZE MEMORY ARRAY TO JOB ID
void initJobsArray( int a[] , int num ){
	for (int i = 0; i < num; i++){
		a[i]=0;
	}
}
    

// -----------------------------------------
// RETURN AMOUNT OF MEMORY
int getFreeMemory(int* x, int num){
	int memoryBlocks = 0;
	// COUNT FREE MEMORY BLOCKS
	for (int i = 0; i < num; i++){
		if (x[i] == 0){
			memoryBlocks++;
		}
	}
	// CALCULATE AMOUNT OF MEMORY
	memoryBlocks = memoryBlocks*1000;
	return  memoryBlocks;
}

// -----------------------------------------
// TEST IF JOB WILL FIT INTO MEMORY
bool jobFit(Job &j, int* arr, int arrSize){
	// IF JOBS < FREE MEMORY AVAILABLE RETURN TRUE ELSE RETURN FALSE
	if (j.size < getFreeMemory(arr,arrSize)){
		return true;
	} else {
		cout << "Not enough memory to store job!" <<endl;
		return false;
	}
}

// -----------------------------------------
// PLACE JOB INTO MEMORY
void placeJob(Job &j, int* arr, int arrSize){
	// DIVIDES JOB SIZE BY 1000 TO DETERMINE HOW MANY MEMORY LOCATIONS JOB WILL USE
	int x = j.size /1000;

	// TEST IF JOB WILL FIT INTO MEMORY
	// COMPARING JOB SIZE WITH TOTAL MEMORY AVAILABLE
	if (jobFit(j,arr,arrSize)){

		// INSERT JOB LOCATIONS INTO A SET AND INTO MEMORY LOCATION
		for (int i=0; i < arrSize; i++){
			if (arr[i] == 0 && x !=0){
				arr[i] = j.id;
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


// --------------------------------------------
//PRINT MEMORY MANAGEMENT TABLE
void printMemoryTable(int* arr, int num){
	for (int i =0; i <num; i++){
		cout << "Place in Memory | " << i << " | Job ID # | " <<  arr[i] << endl;
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
	if (j.id !=0){
		while(it != j.joblocations.end()){
			arr[*it] =0;
			++it;
		}
	} else {
		cout << "Invalid JobID, no job in memory location." <<endl;
	}
	// PRINT OUT JOBID REMOVAL CONFIRMATION
	std::cout << "Job with id# " << j.id << " and size " <<  j.size << "k was successfully removed from memory" << endl;

	// PRINTS OUT FREE MEMORY AVAILABLE AFTER JOB REMOVAL
	std::cout << "You now have " << getFreeMemory(arr,arrSize) << " of free memory available" <<endl;

	// PRINT MEMORY TABLE
	printMemoryTable(arr,arrSize);
}


};

#endif