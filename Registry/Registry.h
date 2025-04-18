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

#include "../../StringTool/StringTool/StringTool.h"

#if _MSC_VER <= 1200
typedef LONG LSTATUS;
#endif

namespace MOONG
{
	// TODO: 특정 레지스트리 키 하위의 자식 값들을 가져오는 함수 추가.
	// TODO: 특정 레지스트리 키 하위의 특정 이름의 값들을 가져오는 함수 추가. Read 함수로??? 재귀 함수로
	// TODO: 특정 레지스트리 키 하위의 모든 값들을 가져오는 함수 추가.
	class Registry
	{
	public:
	protected:
	private:
		static const unsigned int TOTAL_BYTES;
		static const unsigned int BYTE_INCREMENT;

	public:
		static LSTATUS write(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, const MOONG::STRING_TOOL::tstring data);
		static LSTATUS write(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, const DWORD data);

		static LSTATUS read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, TCHAR* const output, const DWORD output_length);
		static LSTATUS read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, MOONG::STRING_TOOL::tstring& output);
		static LSTATUS read(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value, DWORD* output);

		static LSTATUS delete_value(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key, const MOONG::STRING_TOOL::tstring value);
		static LSTATUS delete_key(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key);

		// 하위 키가 남아있는 경우 삭제하지 않고, 하위 키가 없을 때만 삭제. (값의 존재 여부는 판별하지 않음)
		static LSTATUS delete_key_safely(const HKEY key, const MOONG::STRING_TOOL::tstring sub_key);

		// 파라미터로 넘겨준 키 경로의 자식 키들의 이름 목록을 가져옴.
		static const int get_child_keys(const HKEY hKey, const MOONG::STRING_TOOL::tstring sub_key, std::vector<MOONG::STRING_TOOL::tstring>& output_sub_keys);
	protected:
	private:
	};
}

#endif _REGISTRY_H_