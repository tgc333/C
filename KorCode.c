#include <stdio.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main(void)
{
	unsigned int i;
	char input[30];
	system("chcp 949");
	printf("변환할 텍스트파일이름 입력 >> ");
	scanf("%s", input);
	FILE* fp = fopen(input, "r");
	FILE* fp2 = fopen("output.txt", "w");
	while ((i = fgetc(fp)) != EOF)
	{
		fprintf(fp2, "%X", i);
	}

	printf("output.txt 에 변환 완료\n");

	fclose(fp);
	fclose(fp2);

	return 0;
}
