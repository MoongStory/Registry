#include "Registry.h"

#include <strsafe.h>

MOONG::REGISTRY::Registry::Registry() :
TOTALBYTES(8192),
BYTEINCREMENT(4096)
{

}



LSTATUS MOONG::REGISTRY::Registry::Write(HKEY key, CStringA sub_key, CStringA value_name, CStringA data)
{
	HKEY key_result = NULL;
	DWORD disposition = 0;

	LSTATUS status = RegCreateKeyExA(key, sub_key.GetBuffer(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key_result, &disposition);
	if (status == ERROR_SUCCESS)
	{
		status = RegSetValueExA(key_result, value_name.GetBuffer(), 0, REG_SZ, (BYTE*)(data.GetBuffer()), data.GetLength());
		if (status != ERROR_SUCCESS)
		{
			RegCloseKey(key_result);

			return status;
		}
	}
	else
	{
		RegCloseKey(key_result);

		return status;
	}

	RegCloseKey(key_result);

	return ERROR_SUCCESS;
}

LSTATUS MOONG::REGISTRY::Registry::Read(HKEY key, CStringA sub_key, CStringA value_name, char* output, UINT output_length)
{
	HKEY key_result = nullptr;

	LSTATUS status = RegOpenKeyExA(key, sub_key.GetBuffer(), 0, KEY_READ, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	DWORD buffer_size = this->TOTALBYTES;
	char* buffer = (char*)malloc(buffer_size);
	char* buffer_temp = nullptr;
	DWORD cb_data = buffer_size;

	status = RegQueryValueExA(key_result, value_name.GetBuffer(), NULL, NULL, (LPBYTE)buffer, &cb_data);
	while (status == ERROR_MORE_DATA)
	{
		// Get a buffer that is big enough.

		buffer_size += this->BYTEINCREMENT;
		buffer_temp = buffer;
		buffer = (char*)realloc(buffer, buffer_size);
		if (buffer == nullptr)
		{
			free(buffer_temp);

			RegCloseKey(key_result);

			return MOONG::REGISTRY::RETURN_CODE::ERROR_REALLOC;
		}

		cb_data = buffer_size;

		status = RegQueryValueExA(key_result,
			value_name.GetBuffer(),
			NULL,
			NULL,
			(LPBYTE)buffer,
			&cb_data);
	}

	if (status == ERROR_SUCCESS)
	{
		if (buffer != nullptr)
		{
			StringCbCopyA(output, output_length, buffer);
		}
	}

	if (buffer != nullptr)
	{
		free(buffer);
	}

	RegCloseKey(key_result);

	return status;
}




//int MOONG::REGISTRY::Registry::Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPCTSTR value)
//{
//	CRegKey reg_key;
//
//	if (reg_key.Create(key_root, key_name) != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_CREATE;
//	}
//
//	if (reg_key.SetStringValue(value_name, value) != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_SET_VALUE;
//	}
//
//	if (reg_key.Close() != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
//	}
//
//	return EXIT_SUCCESS;
//}
//
//int MOONG::REGISTRY::Registry::Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD value)
//{
//	CRegKey reg_key;
//
//	if (reg_key.Create(key_root, key_name) != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_CREATE;
//	}
//
//	if (reg_key.SetDWORDValue(value_name, value) != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_SET_VALUE;
//	}
//
//	if (reg_key.Close() != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
//	}
//
//	return EXIT_SUCCESS;
//}
//
//
//
//int MOONG::REGISTRY::Registry::Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPTSTR value, ULONG* chars)
//{
//	CRegKey reg_key;
//
//	if (reg_key.Open(key_root, key_name, KEY_READ) != ERROR_SUCCESS)
//	{
//		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN;
//	}
//
//	if (reg_key.QueryStringValue(value_name, value, chars) != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_READ;
//	}
//
//	if (reg_key.Close() != ERROR_SUCCESS)
//	{
//		MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
//	}
//
//	return EXIT_SUCCESS;
//}
//
//int MOONG::REGISTRY::Registry::Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD& value)
//{
//	CRegKey reg_key;
//
//	if (reg_key.Open(key_root, key_name, KEY_READ) != ERROR_SUCCESS)
//	{
//		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN;
//	}
//
//	if (reg_key.QueryDWORDValue(value_name, value) != ERROR_SUCCESS)
//	{
//		return MOONG::REGISTRY::RETURN_CODE::ERROR_READ;
//	}
//
//	if (reg_key.Close() != ERROR_SUCCESS)
//	{
//		return MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
//	}
//
//	return EXIT_SUCCESS;
//}
//
//int MOONG::REGISTRY::Registry::Delete(HKEY hKeyRoot, std::string subKey)
//{
//	//LONG lResult;
//	//HKEY hKey;
//	//DWORD dwBytes = 100;
//	//CString str = "abc";
//
//	//// open Regstry Key
//	//lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
//	//	"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
//	//	0, KEY_ALL_ACCESS, &hKey);
//	//if (lResult != ERROR_SUCCESS)
//	//{
//	//	AfxMessageBox("Register Open Error");
//	//}
//
//
//	//lResult = RegDeleteValue(hKey, str);  // 삭제
//
//	//if (lResult == ERROR_SUCCESS)
//	//	AfxMessageBox("레지스터 삭제 성공");
//	//else
//	//	AfxMessageBox("실패당...ㅠㅠ");
//
//	//RegCloseKey(hKey);
//
//	return EXIT_SUCCESS;
//}