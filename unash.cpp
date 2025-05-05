/* 
Divine G. 
2/13/25
CS420 
Exercise 3
Description: This file will create a very simple shell program. The shell accepts a string of commands separated by spaces and then spawns a new process, waits on that process to terminate, and then repeats the process.  The string of commands will be formatted with the name of the program to be run first, followed by a list of any arguments to be sent to the program.   
*/
#include <iostream>
#include <string>
#include <vector> 
#include <sstream>
#include <cstring>
#include <cstdlib> 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

string readLine();
char** tokenize(string);
void printTest(char**);
bool execute(char**);

int main()
{
    bool flag=1;
    string line;
    char** argList;

    while(flag)
    {
        cout<<"csis> ";

        line = readLine();
        argList = tokenize(line);

        // Check for exit AND free the memory (clear each pointer & null them, then delete da array)
        if (argList[0] != nullptr && strcmp(argList[0], "exit") == 0) {
            for (int i = 0; argList[i] != nullptr; i++) {
                delete[] argList[i];
            }
            delete[] argList;
            break; // To actually kill the process 
        }
        //IMPORTANT: comment the next line out when done testing tokenize().
        //printTest(argList);
        //***
        flag = execute(argList);
    }

}
/*
char** tokenize(string)
    This function is responsible for accepting the command string as a parameter.
    It returns a char** pointer.  The function dynamically allocates an array of 
    char* pointers equal to the number of (space delimited) words in the command string.
    Each char* pointer is dynamically allocated to exactly store one word from the command.
    Make the string pointed to by each char* pointer is NULL terminated (C-strings).
    Make sure the array of char* pointers pointed to by the char** pointer is NULL terminated.
    (This is what will be expected by the execvp function.) 
*/
char** tokenize(string line)
{
    //Declare variables
    vector<string> tokens; 
    string word;
    stringstream s(line); 
    
    //Extract each word from the param
    while(s >> word){ //loop till we reach end of line
        tokens.push_back(word); 
    }

    //Init args (new?)
    char** args = new char*[tokens.size() + 1];

    //Convert tokens to args (memcpy())
    for (size_t i = 0; i < tokens.size(); i++){ //need extra index for null character  
        args[i] = new char[tokens[i].length() + 1]; 
        strlcpy(args[i], tokens[i].c_str(), tokens[i].length() + 1);  
    }

    //Null terminate the args array (plus 1 or no plus 1??)
    args[tokens.size()] = nullptr; 
   
    return args; 
}

/*
bool execute(char** args)
    This function accepts the char** that points to the array of pointers to C-strings.  
    This function uses the fork() command to fork a brand new copy of itself.
    Then, for the child process, it makes use of execvp() to overwrite itself
    with a new program.  Call execvp properly making use of the char**.
    For the parent process (still running the shell program), it waits until
    the child process is terminated.  Make use of waitpid for this. 
*/
bool execute(char** args)
{
    pid_t pid = fork();
    if(pid < 0) { // parent
        perror("Error: Fork not forking"); 
        return true; 
    }

    else if (pid == 0){ // child
        if (execvp(args[0], args) == -1){
            perror("Error: Did not execute process" ); 
        }
        
        exit(EXIT_FAILURE);  
         
    }

    else {
        //Force the parent to wait 
        int status; 
        waitpid(pid, &status, 0); 
    }

    return true;  
}

string readLine()
{
    string line;
    getline(cin, line);
    return line;
}
void printTest(char** temp)
{
    int counter = 0;
    while(temp[counter]!=nullptr)
    {
        cout<<temp[counter]<<endl;
        counter++;
    }
}
