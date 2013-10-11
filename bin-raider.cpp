#include <string>
#include <iostream>
#include <stdio.h>

std::string exec(std::string command)
{
	const char* cmd = command.c_str();
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

void parsePaths(std::string input, std::string * pathList)
{
	int index = 0;
	std::string delimiter = ":";
	size_t pos = 0;
	std::string token;
	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		token = input.substr(0, pos);
		//std::cout << token << std::endl;
		input.erase(0, pos + delimiter.length());
		pathList[index] = token;
		index++;
	}
	//std::cout << input << std::endl;
}

int main ()
{
	std::string pathList [16];
	
	std::string paths = exec("echo \"$PATH\"");
	//std::cout << paths << std::endl;
	parsePaths(paths, pathList);
	
	for (unsigned int i=0; i < sizeof(pathList); i++)
	{
		//std::cout << pathList[i] << std::endl;
		std::string command = "ls -l ";
		command.append(pathList[i]);
		std::cout << exec(command) << std::endl;
	}
	
	return 0;
}
