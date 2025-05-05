#include <sys/types.h>
#include <sys/sysctl.h>
#include <err.h>
#include <iostream>

using namespace std;


//printNumCPUs prints out the number of CPUs: sysctl HW_NCPU
void printNumCPUs(int[], size_t&); //I HAVE PROVIDED THIS FUNCTION

/************
 * The below function declarations are given and may not be changed.
 * Your assignment is to provide the implementations for these.
*/
//printPageSize prints out the software page size: sysctl HW_PAGESIZE
void printPageSize(int[], size_t&);

//printPhysicalMem prints out the total physical memory: sysctl HW_PHYSMEM
void printPhysicalMem(int[], size_t&);

//printMachineClass print out the machine class: sysctl HW_MACHINE
void printMachineClass(int[], size_t&, char*);

//printModel prints out the machine model: sysctl HW_MODEL
void printModel(int[], size_t&, char*);

//Do not change the main()
int main()
{
	int mib[2];
	size_t len;
	int choice=0;
	char* p;
	
	while(choice != 6)
	{
		cout<<"Options List: "<<endl;
		cout<<"  1: Number of CPUs"<<endl;
	     cout<<"  2: Page Size"<<endl;
		cout<<"  3: Total Physical Memory (bytes)"<<endl;
		cout<<"  4: Machine Class"<<endl;
		cout<<"  5: Model"<<endl;	
		cout<<"  6: Quit"<<endl;
		cout<<"Make Selection: ";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				printNumCPUs(mib, len);
				break;
			case 2: 
				printPageSize(mib, len);
				break;
			case 3:
				printPhysicalMem(mib, len);
				break;
			case 4: 
				printMachineClass(mib, len, p);
				break;
			case 5:
				printModel(mib, len, p);
				break;
			default:
				cout<<endl;
				cout<<"Good bye!"<<endl;
		}
	}
}

void printNumCPUs(int mib[], size_t& len)
{
	int cpuCount;
	
	mib[0] = CTL_HW;
	mib[1] = HW_NCPU;
	
	len = sizeof cpuCount;
	
	if(sysctl(mib, 2, &cpuCount, &len, nullptr, 0) == -1)
	{
		err(1, "sysctl");
	}
	else
	{
		cout<<endl;
		cout<<"********"<<endl;
		cout<<"Number of CPUs: "<< cpuCount << endl;
		cout<<endl;
	}
}
void printPageSize(int mib[], size_t& len)
{
	int pageSize; 

	mib[0] = CTL_HW;
	mib[1] = HW_PAGESIZE;

	len = sizeof pageSize;  // sizeof 

	if(sysctl(mib, 2, &pageSize, &len, nullptr, 0 ) == -1)
	{
		err(2, "couldn't find page num");
	}
	else{
		cout << endl; 
		cout << "********" << endl; 
		cout << "Page Size: " << pageSize << endl; 
		cout << endl; 
	}
}

void printPhysicalMem(int mib[], size_t& len)
{
	 unsigned long long mem; 

	 mib[0] = CTL_HW; 
	 mib[1] = HW_PHYSMEM;
	 
	 len = sizeof mem; 	

	 if(sysctl(mib, 2, &mem, &len, nullptr, 0 ) == -1)
	 {
		 err(3, "couldn't find physical memory"); 
	 }
	 else{
		cout << endl; 
		cout << "********" << endl; 
		cout << "Size of Memory (in Bytes): " << mem  << endl; 
		cout << endl; 
	}
}

void printMachineClass(int mib[], size_t& len, char* p)
{
	char mClass[256];  //buffer for machine class

	mib[0] = CTL_HW; 
	mib[1] = HW_MACHINE; 

	len = sizeof mClass; 

	if(sysctl(mib, 2, mClass, &len, nullptr, 0 ) == -1)
	{
		err(4, "couldn't get machine class");  
	}
	else{

		cout << endl; 
		cout << "********" << endl; 
		cout << "Machine Class: " << mClass << endl; 
		cout << endl; 
	}
}
void printModel(int mib[], size_t& len, char* p)
{
     char model[256]; //buffer to store the name 	

     mib[0] = CTL_HW; 
     mib[1] = HW_MODEL; 

     len = sizeof model; 
     
     if(sysctl(mib, 2, model, &len, nullptr, 0 ) == -1)
     {
	     err(5, "couldn't get the model"); 
     }
     else{
		cout << endl; 
		cout << "********" << endl; 
		cout << "Model Type: " << model  << endl; 
		cout << endl; 
	}
}
