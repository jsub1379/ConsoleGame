#pragma once

#include <Windows.h>
#include <iostream>
#include<fcntl.h>
#include <io.h>

#include "Math/Vector2.h"
#include "Math/Color.h"

// ������Ʈ���� �پ��ϰ� ����� ��ƿ��Ƽ �Լ� ����.
namespace Utils
{
	// �� ���� ���� �ٲ� �� ����ϴ� �Լ�.
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	// �ܼ� ��� �ڵ� �������� �Լ�.
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	// �ܼ� Ŀ�� ��ġ �̵� �Լ�.
	inline void SetConsolePosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, coord);
	}

	inline void SetConsolePosition(const Vector2& position)
	{
		SetConsolePosition(static_cast<COORD>(position));
	}


	// �ܼ� �ؽ�Ʈ ���� ���� �Լ�.
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, color);
	}

	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}


	inline void PrintWideCharacter(const wchar_t* character)
	{
		_write(_fileno(stdout), character, (unsigned int)wcslen(character) * sizeof(wchar_t));
	}


	//�����ڵ�� �����ϴ� �Լ�
	inline const wchar_t* ConvertToWideChar(char ch)
	{
		switch (ch)
		{
		case 'P': return L"��";  // �÷��̾�
		case '#': return L"��";  // ��
		case '.': return L"��";  // �ٴ�
		case 'E': return L"��";  // ��
		case 'Z': return L"��";  // ��ǥ ����
		default:  return (const wchar_t*)ch; // �� �ܴ� ���� ���� ����
		}
	}

}