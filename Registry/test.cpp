#include <iostream>

#include "Registry.h"

int main()
{
	const DWORD TEST_DWORD_DATA = 20250125;
	const TCHAR* const TEST_DWORD_VALUE_NAME = TEXT("dword value name");

	const TCHAR* const TEST_SUB_KEY_0 = TEXT("SOFTWARE\\000_char_test");
	const TCHAR* const TEST_SUB_KEY_00 = TEXT("SOFTWARE\\000_char_test\\000");
	const TCHAR* const TEST_SUB_KEY_000 = TEXT("SOFTWARE\\000_char_test\\000\\000");
	const TCHAR* const TEST_SUB_KEY_01 = TEXT("SOFTWARE\\000_char_test\\111");

	const TCHAR* const TEST_SUB_KEY_1 = TEXT("SOFTWARE\\111_char_test");
	const TCHAR* const TEST_SUB_KEY_10 = TEXT("SOFTWARE\\111_char_test\\000");
	const TCHAR* const TEST_SUB_KEY_100 = TEXT("SOFTWARE\\111_char_test\\000\\000");
	const TCHAR* const TEST_SUB_KEY_11 = TEXT("SOFTWARE\\111_char_test\\111");

	const TCHAR* const TEST_VALUE_NAME_DEFAULT = TEXT("");
	const TCHAR* const TEST_VALUE_NAME = TEXT("char value name");
	const TCHAR* const TEST_DATA_DEFAULT = TEXT("char data default");
	const TCHAR* const TEST_DATA = TEXT("char data");

#pragma region 0
	LSTATUS status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_00, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_000, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
	
	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_01, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_VALUE_NAME, TEST_DATA);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_DWORD_VALUE_NAME, TEST_DWORD_DATA);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
#pragma endregion 0

#pragma region 1
	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_1, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_10, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_100, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_11, TEST_VALUE_NAME_DEFAULT, TEST_DATA_DEFAULT);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_1, TEST_VALUE_NAME, TEST_DATA);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}

	status = MOONG::Registry::write(HKEY_CURRENT_USER, TEST_SUB_KEY_1, TEST_DWORD_VALUE_NAME, TEST_DWORD_DATA);
	if (status != ERROR_SUCCESS)
	{
		char* message = NULL;
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, status, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&message, 0, NULL);

		std::cout << "Write fail error_code[" << status << "], message[" << message << "]" << std::endl;

		LocalFree(message);
	}
#pragma endregion 1

	TCHAR char_read_value_default[1024] = { 0 };
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_VALUE_NAME_DEFAULT, char_read_value_default, _countof(char_read_value_default));
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
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_VALUE_NAME, char_read_value, _countof(char_read_value));
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
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_VALUE_NAME, string_read_value);
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

	DWORD dword_read_value = 0;
	status = MOONG::Registry::read(HKEY_CURRENT_USER, TEST_SUB_KEY_0, TEST_DWORD_VALUE_NAME, &dword_read_value);
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
	MOONG::Registry::get_child_keys(HKEY_CURRENT_USER, TEST_SUB_KEY_0, sub_keys);
	for (auto i : sub_keys)
	{
		tcout << "get_reg_sub_keys[" << i << "]" << std::endl;
	}

	// 하위 키 남아있는 상태에서 삭제 안 되는지 확인.
	status = MOONG::Registry::delete_key_safely(HKEY_CURRENT_USER, TEST_SUB_KEY_0);

	// 하위 키 남아있는 상태에서 삭제 되는지 확인.
	status = MOONG::Registry::delete_key(HKEY_CURRENT_USER, TEST_SUB_KEY_0);

	// 값 삭제 되는지 확인.
	status = MOONG::Registry::delete_value(HKEY_CURRENT_USER, TEST_SUB_KEY_1, TEST_DWORD_VALUE_NAME);
	status = MOONG::Registry::delete_value(HKEY_CURRENT_USER, TEST_SUB_KEY_1, TEST_VALUE_NAME);
	status = MOONG::Registry::delete_value(HKEY_CURRENT_USER, TEST_SUB_KEY_1, TEST_VALUE_NAME_DEFAULT);

	// 하위 키 없을 때 삭제 되는지 확인.
	status = MOONG::Registry::delete_key_safely(HKEY_CURRENT_USER, TEST_SUB_KEY_100);
	status = MOONG::Registry::delete_key_safely(HKEY_CURRENT_USER, TEST_SUB_KEY_10);
	status = MOONG::Registry::delete_key_safely(HKEY_CURRENT_USER, TEST_SUB_KEY_11);
	status = MOONG::Registry::delete_key_safely(HKEY_CURRENT_USER, TEST_SUB_KEY_1);

	return EXIT_SUCCESS;
}