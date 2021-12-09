#include "Registry.h"

MOONG::REGISTRY::Registry::Registry() :
TOTALBYTES(8192),
BYTEINCREMENT(4096)
{

}

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
	char* buffer = (char *)malloc(buffer_size);
	char* buffer_temp = nullptr;
	DWORD cb_data = buffer_size;
	
	lResult = RegQueryValueExA(hkey_result, value.c_str(), NULL, NULL, (LPBYTE)buffer, &cb_data);
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
			value.c_str(),
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