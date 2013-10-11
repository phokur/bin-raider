/*
 * Bin-Raider v0.0
 * Program will return a list of all executables the system
 * has in its numerous paths.
 * */

#include <string>
#include <iostream>
#include <stdio.h>

// Run command and return result as a string
std::string exec(std::string command)
{
	// Get const char* from input string command (suppress warnings)
	const char* cmd = command.c_str();
	// Run input command and return result as a string
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

// Given a delimited string, parse the strings into a string array
void parsePaths(std::string input, std::string * pathList, int & pathIndex)
{
	std::string delimiter = ":";
	size_t pos = 0;
	// Loop through input and insert delimited values into pathList
	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		pathList[pathIndex] = input.substr(0, pos);
		input.erase(0, pos + delimiter.length());
		pathIndex++;
	}
	// Get the final delimited value
	pathList[pathIndex] = input;
}

// Main method
int main ()
{
	// Array to hold system paths
	std::string pathList [16];
	int pathIndex = 0;
	// Result of $Path (colon delimited string)
	std::string paths = exec("echo \"$PATH\"");
	// Parse delimited string into pathList array
	parsePaths(paths, pathList, pathIndex);
	// Loop through pathList
	for (int i=0; i <= pathIndex; i++)
	{
		// Print path
		std::cout << pathList[i] << std::endl;
		// Print ll for path
		std::string command = "ls -l ";
		command.append(pathList[i]);
		std::cout << exec(command) << std::endl;
	}
	
	return 0;
}

