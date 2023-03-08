/*******************************************************************************
MIT License

Copyright (c) 2023 Moong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

// https://github.com/MoongStory/Registry

#if _MSC_VER > 1000
	#pragma once
#endif

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#include <iostream>
#include <atlbase.h>
#include <vector>

#if _MSC_VER <= 1200
typedef LONG LSTATUS;
#endif

namespace MOONG
{
	namespace REGISTRY
	{
		namespace RETURN
		{
			static const int SUCCESS = 0;

			namespace FAILURE
			{
				static const int REALLOC = 1;
			}
		}
	}

	class Registry
	{
	public:
	protected:
	private:
		static const unsigned int TOTALBYTES;
		static const unsigned int BYTEINCREMENT;

	public:
		static LSTATUS write(const HKEY key, const std::string sub_key, const std::string value, const std::string data);
		static LSTATUS write(const HKEY key, const std::string sub_key, const std::string value, const DWORD data);

		static LSTATUS read(const HKEY key, const std::string sub_key, const std::string value, char* const output, const unsigned int output_length);
		static LSTATUS read(const HKEY key, const std::string sub_key, const std::string value, wchar_t* const output, const unsigned int output_length);
		static LSTATUS read(const HKEY key, const std::string sub_key, const std::string value, std::string& output);
		static LSTATUS read(const HKEY key, const std::string sub_key, const std::string value, DWORD* output);

		static LSTATUS remove(const HKEY key, const std::string sub_key, const std::string value);
		static LSTATUS remove(const HKEY key, const std::string sub_key);

		static const int get_reg_sub_keys(const HKEY hKey, const std::string subKey, std::vector<std::string>& subKeys);





		//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value, LPCTSTR value);				// 예제용으로 남겨놓기.
		//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value, DWORD value);					// 예제용으로 남겨놓기.

		//// ULONG* chars 설명.
		////		4번째 파라미터인 value가 가리키는 버퍼의 크기 (tchars)입니다. 메서드가 반환 될 때 chars는 null 종결 문자를 포함하여 검색 된 문자열의 크기(tchars)를 포함합니다.
		//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value, LPTSTR value, ULONG* chars);	// 예제용으로 남겨놓기.
		//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value, DWORD& value);					// 예제용으로 남겨놓기.
	protected:
	private:
	};
}

#endif _REGISTRY_H_