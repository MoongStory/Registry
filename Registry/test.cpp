#include <iostream>

#include "Registry.h"

int main()
{
	const DWORD TEST_DWORD_DATA = 20211222;
	const TCHAR* const TEST_DWORD_VALUE_NAME = TEXT("dword value name");

	const TCHAR* const TEST_SUB_KEY = TEXT("SOFTWARE\\111_char_test");
	const TCHAR* const TEST_SUB_KEY_0 = TEXT("SOFTWARE\\111_char_test\\000");
	const TCHAR* const TEST_SUB_KEY_1 = TEXT("SOFTWARE\\111_char_test\\111");
	const TCHAR* const TEST_VALUE_NAME_DEFAULT = TEXT("");
	const TCHAR* const TEST_VALUE_NAME = TEXT("char value name");
	const TCHAR* const TEST_DATA_DEFAULT = TEXT("char data default");
	const TCHAR* const TEST_DATA = TEXT("char data");

	LSTATUS status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	
	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_1, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME, TEST_DATA);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_DWORD_VALUE_NAME, TEST_DWORD_DATA);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	TCHAR char_read_value_default[1024] = { 0 };
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME_DEFAULT, char_read_value_default, _countof(char_read_value_default));
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::wcout << "읽기 결과 (char)[" << char_read_value_default << "]" << std::endl;
	}

	TCHAR char_read_value[1024] = { 0 };
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME, char_read_value, _countof(char_read_value));
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::wcout << "읽기 결과 (char)[" << char_read_value << "]" << std::endl;
	}

	MOONG::STRING_TOOL::tstring string_read_value;
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME, string_read_value);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	else
	{
		std::wcout << "읽기 결과 (string)[" << string_read_value.c_str() << "]" << std::endl;
	}

	DWORD dword_read_value;
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_DWORD_VALUE_NAME, &dword_read_value);
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

	std::vector<MOONG::STRING_TOOL::tstring> sub_keys;
	MOONG::Registry::get_reg_sub_keys(HKEY_CURRENT_USER, TEST_SUB_KEY, sub_keys);
	for (auto i : sub_keys)
	{
		tcout << "get_reg_sub_keys[" << i << "]" << std::endl;
	}

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_DWORD_VALUE_NAME);

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME);

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME_DEFAULT);

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY_0);

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY_1);

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY);

	return EXIT_SUCCESS;
}