#include "Registry.h"

int MOONG::REGISTRY::Registry::Read(HKEY hKeyRoot, std::string subKey, std::string value, std::string& output)
{
	HKEY hkey_result = nullptr;

	LSTATUS lResult = RegOpenKeyExA(hKeyRoot, subKey.c_str(), 0, KEY_READ, &hkey_result);

	if (lResult != ERROR_SUCCESS)
	{
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			return MOONG::REGISTRY::RETURN_CODE::KEY_NOT_FOUND;
		}
		else
		{
			return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_OPEN_KEY_EX;
		}
	}

	DWORD buffer_size = this->TOTALBYTES;
	char* perf_data = (char *)malloc(buffer_size);
	DWORD cb_data = buffer_size;
	
	lResult = RegQueryValueExA(hkey_result, value.c_str(), NULL, NULL, (LPBYTE)perf_data, &cb_data);
	while (lResult == ERROR_MORE_DATA)
	{
		// Get a buffer that is big enough.

		buffer_size += this->BYTEINCREMENT;
		char* temp = perf_data;
		perf_data = (char *)realloc(perf_data, buffer_size);
		if (perf_data == nullptr)
		{
			free(temp);

			return MOONG::REGISTRY::RETURN_CODE::ERROR_REALLOC;
		}

		cb_data = buffer_size;

		lResult = RegQueryValueExA(hkey_result,
			value.c_str(),
			NULL,
			NULL,
			(LPBYTE)perf_data,
			&cb_data);
	}

	if (lResult == ERROR_SUCCESS)
	{
		if (perf_data != nullptr)
		{
			output = perf_data;
		}
	}
	else
	{
		return MOONG::REGISTRY::RETURN_CODE::ERROR_REG_QUERY_VALUE_EX;
	}

	RegCloseKey(hkey_result);

	return EXIT_SUCCESS;
}