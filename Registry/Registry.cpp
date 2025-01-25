#include "Registry.h"

#include "../../ConvertDataType/ConvertDataType/ConvertDataType.h"

#include <strsafe.h>

const unsigned int MOONG::Registry::TOTALBYTES = 8192;
const unsigned int MOONG::Registry::BYTEINCREMENT = 4096;

//LSTATUS MOONG::Registry::write(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, const MOONG::STRING_TOOL::tstring data)
//{
//	HKEY key_result = NULL;
//	DWORD disposition = 0;
//
//	LSTATUS status = RegCreateKeyEx(key, sub_key.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key_result, &disposition);
//	if (status == ERROR_SUCCESS)
//	{
//		status = RegSetValueEx(key_result, value.c_str(), 0, REG_SZ, (const BYTE*)(data.c_str()), (DWORD)data.length());
//		if (status != ERROR_SUCCESS)
//		{
//			RegCloseKey(key_result);
//
//			return status;
//		}
//	}
//	else
//	{
//		RegCloseKey(key_result);
//
//		return status;
//	}
//
//	RegCloseKey(key_result);
//
//	return ERROR_SUCCESS;
//}
//
//LSTATUS MOONG::Registry::write(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, const DWORD data)
//{
//	HKEY key_result = NULL;
//	DWORD disposition = 0;
//
//	LSTATUS status = RegCreateKeyEx(key, sub_key.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key_result, &disposition);
//	if (status == ERROR_SUCCESS)
//	{
//		status = RegSetValueEx(key_result, value.c_str(), 0, REG_DWORD, (const BYTE*)(&data), sizeof(data));
//		if (status != ERROR_SUCCESS)
//		{
//			RegCloseKey(key_result);
//
//			return status;
//		}
//	}
//	else
//	{
//		RegCloseKey(key_result);
//
//		return status;
//	}
//
//	RegCloseKey(key_result);
//
//	return ERROR_SUCCESS;
//}

LSTATUS MOONG::Registry::write(const HKEY key_root, const MOONG::STRING_TOOL::tstring key_name, const MOONG::STRING_TOOL::tstring value_name, const MOONG::STRING_TOOL::tstring value)
{
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Create(key_root, key_name.c_str());
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.SetStringValue(value_name.c_str(), value.c_str(), REG_SZ);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.Close();
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return EXIT_SUCCESS;
}

LSTATUS MOONG::Registry::write(const HKEY key_root, const MOONG::STRING_TOOL::tstring key_name, const MOONG::STRING_TOOL::tstring value_name, DWORD value)
{
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Create(key_root, key_name.c_str());
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.SetDWORDValue(value_name.c_str(), value);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.Close();
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return EXIT_SUCCESS;
}

LSTATUS MOONG::Registry::read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, TCHAR* const output, const unsigned int output_length)
{

	try
	{
		HKEY key_result = NULL;

		LSTATUS status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_READ, &key_result);
		if (status != ERROR_SUCCESS)
		{
			return status;
		}

		DWORD buffer_size = MOONG::Registry::TOTALBYTES;
		TCHAR* buffer = new TCHAR[buffer_size];
		TCHAR* buffer_temp = NULL;
		DWORD cb_data = buffer_size;

		status = RegQueryValueEx(key_result, value.c_str(), NULL, NULL, (LPBYTE)buffer, &cb_data);
		while (status == ERROR_MORE_DATA)
		{
			// Get a buffer that is big enough.
			buffer_size += MOONG::Registry::BYTEINCREMENT;
			buffer_temp = buffer;
			buffer = (TCHAR*)realloc(buffer, buffer_size);
			if (buffer == NULL)
			{
				free(buffer_temp);

				RegCloseKey(key_result);

				return MOONG::REGISTRY::RETURN::FAILURE::REALLOC;
			}

			cb_data = buffer_size;

			status = RegQueryValueEx(key_result,
				value.c_str(),
				NULL,
				NULL,
				(LPBYTE)buffer,
				&cb_data);
		}

		if (status == ERROR_SUCCESS)
		{
			if (buffer != NULL)
			{
				StringCchCopy(output, output_length, buffer);
			}
		}

		if (buffer != NULL)
		{
			delete buffer;
		}

		RegCloseKey(key_result);

		return status;
	}
	catch (const std::exception& exception)
	{
		throw exception;
	}
}

