#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


bool debug = true;
bool obscurantism = true;

void usage()
{
	printf("Usage: \nnormal usage:\n\ttasm-makeconfig <output path> <binary path> <binary name>\n");
	printf("\t\toutput path\t- path/to/dir where config will be created\n");
	printf("\t\tbinary path\t- path/to/dir where binary is located\n");
	printf("\t\tbinary name\t- name of binary file\n");
	printf("\n");
	printf("--build option:\n");
	printf("\ttasm-makeconfig --build <output path> <tasm path> <source path> <source name>\n");
	printf("\t\toutput path\t- path/to/dir where config will be created\n");
	printf("\t\ttasm path\t- path/to/dir where tasm binutils is located\n");
	printf("\t\tsource path\t- path/to/dir where asm source file is located\n");
	printf("\t\tbinary output path\t- path/to/dir where binary will be created\n");
	printf("\t\tsource name\t- name of asm source file\n");
}

void write_builder_config(
		std::ofstream& file, 
		const std::string path, 
		const std::string tasmPath, 
		const std::string sourcePath,
		const std::string outputPath,
		const std::string filename
		)
{
	std::string path_to_file = path + "/builder";
	file.open(path_to_file, std::ios::out);
	if (!file.is_open())
	{
		std::cerr << "File not found!\n";
		exit(1);
	}
	file << "[autoexec]\n";
	file << "@echo off\n";
	file << "mount c: \"" << tasmPath << "\"\n";
	file << "mount d: \"" << sourcePath << "\"\n";
	file << "mount f: \"" << outputPath << "\"\n";
	file << "path=z:\\;c:\\\n";
	file << "f:\n";
	file << "tasm d:\\" << filename << ".asm\n";
	file << "tlink " << filename << ".obj\n";
	if (!debug)
	{
		file << "cls\n";
		file << "exit\n";
	}
}

void write_runner_config(
		std::ofstream& file, 
		const std::string path, 
		const std::string binaryPath,
		const std::string filename
		)
{
	std::string path_to_file = path + "/runner";
	file.open(path_to_file, std::ios::out);
	if (!file.is_open())
	{
		std::cerr << "File not found!\n";
		exit(1);
	}
	file << "[autoexec]\n";
	file << "@echo off\n";
	file << "mount d: \"" << binaryPath << "\"\n";
	file << "path=z:\\;c:\\\n";
	file << "d:\n";
	file << "cls\n";
	file << "d:\\" << filename << '\n';
	if (obscurantism)
	{
		for (int i = 0; i < 3; ++i){
			file << "echo .\n";
		}
	}
	file << "pause\n";
	file << "exit\n";
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[])
{
	bool build = false;  // is build option enabled?
	std::ofstream config;  // output file - configuration for dosbox
	std::string build_option = "--build";
	
	if (cmdOptionExists(argv, argv + argc, build_option))
	{
		build = true;
	}
	if (build)
	{
		if (argc != 7)
		{
			usage();
			exit(1);
		}
		std::string path = argv[2];
		std::string tasmPath = argv[3];
		std::string sourcePath = argv[4];
		std::string outputPath = argv[5];
		std::string filename_ = argv[6];
		size_t pos = filename_.find('.');
		std::string filename = filename_.substr(0, pos);
		if (filename.size() > 8) // 8 - max len
		{
			std::cerr << "File max name length should be 8\n";
			exit(1);
		}
		write_builder_config(config, path, tasmPath, sourcePath, outputPath, filename);
		return 0;
	}
	if (argc != 4)
	{
		usage();
		exit(1);
	}
	std::string path = argv[1];
	std::string binaryPath = argv[2];
	std::string filename = argv[3];
	if (filename.size() > 12) // 8 - max len + 4 - ".exe" - len
	{
		std::cerr << "File max name length should be 8\n";
		exit(1);
	}
	write_runner_config(config, path, binaryPath, filename);
	std::cout << "hello, world!\n";
	return 0;
}
