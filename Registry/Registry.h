// https://github.com/MoongStory/Registry

#if _MSC_VER > 1000
	#pragma once
#endif

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#include <iostream>
#include <atlbase.h>

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

			LSTATUS Write(const HKEY key, const std::string sub_key, const std::string value_name, const std::string data) const;
			LSTATUS Write(const HKEY key, const std::string sub_key, const std::string value_name, const DWORD data) const;

			LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, char* const output, const unsigned int output_length) const;
			LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, wchar_t* const output, const unsigned int output_length) const;
			LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, std::string& output) const;
			LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, DWORD* output) const;

			LSTATUS Delete(const HKEY key, const std::string sub_key, const std::string value_name) const;
			LSTATUS Delete(const HKEY key, const std::string sub_key) const;



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