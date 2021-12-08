#include <iostream>

#include "Registry.h"

int main()
{
	MOONG::REGISTRY::Registry registry;

	std::string result;

	int return_value = registry.Read(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", "ProgID", result);

	std::cout << "return_vlaue[" << return_value << "], result[" << result << "]" << std::endl;

	return EXIT_SUCCESS;
}