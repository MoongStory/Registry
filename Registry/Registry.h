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
		static LSTATUS Write(const HKEY key, const std::string sub_key, const std::string value, const std::string data);
		static LSTATUS Write(const HKEY key, const std::string sub_key, const std::string value, const DWORD data);

		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value, char* const output, const unsigned int output_length) noexcept(false);
		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value, wchar_t* const output, const unsigned int output_length) noexcept(false);
		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value, std::string& output) noexcept(false);
		static LSTATUS Read(const HKEY key, const std::string sub_key, const std::string value, DWORD* output);

		static LSTATUS Delete(const HKEY key, const std::string sub_key, const std::string value);
		static LSTATUS Delete(const HKEY key, const std::string sub_key);

		static const int getRegSubKeys(const HKEY hKey, const std::string subKey, std::vector<std::string>& subKeys);





		//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value, LPCTSTR value);				// ���������� ���ܳ���.
		//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value, DWORD value);					// ���������� ���ܳ���.

		//// ULONG* chars ����.
		////		4��° �Ķ������ value�� ����Ű�� ������ ũ�� (tchars)�Դϴ�. �޼��尡 ��ȯ �� �� chars�� null ���� ���ڸ� �����Ͽ� �˻� �� ���ڿ��� ũ��(tchars)�� �����մϴ�.
		//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value, LPTSTR value, ULONG* chars);	// ���������� ���ܳ���.
		//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value, DWORD& value);					// ���������� ���ܳ���.
	protected:
	private:
	};
}

#endif _REGISTRY_H_