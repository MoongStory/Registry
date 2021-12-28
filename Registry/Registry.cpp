#include "Registry.h"

#include <strsafe.h>

MOONG::REGISTRY::Registry::Registry() :
TOTALBYTES(8192),
BYTEINCREMENT(4096)
{

}



LSTATUS MOONG::REGISTRY::Registry::Write(const HKEY key, const CStringA sub_key, const CStringA value_name, const CStringA data) const
{
	HKEY key_result = NULL;
	DWORD disposition = 0;

	LSTATUS status = RegCreateKeyExA(key, sub_key.GetString(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key_result, &disposition);
	if (status == ERROR_SUCCESS)
	{
		status = RegSetValueExA(key_result, value_name.GetString(), 0, REG_SZ, (const BYTE*)(data.GetString()), data.GetLength());
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

LSTATUS MOONG::REGISTRY::Registry::Write(const HKEY key, const CStringA sub_key, const CStringA value_name, const DWORD data) const
{
	HKEY key_result = NULL;
	DWORD disposition = 0;

	LSTATUS status = RegCreateKeyExA(key, sub_key.GetString(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key_result, &disposition);
	if (status == ERROR_SUCCESS)
	{
		status = RegSetValueExA(key_result, value_name.GetString(), 0, REG_DWORD, (const BYTE*)(&data), sizeof(data));
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

LSTATUS MOONG::REGISTRY::Registry::Read(const HKEY key, const CStringA sub_key, const CStringA value_name, char* const output, const unsigned int output_length) const
{
	HKEY key_result = nullptr;

	LSTATUS status = RegOpenKeyExA(key, sub_key.GetString(), 0, KEY_READ, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	DWORD buffer_size = this->TOTALBYTES;
	char* buffer = (char*)malloc(buffer_size);
	char* buffer_temp = nullptr;
	DWORD cb_data = buffer_size;

	status = RegQueryValueExA(key_result, value_name.GetString(), NULL, NULL, (LPBYTE)buffer, &cb_data);
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
			value_name.GetString(),
			NULL,
			NULL,
			(LPBYTE)buffer,
			&cb_data);
	}

	if (status == ERROR_SUCCESS)
	{
		if (buffer != nullptr)
		{
			StringCchCopyA(output, output_length, buffer);
		}
	}

	if (buffer != nullptr)
	{
		free(buffer);
	}

	RegCloseKey(key_result);

	return status;
}

LSTATUS MOONG::REGISTRY::Registry::Read(const HKEY key, const CStringA sub_key, const CStringA value_name, wchar_t* const output, const unsigned int output_length) const
{
	char* buffer = new char[output_length];

	LSTATUS status = this->Read(key, sub_key, value_name, buffer, output_length);
	if (status != ERROR_SUCCESS)
	{
		delete[] buffer;

		return status;
	}

	CStringW convert_string = buffer;

	delete[] buffer;

	StringCchCopyW(output, output_length, convert_string.GetBuffer());

	return status;
}

LSTATUS MOONG::REGISTRY::Registry::Read(const HKEY key, const CStringA sub_key, const CStringA value_name, std::string& output) const
{
	HKEY key_result = nullptr;

	LSTATUS status = RegOpenKeyExA(key, sub_key.GetString(), 0, KEY_READ, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	DWORD buffer_size = this->TOTALBYTES;
	char* buffer = (char*)malloc(buffer_size);
	char* buffer_temp = nullptr;
	DWORD cb_data = buffer_size;

	status = RegQueryValueExA(key_result, value_name.GetString(), NULL, NULL, (LPBYTE)buffer, &cb_data);
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

		status = RegQueryValueExA(key_result, value_name.GetString(), NULL, NULL, (LPBYTE)buffer, &cb_data);
	}

	if (status == ERROR_SUCCESS)
	{
		if (buffer != nullptr)
		{
			output = buffer;
		}
	}

	if (buffer != nullptr)
	{
		free(buffer);
	}

	RegCloseKey(key_result);

	return status;
}

LSTATUS MOONG::REGISTRY::Registry::Read(const HKEY key, const CStringA sub_key, const CStringA value_name, CStringA& output) const
{
	std::string buffer;
	LSTATUS status = this->Read(key, sub_key, value_name, buffer);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	output = buffer.c_str();

	return status;
}

LSTATUS MOONG::REGISTRY::Registry::Read(const HKEY key, const CStringA sub_key, const CStringA value_name, CStringW& output) const
{
	std::string buffer;
	LSTATUS status = this->Read(key, sub_key, value_name, buffer);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	output = buffer.c_str();

	return status;
}

LSTATUS MOONG::REGISTRY::Registry::Read(const HKEY key, const CStringA sub_key, const CStringA value_name, DWORD* output) const
{
	HKEY key_result = nullptr;

	LSTATUS status = RegOpenKeyExA(key, sub_key.GetString(), 0, KEY_READ, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	DWORD buffer = 0;
	DWORD cb_data = sizeof(DWORD);

	status = RegQueryValueExA(key_result, value_name.GetString(), NULL, NULL, (LPBYTE)(&buffer), &cb_data);
	if (status != ERROR_SUCCESS)
	{
		RegCloseKey(key_result);

		return status;
	}

	*output = buffer;

	RegCloseKey(key_result);

	return status;
}

LSTATUS MOONG::REGISTRY::Registry::Delete(const HKEY key, const CStringA sub_key) const
{
	LSTATUS status = RegDeleteKeyExA(key, sub_key.GetString(), KEY_ALL_ACCESS, 0);

	return status;
}

LSTATUS MOONG::REGISTRY::Registry::Delete(const HKEY key, const CStringA sub_key, const CStringA value_name) const
{
	HKEY key_result = nullptr;

	LSTATUS status = RegOpenKeyExA(key, sub_key.GetString(), 0, KEY_ALL_ACCESS, &key_result);
	if (status != ERROR_SUCCESS)
	{
		return status;
	}

	status = RegDeleteValueA(key_result, value_name.GetString());

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