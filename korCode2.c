#include<stdio.h>
#include<locale.h>
#include<wchar.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


int main(void)
{
	wchar_t syllable, initial_C, initial, medial_V, medial, final_C, final;

	setlocale(LC_ALL, "");
	while (1)
	{
		wprintf(L"�ϳ��� �ѱ� ����(�� : ��)�� �Է��ϼ���(���� : 0) : ");
		wscanf(L"%c", &syllable);
		if (syllable == '0')
			break;
		wprintf(L"�����ڵ� : 0x%04X\n", syllable);
		initial_C = ((syllable - 0xAC00) / 28) / 21 + 0x1100;
		medial_V = ((syllable - 0xAC00) / 28) % 21 + 0x1161;
		final_C = (syllable - 0xAC00) % 28 + 0x11A7;
		initial = ((syllable - 0xAC00) / 28) / 21 + 2;
		medial = ((syllable - 0xAC00) / 28) % 21 + 3;
		final = (syllable - 0xAC00) % 28 + 1;
		if (medial >= 8 && medial <= 13)
			medial += 2;
		else if (medial >= 14 && medial <= 19)
			medial += 4;
		else if (medial >= 20 && medial <= 23)
			medial += 6;
		else if (medial >= 8 && medial <= 13)
			medial += 2;

		if (final >= 18)
			final += 1;

		wprintf(L"�ʼ� : %c (0x%04X) ������ �ڵ� : %d \n"
			, initial_C, initial_C, initial);
		wprintf(L"�߼� : %c (0x%04X) ������ �ڵ� : %d \n"
			, medial_V, medial_V, medial);
		if (final_C == 0x11A7)
			wprintf(L"���� ���� \n");
		else
			wprintf(L"���� : %c (0x%04X) ������ �ڵ� : %d \n"
				, final_C, final_C, final);
		getchar();
	}
	wprintf(L"���� \n");
	return 0;
}
