// https://github.com/MoongStory/Registry


// 1. TODO: �����ε����� Wirte �ڷ��� ���� �߰�.

// 2. TODO: Convert???, Convert???A, Convert???W�ؼ�... Convert???(std::string str); �̷������� ���� �� �ֳ�???
//		CONVERT Ŭ���� �ۼ�???

// 3. FIXME: CRegKey RegKey; Ŭ������ �ִµ�... ���� �� ���� �Ǵ°� �ƴѰ�...

// 4. THINK: ���� �Ķ���� string Ŭ������ ���ϰ� char, wchar �����ε� �Լ��� �����?
//		�̰ɷ� �ϸ� 2���� ���ص� ��...

// 5. THINK: CRegKey ����Լ��� �̸� �Ȱ��� ����°� ���...

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
			//		value�� ����Ű�� ������ ũ�� (tchars)�Դϴ�. �޼��尡 ��ȯ �� �� chars�� null ���� ���ڸ� �����Ͽ� �˻� �� ���ڿ��� ũ��(tchars)�� �����մϴ�.
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