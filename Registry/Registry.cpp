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
			reg_key.Close();

			return return_status;
		}
	
		return reg_key.Close();
#else
	return RegSetKeyValue(key, sub_key.c_str(), value.c_str(), REG_SZ, data.c_str(), (DWORD)((data.length() + 1) * sizeof(TCHAR)));
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
		reg_key.Close();

		return return_status;
	}

	return reg_key.Close();
#else
	return RegSetKeyValue(key, sub_key.c_str(), value.c_str(), REG_DWORD, &data, sizeof(DWORD));
#endif
}

LSTATUS MOONG::Registry::read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, TCHAR* const output, const DWORD output_length)
{
#if _MSC_VER > 1200
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Open(key, sub_key.c_str(), KEY_READ);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.QueryStringValue(value.c_str(), output, (ULONG*)(&output_length));
	if (return_status != ERROR_SUCCESS)
	{
		reg_key.Close();

		return return_status;
	}

	return reg_key.Close();
#else
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

	return RegCloseKey(key_result);
#endif
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
#if _MSC_VER > 1200
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Open(key, sub_key.c_str(), KEY_READ);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.QueryDWORDValue(value.c_str(), *output);
	if (return_status != ERROR_SUCCESS)
	{
		reg_key.Close();

		return return_status;
	}

	return reg_key.Close();
#else
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

	return_status = RegCloseKey(key_result);

	return return_status;
#endif
}

LSTATUS MOONG::Registry::delete_value(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value)
{
#if _MSC_VER > 1200
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Open(key, sub_key.c_str(), KEY_ALL_ACCESS);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.DeleteValue(value.c_str());
	if (return_status != ERROR_SUCCESS)
	{
		reg_key.Close();

		return return_status;
	}

	return reg_key.Close();
#else
	HKEY key_result = NULL;

	LSTATUS status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_ALL_ACCESS, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	status = RegDeleteValue(key_result, value.c_str());

	RegCloseKey(key_result);

	return status;
#endif
}

LSTATUS MOONG::Registry::delete_key(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key)
{
#if _MSC_VER > 1200
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Open(key, sub_key.substr(0, sub_key.rfind(TEXT("\\"))).c_str(), KEY_ALL_ACCESS);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.RecurseDeleteKey(sub_key.substr(sub_key.rfind(TEXT("\\")) + 1).c_str());
	if (return_status != ERROR_SUCCESS)
	{
		reg_key.Close();

		return return_status;
	}

	return reg_key.Close();
#else
	return RegDeleteTree(key, sub_key.c_str());
#endif
}

LSTATUS MOONG::Registry::delete_key_safely(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key)
{
#if _MSC_VER > 1200
	CRegKey reg_key;

	LSTATUS return_status = reg_key.Open(key, sub_key.substr(0, sub_key.rfind(TEXT("\\"))).c_str(), KEY_ALL_ACCESS);
	if (return_status != ERROR_SUCCESS)
	{
		return return_status;
	}

	return_status = reg_key.DeleteSubKey(sub_key.substr(sub_key.rfind(TEXT("\\")) + 1).c_str());
	if (return_status != ERROR_SUCCESS)
	{
		reg_key.Close();

		return return_status;
	}

	return reg_key.Close();
#else
	return RegDeleteKeyEx(key, sub_key.c_str(), KEY_ALL_ACCESS, 0);

	//return RegDeleteKey(key, sub_key.c_str()); // Visual Studio 버전 낮아서 RegDeleteKeyEx() 함수 지원이 안 될 경우 사용.
#endif
}

const int MOONG::Registry::get_reg_sub_keys(const HKEY hKey, const MOONG::STRING_TOOL::tstring sub_key, std::vector<MOONG::STRING_TOOL::tstring>& output_sub_keys)
{
	HKEY hkResult = NULL;
	LONG lStatus = 0;
	DWORD dwIndex = 0;
	TCHAR szKeyName[MAX_PATH] = { 0 };
	DWORD cbName = MAX_PATH;
	int return_value = EXIT_FAILURE;

	if (RegOpenKeyEx(hKey, sub_key.c_str(), 0, KEY_READ, &hkResult) != ERROR_SUCCESS)
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

				output_sub_keys.push_back(szKeyName);

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





//LSTATUS MOONG::Registry::remove(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value)
//{
//#if _MSC_VER > 1200
//	CRegKey reg_key;
//
//	LSTATUS return_status = reg_key.Open(key, sub_key.c_str(), KEY_SET_VALUE);
//	if (return_status != ERROR_SUCCESS)
//	{
//		return return_status;
//	}
//
//	return_status = reg_key.DeleteValue(value.c_str());
//	if (return_status != ERROR_SUCCESS)
//	{
//		reg_key.Close();
//		return return_status;
//	}
//
//	return reg_key.Close();
//#else
//	HKEY key_result = NULL;
//
//	LSTATUS status = RegOpenKeyEx(key, sub_key.c_str(), 0, KEY_SET_VALUE, &key_result);
//	if (status != ERROR_SUCCESS)
//	{
//		return status;
//	}
//
//	status = RegDeleteValue(key_result, value.c_str());
//
//	RegCloseKey(key_result);
//
//	return status;
//#endif
//}
//
//LSTATUS MOONG::Registry::remove(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key)
//{
//#if _MSC_VER > 1200
//	CRegKey reg_key;
//
//	LSTATUS return_status = reg_key.Open(key, sub_key.c_str(), KEY_ALL_ACCESS);
//	if (return_status != ERROR_SUCCESS)
//	{
//		return return_status;
//	}
//
//	return_status = reg_key.RecurseDeleteKey(sub_key.c_str());
//	if (return_status != ERROR_SUCCESS)
//	{
//		reg_key.Close();
//		return return_status;
//	}
//
//	return reg_key.Close();
//#else
//	LSTATUS status = RegDeleteKeyA(key, sub_key.c_str());
//	return status;
//#endif
//}