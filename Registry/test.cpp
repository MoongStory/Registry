#include <iostream>

#include "Registry.h"

int main()
{
	const char* const char_sub_key = "SOFTWARE\\111_char_test";
	const char* const char_value_name_default = "";
	const char* const char_value_name = "char value name";
	const char* const char_data_default = "char data";

	const wchar_t* const wchar_sub_key = L"SOFTWARE\\111_wchar_test";
	const wchar_t* const wchar_value_name_default = L"";
	const wchar_t* const wchar_value_name = L"wchar value name";
	const wchar_t* const wchar_data_default = L"wchar data";

	const TCHAR* const tchar_sub_key = TEXT("SOFTWARE\\111_tchar_test");
	const TCHAR* const tchar_value_name_default = TEXT("");
	const TCHAR* const tchar_value_name = TEXT("tchar value name");
	const TCHAR* const tchar_data_default = TEXT("tchar data");

	const std::string string_sub_key = "SOFTWARE\\111_string_test";
	const std::string string_value_name_default = "";
	const std::string string_value_name = "string value name";
	const std::string string_data_default = "string data";

	MOONG::REGISTRY::Registry registry;

	LSTATUS status = registry.Write(HKEY_CURRENT_USER, wchar_sub_key, char_value_name_default, tchar_data_default);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = registry.Write(HKEY_CURRENT_USER, wchar_sub_key, string_value_name.c_str(), char_data_default);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	char read_value[1024] = { 0 };
	status = registry.Read(HKEY_CURRENT_USER, wchar_sub_key, string_value_name.c_str(), read_value, _countof(read_value));
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::cout << "읽기 결과[" << read_value << "]" << std::endl;
	}

	//int return_code = 0;

	//return_code = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT(""), TEXT("default_value"));

	//LPTSTR result_lptstr = new TCHAR[256];
	//ULONG chars = 256;
	//registry.Read(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT(""), result_lptstr, &chars);
	//printf("result_lptstr[%ls], result length[%d]\n", result_lptstr, chars);
	//delete[] result_lptstr;

	//std::string result_string;
	//return_code = registry.Read(HKEY_CURRENT_USER, "SOFTWARE\\1111test", "", result_string);

	//std::cout << "return_code[" << return_code << "], result_lptstr[" << result_string << "]" << std::endl;

	//std::cout << std::endl;



	//return_code = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_string"), TEXT("value_string"));

	//result_lptstr = new TCHAR[256];
	//chars = 256;
	//registry.Read(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_string"), result_lptstr, &chars);
	//printf("result_lptstr[%ls], result length[%d]\n", result_lptstr, chars);
	//delete[] result_lptstr;

	//result_string;
	//return_code = registry.Read(HKEY_CURRENT_USER, "SOFTWARE\\1111test", "name_string", result_string);

	//std::cout << "return_code[" << return_code << "], result_lptstr[" << result_string << "]" << std::endl;

	//std::cout << std::endl;



	//return_code = registry.Write(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_dword"), 20);

	//DWORD result_dword = 0;
	//return_code = registry.Read(HKEY_CURRENT_USER, TEXT("SOFTWARE\\1111test"), TEXT("name_dword"), result_dword);

	//std::cout << "return_code[" << return_code << "], result_dword[" << result_dword << "]" << std::endl;

	return EXIT_SUCCESS;
}