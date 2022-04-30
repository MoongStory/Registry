// https://github.com/MoongStory/Registry

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _REGISTRY_H_
#define _REGISTRY_H_

#include <iostream>
#include <atlbase.h>

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
		static LSTATUS Write(const HKEY key, const std::string sub_key, const std::string value_name, const std::string data);
		static LSTATUS Write(const HKEY key, const std::string sub_key, const std::string value_name, const DWORD data);
		
		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, char* const output, const unsigned int output_length);
		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, wchar_t* const output, const unsigned int output_length);
		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, std::string& output);
		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value_name, DWORD* output);
		
		static LSTATUS Delete(const HKEY key, const std::string sub_key, const std::string value_name);
		static LSTATUS Delete(const HKEY key, const std::string sub_key);
		
		
		
		//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPCTSTR value);				// ���������� ���ܳ���.
		//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD value);					// ���������� ���ܳ���.
		
		//// ULONG* chars ����.
		////		4��° �Ķ������ value�� ����Ű�� ������ ũ�� (tchars)�Դϴ�. �޼��尡 ��ȯ �� �� chars�� null ���� ���ڸ� �����Ͽ� �˻� �� ���ڿ��� ũ��(tchars)�� �����մϴ�.
		//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPTSTR value, ULONG* chars);	// ���������� ���ܳ���.
		//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD& value);					// ���������� ���ܳ���.
		
	private:
		static const unsigned int TOTALBYTES;
		static const unsigned int BYTEINCREMENT;
	};
}

#endif _REGISTRY_H_