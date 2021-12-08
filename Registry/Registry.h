#pragma once

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <Windows.h>

#include <iostream>

namespace MOONG
{
	namespace REGISTRY
	{
		namespace RETURN_CODE
		{
			enum RETURN_CODE
			{
				KEY_NOT_FOUND = 1,
				ERROR_REG_OPEN_KEY_EX = 2,
				ERROR_REG_QUERY_VALUE_EX = 3,
				ERROR_REALLOC = 4
			};
		}

		class Registry
		{
		public:
			int Read(HKEY hKeyRoot, std::string subKey, std::string value, std::string& output);
			//TODO: int Write();
			//TODO: int Delete();

		private:
			const unsigned int TOTALBYTES = 8192;
			const unsigned int BYTEINCREMENT = 4096;
		};
	}
}

#endif REGISTRY_H_