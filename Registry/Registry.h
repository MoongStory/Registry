// https://github.com/MoongStory/Registry

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
			LSTATUS Write(const HKEY key, CStringA sub_key, CStringA value_name, const DWORD data);

			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, char* const output, const unsigned int output_length);
			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, wchar_t* const output, const unsigned int output_length);
			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, std::string &output);
			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, CStringA &output);
			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, CStringW& output);
			LSTATUS Read(const HKEY key, CStringA sub_key, CStringA value_name, DWORD* output);

			LSTATUS Delete(const HKEY key, CStringA sub_key);
			LSTATUS Delete(const HKEY key, CStringA sub_key, CStringA value_name);



			//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPCTSTR value);				// ���������� ���ܳ���.
			//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD value);					// ���������� ���ܳ���.

			//// ULONG* chars ����.
			////		4��° �Ķ������ value�� ����Ű�� ������ ũ�� (tchars)�Դϴ�. �޼��尡 ��ȯ �� �� chars�� null ���� ���ڸ� �����Ͽ� �˻� �� ���ڿ��� ũ��(tchars)�� �����մϴ�.
			//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPTSTR value, ULONG* chars);	// ���������� ���ܳ���.
			//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD& value);					// ���������� ���ܳ���.

		private:
			const unsigned int TOTALBYTES;
			const unsigned int BYTEINCREMENT;
		};
	}
}

#endif _REGISTRY_H_