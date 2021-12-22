// https://github.com/MoongStory/Registry


// 1. TODO: �����ε����� Wirte �ڷ��� ���� �߰�.

// 2. TODO: Convert???, Convert???A, Convert???W�ؼ�... Convert???(std::string str); �̷������� ���� �� �ֳ�???
//		CONVERT Ŭ���� �ۼ�???

// 3. FIXME: CRegKey RegKey; Ŭ������ �ִµ�... ���� �� ���� �Ǵ°� �ƴѰ�...

// 4. THINK: ���� �Ķ���� string Ŭ������ ���ϰ� char, wchar �����ε� �Լ��� �����?
//		�̰ɷ� �ϸ� 2���� ���ص� ��...
//		CStringA�� ����ϸ�???

// 5. THINK: CRegKey ����Լ��� �̸� �Ȱ��� ����°� ���...

// 6. CRegKey�� ��������� ���ܳ���

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



			//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPCTSTR value);				// ���������� ���ܳ���.
			//int Write(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD value);					// ���������� ���ܳ���.

			//// ULONG* chars ����.
			////		4��° �Ķ������ value�� ����Ű�� ������ ũ�� (tchars)�Դϴ�. �޼��尡 ��ȯ �� �� chars�� null ���� ���ڸ� �����Ͽ� �˻� �� ���ڿ��� ũ��(tchars)�� �����մϴ�.
			//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, LPTSTR value, ULONG* chars);	// ���������� ���ܳ���.
			//int Read(HKEY key_root, LPCTSTR key_name, LPCTSTR value_name, DWORD& value);					// ���������� ���ܳ���.

			//int Delete(HKEY hKeyRoot, std::string subKey);

		private:
			const unsigned int TOTALBYTES;
			const unsigned int BYTEINCREMENT;
		};
	}
}

#endif _REGISTRY_H_