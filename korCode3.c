#include<stdio.h>
#include<Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


int main(void)
{
	union {
		WORD word;
		BYTE byte[2];
	} syllable;
	BYTE last;
	WORD mid, first;

	system("chcp 1361");    // 조합형 한글코드

	syllable.word = 0;

	last = 1;
	syllable.word |= last;

	mid = 29;
	syllable.word |= (mid << 5);

	first = 13;
	syllable.word |= (first << 10);

	syllable.word |= (1 << 15);

	printf("%02x%02x(%c%c)  ", syllable.byte[1], syllable.byte[0],
		syllable.byte[1], syllable.byte[0]);     // '이'  출력



	syllable.word = 0;

	last = 1;
	syllable.word |= last;

	mid = 10;
	syllable.word |= (mid << 5);

	first = 14;
	syllable.word |= (first << 10);

	syllable.word |= (1 << 15);

	printf("%02x%02x(%c%c)  ", syllable.byte[1], syllable.byte[0],
		syllable.byte[1], syllable.byte[0]);   // '제'  출력



	syllable.word = 0;

	last = 5;
	syllable.word |= last;

	mid = 11;
	syllable.word |= (mid << 5);

	first = 20;
	syllable.word |= (first << 10);

	syllable.word |= (1 << 15);

	printf("%02x%02x(%c%c)\n", syllable.byte[1], syllable.byte[0],
		syllable.byte[1], syllable.byte[0]);  // '현' 출력

	return 0;
}