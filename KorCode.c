#include <stdio.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int main(void)
{
	unsigned int i;
	char input[30];
	system("chcp 949");
	printf("��ȯ�� �ؽ�Ʈ�����̸� �Է� >> ");
	scanf("%s", input);
	FILE* fp = fopen(input, "r");
	FILE* fp2 = fopen("output.txt", "w");
	while ((i = fgetc(fp)) != EOF)
	{
		fprintf(fp2, "%X", i);
	}

	printf("output.txt �� ��ȯ �Ϸ�\n");

	fclose(fp);
	fclose(fp2);

	return 0;
}
