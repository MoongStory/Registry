// https://github.com/MoongStory/Registry

#if _MSC_VER > 1000
	#pragma once
#endif

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

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
			Registry();

			int Read(HKEY hKeyRoot, std::string subKey, std::string value, std::string& output);
			//TODO: int Write();
			//TODO: int Delete();

		private:
			const unsigned int TOTALBYTES;
			const unsigned int BYTEINCREMENT;
		};
	}
}

#endif _REGISTRY_H_