LSTATUS MOONG::Registry::read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, MOONG::STRING_TOOL::tstring& output)
{
	try
	{
		HKEY key_result = NULL;

		LSTATUS status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_READ, &key_result);
		if (status != ERROR_SUCCESS)
		{
			return status;
		}

		DWORD buffer_size = MOONG::Registry::TOTALBYTES;
		TCHAR* buffer = new TCHAR[buffer_size];
		TCHAR* buffer_temp = NULL;
		DWORD cb_data = buffer_size;

		status = RegQueryValueEx(key_result, value.c_str(), NULL, NULL, (LPBYTE)buffer, &cb_data);
		while (status == ERROR_MORE_DATA)
		{
			// Get a buffer that is big enough.
			buffer_size += MOONG::Registry::BYTEINCREMENT;
			buffer_temp = buffer;
			buffer = (TCHAR*)realloc(buffer, buffer_size);
			if (buffer == NULL)
			{
				free(buffer_temp);

				RegCloseKey(key_result);

				return MOONG::REGISTRY::RETURN::FAILURE::REALLOC;
			}

			cb_data = buffer_size;

			status = RegQueryValueEx(key_result, value.c_str(), NULL, NULL, (LPBYTE)buffer, &cb_data);
		}

		if (status == ERROR_SUCCESS)
		{
			if (buffer != NULL)
			{
				output = buffer;
			}
		}

		if (buffer != NULL)
		{
			delete buffer;
		}

		RegCloseKey(key_result);

		return status;
	}
	catch (const std::exception& exception)
	{
		throw exception;
	}
}

LSTATUS MOONG::Registry::read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, DWORD* output)
{
	HKEY key_result = NULL;

	LSTATUS status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_READ, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	DWORD buffer = 0;
	DWORD cb_data = sizeof(DWORD);

	status = RegQueryValueEx(key_result, value.c_str(), NULL, NULL, (LPBYTE)(&buffer), &cb_data);
	if (status != ERROR_SUCCESS)
	{
		RegCloseKey(key_result);

		return status;
	}

	*output = buffer;

	RegCloseKey(key_result);

	return status;
}

LSTATUS MOONG::Registry::remove(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value)
{
	HKEY key_result = NULL;

	LSTATUS status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_ALL_ACCESS, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	status = RegDeleteValue(key_result, value.c_str());

	RegCloseKey(key_result);

	return status;
}

LSTATUS MOONG::Registry::remove(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key)
{
#if _MSC_VER > 1200
	LSTATUS status = RegDeleteKeyEx(key, sub_key.c_str(), KEY_ALL_ACCESS, 0);
#else
	LSTATUS status = RegDeleteKeyA(key, sub_key.c_str());
#endif

	return status;
}

const int MOONG::Registry::get_reg_sub_keys(const HKEY hKey, const MOONG::STRING_TOOL::tstring subKey, std::vector<MOONG::STRING_TOOL::tstring>& subKeys)
{
	HKEY hkResult = NULL;
	LONG lStatus = 0;
	DWORD dwIndex = 0;
	TCHAR szKeyName[MAX_PATH] = { 0 };
	DWORD cbName = MAX_PATH;
	int returnValue = EXIT_FAILURE;

	if (RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_READ, &hkResult) != ERROR_SUCCESS)
	{
		returnValue = EXIT_FAILURE;
	}
	else
	{
		while ((lStatus = RegEnumKeyEx(hkResult,
			dwIndex,
			szKeyName,
			&cbName,
			NULL,
			NULL,
			NULL,
			NULL)) != ERROR_NO_MORE_ITEMS)
		{
			if (lStatus == ERROR_SUCCESS)
			{
				HKEY hItem = NULL;

				subKeys.push_back(szKeyName);

				ZeroMemory(szKeyName, sizeof(szKeyName));

				returnValue = EXIT_SUCCESS;
			}

			dwIndex++;
			cbName = MAX_PATH;
		}

		RegCloseKey(hkResult);
	}

	return returnValue;
}

// TODO: 특정 레지스트리 키 하위의 특정 이름의 값들을 가져오는 함수 추가. Read 함수로???






//
//
//
//int MOONG::Registry::Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value, LPTSTR value, ULONG* chars)
//{
//	CRegKey reg_key;
//
//	if (reg_key.Open(key_root, key_name, KEY_READ) != ERROR_SUCCESS)
//	{
//		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN;
//	}
//
//	if (reg_key.QueryStringValue(value, value, chars) != ERROR_SUCCESS)
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
//int MOONG::Registry::Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value, DWORD& value)
//{
//	CRegKey reg_key;
//
//	if (reg_key.Open(key_root, key_name, KEY_READ) != ERROR_SUCCESS)
//	{
//		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN;
//	}
//
//	if (reg_key.QueryDWORDValue(value, value) != ERROR_SUCCESS)
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