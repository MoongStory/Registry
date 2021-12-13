#include <iostream>

#include "Registry.h"

int main()
{
	MOONG::REGISTRY::Registry registry;

	int return_code = 0;

	return_code = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT(""), TEXT("default_value"));

	LPTSTR result_lptstr = new TCHAR[256];
	ULONG chars = 256;
	registry.Read(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT(""), result_lptstr, &chars);
	printf("result_lptstr[%ls], result length[%d]\n", result_lptstr, chars);
	delete[] result_lptstr;

	std::string result_string;
	return_code = registry.Read(HKEY_CURRENT_USER, "SOFTWARE\\1111test", "", result_string);

	std::cout << "return_code[" << return_code << "], result_lptstr[" << result_string << "]" << std::endl;

	std::cout << std::endl;



	return_code = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_string"), TEXT("value_string"));

	result_lptstr = new TCHAR[256];
	chars = 256;
	registry.Read(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_string"), result_lptstr, &chars);
	printf("result_lptstr[%ls], result length[%d]\n", result_lptstr, chars);
	delete[] result_lptstr;

	result_string;
	return_code = registry.Read(HKEY_CURRENT_USER, "SOFTWARE\\1111test", "name_string", result_string);

	std::cout << "return_code[" << return_code << "], result_lptstr[" << result_string << "]" << std::endl;

	std::cout << std::endl;



	return_code = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_dword"), 20);

	DWORD result_dword = 0;
	return_code = registry.Read(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_dword"), result_dword);

	std::cout << "return_code[" << return_code << "], result_dword[" << result_dword << "]" << std::endl;

	return EXIT_SUCCESS;
}