// https://github.com/MoongStory/Registry


// 1. TODO: 오버로딩으로 Wirte 자료형 별로 추가.

// 2. TODO: Convert???, Convert???A, Convert???W해서... Convert???(std::string str); 이런식으로 만들 수 있나???
//		CONVERT 클래스 작성???

// 3. FIXME: CRegKey RegKey; 클래스가 있는데... 굳이 안 만들어도 되는거 아닌가...

// 4. THINK: 굳이 파라미터 string 클래스로 안하고 char, wchar 오버로딩 함수로 만들면?
//		이걸로 하면 2번은 안해도 됨...
//		CStringA를 사용하면???

// 5. THINK: CRegKey 멤버함수랑 이름 똑같이 만들는거 고려...

// 6. CRegKey는 참고용으로 남겨놓자

#if _MSC_VER > 1000
	#pragma once
#endif

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#include <iostream>
#include <atlstr.h>

namespace MOONG
{
	namespace REGISTRY
	{
		namespace RETURN_CODE
		{
			enum RETURN_CODE
			{
				ERROR_REALLOC = 1
			};
		}

		class Registry
		{
		public:
			Registry();

			LSTATUS Write(const HKEY key, CStringA sub_key, CStringA value_name, CStringA data);

			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, char* const output, const UINT output_length);
			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, wchar_t* const output, const UINT output_length);
			//LSTATUS Read(HKEY key, CStringA sub_key, CStringA value_name, std::string& output);
			//LSTATUS Read(HKEY key, CStringA sub_key, CStringA value_name, CStringA& output);
			//LSTATUS Read(HKEY key, CStringA sub_key, CStringA value_name, CStringW& output);



			//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPCTSTR value);				// 예제용으로 남겨놓기.
			//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD value);					// 예제용으로 남겨놓기.

			//// ULONG* chars 설명.
			////		4번째 파라미터인 value가 가리키는 버퍼의 크기 (tchars)입니다. 메서드가 반환 될 때 chars는 null 종결 문자를 포함하여 검색 된 문자열의 크기(tchars)를 포함합니다.
			//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPTSTR value, ULONG* chars);	// 예제용으로 남겨놓기.
			//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD& value);					// 예제용으로 남겨놓기.

			//int Delete(HKEY hKeyRoot, std::string subKey);

		private:
			const unsigned int TOTALBYTES;
			const unsigned int BYTEINCREMENT;
		};
	}
}

#endif _REGISTRY_H_