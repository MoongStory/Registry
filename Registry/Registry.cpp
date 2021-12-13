#include "Registry.h"

#include <atlbase.h>

MOONG::REGISTRY::Registry::Registry() :
TOTALBYTES(8192),
BYTEINCREMENT(4096)
{

}

int MOONG::REGISTRY::Registry::Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPCTSTR value)
{
	CRegKey reg_key;

	if (reg_key.Create(key_root, key_name) != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_CREATE;
	}

	if (reg_key.SetStringValue(value_name, value) != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_SET_VALUE;
	}

	if (reg_key.Close() != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
	}

	return EXIT_SUCCESS;
}

int MOONG::REGISTRY::Registry::Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD value)
{
	CRegKey reg_key;

	if (reg_key.Create(key_root, key_name) != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_CREATE;
	}

	if (reg_key.SetDWORDValue(value_name, value) != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_SET_VALUE;
	}

	if (reg_key.Close() != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
	}

	return EXIT_SUCCESS;
}

int MOONG::REGISTRY::Registry::Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPTSTR value, ULONG* chars)
{
	CRegKey reg_key;

	if (reg_key.Open(key_root, key_name, KEY_READ) != ERROR_SUCCESS)
	{
		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN;
	}

	if (reg_key.QueryStringValue(value_name, value, chars) != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_READ;
	}

	if (reg_key.Close() != ERROR_SUCCESS)
	{
		MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
	}

	return EXIT_SUCCESS;
}

int MOONG::REGISTRY::Registry::Read(HKEY key, std::string sub_key, std::string value_name, std::string& output)
{
	HKEY hkey_result = nullptr;

	LSTATUS lResult = RegOpenKeyExA(key, sub_key.c_str(), 0, KEY_READ, &hkey_result);

	if (lResult != ERROR_SUCCESS)
	{
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			return MOONG::REGISTRY::RETURN_CODE::ERROR_KEY_NOT_FOUND;
		}
		else
		{
			return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN_KEY_EX;
		}
	}

	DWORD buffer_size = this->TOTALBYTES;
	char* buffer = (char *)malloc(buffer_size);
	char* buffer_temp = nullptr;
	DWORD cb_data = buffer_size;
	
	lResult = RegQueryValueExA(hkey_result, value_name.c_str(), NULL, NULL, (LPBYTE)buffer, &cb_data);
	while (lResult == ERROR_MORE_DATA)
	{
		// Get a buffer that is big enough.

		buffer_size += this->BYTEINCREMENT;
		buffer_temp = buffer;
		buffer = (char *)realloc(buffer, buffer_size);
		if (buffer == nullptr)
		{
			free(buffer_temp);

			return MOONG::REGISTRY::RETURN_CODE::ERROR_REALLOC;
		}

		cb_data = buffer_size;

		lResult = RegQueryValueExA(hkey_result,
			value_name.c_str(),
			NULL,
			NULL,
			(LPBYTE)buffer,
			&cb_data);
	}

	if (lResult == ERROR_SUCCESS)
	{
		if (buffer != nullptr)
		{
			output = buffer;
		}
	}
	else
	{
		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_QUERY_VALUE_EX;
	}

	RegCloseKey(hkey_result);

	return EXIT_SUCCESS;
}

int MOONG::REGISTRY::Registry::Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD& value)
{
	CRegKey reg_key;

	if (reg_key.Open(key_root, key_name, KEY_READ) != ERROR_SUCCESS)
	{
		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN;
	}

	if (reg_key.QueryDWORDValue(value_name, value) != ERROR_SUCCESS)
	{
		return MOONG::REGISTRY::RETURN_CODE::ERROR_READ;
	}

	if (reg_key.Close() != ERROR_SUCCESS)
	{
		return MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
	}

	return EXIT_SUCCESS;
}

int MOONG::REGISTRY::Registry::Delete(HKEY hKeyRoot, std::string subKey)
{
	//LONG lResult;
	//HKEY hKey;
	//DWORD dwBytes = 100;
	//CString str = "abc";

	//// open Regstry Key
	//lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
	//	"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
	//	0, KEY_ALL_ACCESS, &hKey);
	//if (lResult != ERROR_SUCCESS)
	//{
	//	AfxMessageBox("Register Open Error");
	//}


	//lResult = RegDeleteValue(hKey, str);  // 삭제

	//if (lResult == ERROR_SUCCESS)
	//	AfxMessageBox("레지스터 삭제 성공");
	//else
	//	AfxMessageBox("실패당...ㅠㅠ");

	//RegCloseKey(hKey);

	return EXIT_SUCCESS;
}