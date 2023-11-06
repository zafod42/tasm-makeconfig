#include <iostream>
#include <fstream>
#include <string>

void usage()
{
	printf("Usage: tasm-makeconfig <output path> <tasm path> <source path> <filename>\n");
	printf("\toutput path\t- path/to/dir where you want to see config file\n");
	printf("\ttasm path\t- path/to/dir where tasm binutils is located\n");
	printf("\tsource path\t- path/to/dir where asm source is located\n");
	printf("\tfilename\t- name of asm source file\n");
}

void write_config(
		std::ofstream& file, 
		const std::string path, 
		const std::string tasmPath, 
		const std::string sourcePath,
		const std::string filename
		)
{
	file.open(path, std::ios::out);
	if (!file.is_open())
	{
		std::cerr << "File not found!\n";
		exit(1);
	}
	file << "[autoexec]\n";
	file << "@echo off";
	file << "mount c: " << tasmPath << '\n';
	file << "mount d: " << sourcePath << '\n';
	file << "path=z:\\;c:\\\n";
	file << "d:\n";
	file << "cls\n";
	file << "d:\\" << filename << '\n';
	file << "pause\n";
	file << "exit\n";
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		usage();
	}	
	std::ofstream config;
	//std::string path = "/home/zafod/Documents/DOS_ASM/tasm-mkconfig/config.conf";
	std::string path = argv[1];
	std::string tasmPath = argv[2];
	std::string sourcePath = argv[3];
	std::string filename = argv[4];
	write_config(config, path);
	std::cout << "hello, world!\n";
	return 0;
}
