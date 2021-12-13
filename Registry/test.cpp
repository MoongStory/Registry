#include <iostream>

#include "Registry.h"

int main()
{
	MOONG::REGISTRY::Registry registry;

	int return_value = 0;

	return_value = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT(""), TEXT("default_value"));
	return_value = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_string"), TEXT("value_string"));
	return_value = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_dword"), 20);

	LPTSTR result_lptstr = new TCHAR[256];
	ULONG chars = 256;
	registry.Read(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_string"), result_lptstr, &chars);
	printf("result[%ls], result length[%d]\n", result_lptstr, chars);

	std::string result_string;
	return_value = registry.Read(HKEY_CURRENT_USER, "SOFTWARE\\1111test", "name_string", result_string);

	std::cout << "return_vlaue[" << return_value << "], result[" << result_string << "]" << std::endl;

	return EXIT_SUCCESS;
}