#include <iostream>

#include "Registry.h"

int main()
{
	const DWORD dword_data = 20211222;
	const char* const dword_value_name = "dword value name";

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

	status = registry.Write(HKEY_CURRENT_USER, wchar_sub_key, dword_value_name, dword_data);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	char char_read_value[1024] = { 0 };
	status = registry.Read(HKEY_CURRENT_USER, wchar_sub_key, string_value_name.c_str(), char_read_value, _countof(char_read_value));
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::cout << "읽기 결과 (char)[" << char_read_value << "]" << std::endl;
	}

	wchar_t wchar_read_value[1024] = { 0 };
	status = registry.Read(HKEY_CURRENT_USER, wchar_sub_key, string_value_name.c_str(), wchar_read_value, _countof(wchar_read_value));
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		printf("읽기 결과 (wchar)[%ls]\n", wchar_read_value);
	}

	std::string string_read_value;
	status = registry.Read(HKEY_CURRENT_USER, wchar_sub_key, string_value_name.c_str(), string_read_value);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::cout << "읽기 결과 (string)[" << string_read_value << "]" << std::endl;
	}

	CStringA CStringA_read_value;
	status = registry.Read(HKEY_CURRENT_USER, wchar_sub_key, string_value_name.c_str(), CStringA_read_value);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::cout << "읽기 결과 (CStringA)[" << CStringA_read_value << "]" << std::endl;
	}

	CStringW CStringW_read_value;
	status = registry.Read(HKEY_CURRENT_USER, wchar_sub_key, string_value_name.c_str(), CStringW_read_value);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		printf("읽기 결과 (CStringW)[%ls]\n", CStringW_read_value.GetBuffer());
	}

	DWORD dword_read_value;
	status = registry.Read(HKEY_CURRENT_USER, wchar_sub_key, dword_value_name, &dword_read_value);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::cout << "읽기 결과 (DWORD)[" << dword_read_value << "]" << std::endl;
	}

	status = registry.Delete(HKEY_CURRENT_USER, wchar_sub_key, dword_value_name);

	status = registry.Delete(HKEY_CURRENT_USER, wchar_sub_key);

	return EXIT_SUCCESS;
}