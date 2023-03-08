#include <iostream>

#include "Registry.h"

int main()
{
	const DWORD TEST_DWORD_DATA = 20211222;
	const char* const TEST_DWORD_VALUE_NAME = "dword value name";

	const char* const TEST_SUB_KEY = "SOFTWARE\\111_char_test";
	const char* const TEST_VALUE_NAME_DEFAULT = "";
	const char* const TEST_VALUE_NAME = "char value name";
	const char* const TEST_DATA_DEFAULT = "char data default";
	const char* const TEST_DATA = "char data";

	LSTATUS status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
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

	char char_read_value[1024] = { 0 };
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
		std::cout << "읽기 결과 (char)[" << char_read_value << "]" << std::endl;
	}

	wchar_t wchar_read_value[1024] = { 0 };
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME, wchar_read_value, _countof(wchar_read_value));
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
		std::cout << "읽기 결과 (string)[" << string_read_value.c_str() << "]" << std::endl;
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

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_DWORD_VALUE_NAME);

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY, TEST_VALUE_NAME_DEFAULT);

	status = MOONG::Registry::remove(HKEY_CURRENT_USER, TEST_SUB_KEY);

	return EXIT_SUCCESS;
}