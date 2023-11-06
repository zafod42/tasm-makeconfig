#include <iostream>
#include <fstream>
#include <string>

void usage()
{
	printf("tasm-makeconfig <path>");
}

void write_config(std::ofstream& file, const std::string path)
{
	file.open(path, std::ios::out);
	if (!file.is_open())
	{
		std::cerr << "File not found!\n";
		exit(1);
	}
	file << "hello, world\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		usage();
	}	
	std::ofstream config;
	//std::string path = "/home/zafod/Documents/DOS_ASM/tasm-mkconfig/config.conf";
	std::string path = argv[1];
	write_config(config, path);
	std::cout << "hello, world!\n";
	return 0;
}
