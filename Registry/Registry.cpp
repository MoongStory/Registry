#include "Registry.h"

#include <strsafe.h>

const unsigned int MOONG::Registry::TOTAL_BYTES = 1024;

LSTATUS MOONG::Registry::write(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, const MOONG::STRING_TOOL::tstring data)
{
#if _MSC_VER > 1200
		CRegKey reg_key;
	
		LSTATUS return_status = reg_key.Create(key, sub_key.c_str());
		if (return_status != ERROR_SUCCESS)
		{
			return return_status;
		}
	
		return_status = reg_key.SetStringValue(value.c_str(), data.c_str(), REG_SZ);
		if (return_status != ERROR_SUCCESS)
		{
			return return_status;
		}
	
		return_status = reg_key.Close();
		if (return_status != ERROR_SUCCESS)
		{
			return return_status;
		}
	
		return return_status;
#else
	LSTATUS return_status = RegSetKeyValue(key, sub_key.c_str(), value.c_str(), REG_SZ, data.c_str(), (DWORD)((data.length() + 1) * sizeof(TCHAR)));

	return return_status;
#endif
}

LSTATUS MOONG::Registry::write(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, const DWORD data)
{
#if _MSC_VER > 1200
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Create(key, sub_key.c_str());
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.SetDWORDValue(value.c_str(), data);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.Close();
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return return_status;
#else
	LSTATUS return_status = RegSetKeyValue(key, sub_key.c_str(), value.c_str(), REG_DWORD, &data, sizeof(DWORD));

	return return_status;
#endif
}

LSTATUS MOONG::Registry::read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, TCHAR* const output, const DWORD output_length)
{
    HKEY key_result = NULL;

    LSTATUS return_status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_READ, &key_result);
    if (return_status != ERROR_SUCCESS)
    {
        return return_status;
    }

    DWORD dataType = 0;
    return_status = RegQueryValueEx(key_result, value.c_str(), NULL, &dataType, (LPBYTE)output, (LPDWORD)(&output_length));
    if (return_status != ERROR_SUCCESS)
    {
        RegCloseKey(key_result);

        return return_status;
    }

    if (dataType != REG_SZ)
    {
        RegCloseKey(key_result);

        return ERROR_INVALID_DATA;
    }

    RegCloseKey(key_result);

    return ERROR_SUCCESS;
}

LSTATUS MOONG::Registry::read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, MOONG::STRING_TOOL::tstring& output)
{
	TCHAR temp[MOONG::Registry::TOTAL_BYTES] = { 0 };

	LSTATUS return_value = read(key, sub_key, value, temp, _countof(temp));

	output = temp;

	return return_value;
}

LSTATUS MOONG::Registry::read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, DWORD* output)
{
	HKEY key_result = NULL;

	LSTATUS return_status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_READ, &key_result);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	DWORD dataType = 0;
	DWORD cb_data = sizeof(DWORD);
	return_status = RegQueryValueEx(key_result, value.c_str(), NULL, &dataType, (LPBYTE)output, &cb_data);
	if (return_status != ERROR_SUCCESS)
	{
		RegCloseKey(key_result);

		return return_status;
	}

	if (dataType != REG_DWORD)
	{
		RegCloseKey(key_result);

		return ERROR_INVALID_DATA;
	}

	RegCloseKey(key_result);

	return ERROR_SUCCESS;
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
	int return_value = EXIT_FAILURE;

	if (RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_READ, &hkResult) != ERROR_SUCCESS)
	{
		return_value = EXIT_FAILURE;
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

				return_value = EXIT_SUCCESS;
			}

			dwIndex++;
			cbName = MAX_PATH;
		}

		RegCloseKey(hkResult);
	}

	return return_value;
}








//
//
//
//int MOONG::Registry::Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_0, LPTSTR value_1, ULONG* chars)
//{
//	CRegKey reg_key;
//
//	if (reg_key.Open(key_root, key_name, KEY_READ) != ERROR_SUCCESS)
//	{
//		//return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN;
//	}
//
//	if (reg_key.QueryStringValue(value_0, value_1, chars) != ERROR_SUCCESS)
//	{
//		//MOONG::REGISTRY::RETURN_CODE::ERROR_READ;
//	}
//
//	if (reg_key.Close() != ERROR_SUCCESS)
//	{
//		//MOONG::REGISTRY::RETURN_CODE::ERROR_CLOSE;
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