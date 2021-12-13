// https://github.com/MoongStory/Registry


// 1. TODO: 오버로딩으로 Wirte 자료형 별로 추가.

// 2. TODO: Convert???, Convert???A, Convert???W해서... Convert???(std::string str); 이런식으로 만들 수 있나???
//		CONVERT 클래스 작성???

// 3. FIXME: CRegKey RegKey; 클래스가 있는데... 굳이 안 만들어도 되는거 아닌가...

// 4. THINK: 굳이 파라미터 string 클래스로 안하고 char, wchar 오버로딩 함수로 만들면?
//		이걸로 하면 2번은 안해도 됨...

// 5. THINK: CRegKey 멤버함수랑 이름 똑같이 만들는거 고려...

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
				ERROR_REALLOC = 4,
				ERROR_REG_OPEN = 5,
				ERROR_READ = 6,
				ERROR_CLOSE = 7,
				ERROR_CREATE = 8,
				ERROR_SET_VALUE = 9
			};
		}

		class Registry
		{
		public:
			Registry();

			int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPCTSTR value);
			int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD value);

			// ULONG* chars
			//		value가 가리키는 버퍼의 크기 (tchars)입니다. 메서드가 반환 될 때 chars는 null 종결 문자를 포함하여 검색 된 문자열의 크기(tchars)를 포함합니다.
			int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPTSTR value, ULONG* chars);
			int Read(HKEY key, std::string sub_key, std::string value_name, std::string& output);
			int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD& value);

			int Delete(HKEY hKeyRoot, std::string subKey);

		private:
			const unsigned int TOTALBYTES;
			const unsigned int BYTEINCREMENT;
		};
	}
}

#endif _REGISTRY_H_