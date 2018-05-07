#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

typedef struct {
	char word[20];
	char mean[20];
	char similar[20];
	char verse[20];
	char example[50];
	char import[20];
}WORD;					//�ܾ�  �ǹ� ���Ǿ�, ���Ǿ�, ����, �߿䵵 ����� ���� ����ü

void flushStdin(void)
{
	int ch;
	fseek(stdin, 0, SEEK_END);
	if (ftell(stdin)>0)
		do
			ch = getchar();
	while (ch != EOF && ch != '\n');
}

char *fgetsCleanup(char *string)
{
	if (string[strlen(string) - 1] == '\n')
		string[strlen(string) - 1] = '\0';
	else
		flushStdin();
	return string;
}						//fflush �� ����� �ϴ� �Լ�

int trim(char str[])
{
	int count = 0;
	count = ltrim(str);
	count += rtrim(str);
	count += mtrim(str);
	return count;
}

int ltrim(char str[])
{
	int i, count = 0;
	for (i = 0; i<strlen(str); i++)
		if ((str[i] == ' ') || (str[i] == '\n') || (str[i] == '\t'))
			count++;
		else
			break;
	if (count == 0)
		return 0;
	else {
		for (i = count; i <= strlen(str); i++)
			str[i - count] = str[i];
		return count;
	}
}

int rtrim(char str[])
{
	int i, count = 0;
	for (i = strlen(str) - 1; i >= 0; i--)
		if ((str[i] == ' ') || (str[i] == '\n') || (str[i] == '\t'))
			count++;
		else
			break;
	if (count == 0)
		return 0;
	else {
		str[strlen(str) - count] = '\0';
		return count;
	}
}

int mtrim(char str[])
{
	int i, j, count = 0, num;
	for (i = 0; i<strlen(str); i++)
		if ((str[i] == '\n') || (str[i] == '\t'))
			str[i] = ' ';
	i = 0;
	while (str[i] != '\0') {
		num = 0;
		if (str[i] == ' ')
			while (str[i + num] == ' ')
				num++;
		if (num>1) {
			for (j = i + num; j <= strlen(str); j++)
				str[j - num + 1] = str[j];
			count += num - 1;
		}
		i++;
	}
	return count;
}						//trim �Լ�


int inputWord(WORD Dict[], int n)
{
	printf("\n�ܾ� �Է� >> ");
	scanf("%s", Dict[n].word);
	printf("�ǹ� �Է� >> ");
	scanf("%s", Dict[n].mean);
	printf("���Ǿ� �Է� >> ");
	scanf("%s", Dict[n].similar);
	printf("���Ǿ� �Է� >> ");
	scanf("%s", Dict[n].verse);
	flushStdin();					//�Է¹��۸� ����� ���ؼ�
	printf("���� �Է� >> ");
	fgets(Dict[n].example, 50, stdin);
	int len = strlen(Dict[n].example);
	if (Dict[n].example[len - 1] == '\n')
		Dict[n].example[len - 1] = '\0';    //fgets ���� ���������ڸ� �ι��ڷ� �ٲ���
	trim(Dict[n].example);				//trim �Լ��� ���ʿ��� ���� ����
	printf("�߿䵵 �Է� >> ");
	scanf("%s", Dict[n].import);
	n++;
	return n;
}						//�ܾ��� ������ �Է¹޴� �Լ�

void outputWord(WORD Dict[], int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("\n==========================\n");
		printf("%d�� �ܾ��� ����\n\n", i + 1);
		printf("�ܾ� >> %s\n", Dict[i].word);
		printf("�ǹ� >> %s\n", Dict[i].mean);
		printf("���Ǿ� >> %s\n", Dict[i].similar);
		printf("���Ǿ� >> %s\n", Dict[i].verse);
		printf("���� >> %s\n", Dict[i].example);
		printf("�߿䵵 >> %s\n", Dict[i].import);
		printf("==========================\n\n");
	}
	printf("Ż���Ϸ��� �ƹ�Ű�� ��������.\n");
	getch();
}				//�Է¹��� ��� �ܾ��� ������ ����ϴ� �Լ�

void SearchWord(WORD Dict[], int n)
{
	int i, j, count = 0;  //�ݺ����� ���� �ε��� i,j   ��ġ�ϴ°��� count
	char searchWord1[20];    //�Է¹��� ����
	char lower1[20];		//�Է¹��� ������ �ҹ��ڷ� ��ȯ
	char lower2[40];		//����ü�� ����ִ� ������ �ҹ��ڷ� ��ȯ
	printf("�˻��ܾ� �Է� >> ");
	scanf("%s", searchWord1);
	strcpy(lower1, searchWord1);	//�Է¹��� �ܾ lower1�� ����
	for (i = 0; i < strlen(lower1); i++)	//lower1�� ���ĺ��� �ҹ��ڷ� ��ȯ
		if ((lower1[i] <= 'Z') && (lower1[i] >= 'A'))
			lower1[i] += 32;

	printf("\n=========�˻����=========\n\n");
	for (i = 0; i < n; i++) {
		strcpy(lower2, Dict[i].word);	//����ü ����� lower2�� ����
		for (j = 0; j < strlen(lower2); j++)	//lower2�� ���ĺ��� �ҹ��ڷ� ��ȯ
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {	//lower1 �� lower2 �� ���ٸ�
			printf("%d��° �ܾ� >> %s\n", i + 1, Dict[i].word);
			count++;
		}
		strcpy(lower2, Dict[i].mean);
		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {
			printf("%d��° �ܾ��� �ǹ� >> %s\n", i + 1, Dict[i].mean);
			count++;
		}
		strcpy(lower2, Dict[i].similar);

		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {
			printf("%d��° �ܾ��� ���Ǿ� >> %s\n", i + 1, Dict[i].similar);
			count++;
		}
		strcpy(lower2, Dict[i].verse);
		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {
			printf("%d��° �ܾ��� ���Ǿ� >> %s\n", i + 1, Dict[i].verse);
			count++;
		}
		strcpy(lower2, Dict[i].example);
		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower2, lower1) != NULL) {
			printf("%d��° �ܾ��� ���� >> %s\n", i + 1, Dict[i].example);
			count++;
		}
		if (count == 0)		//��ġ�ϴ� ������ ������
			printf("��ġ�ϴ� ��� ����\n");
		printf("\n");
	}
	printf("Ż���Ϸ��� �ƹ�Ű�� ��������.\n");
	getch();
}

int DeleteWord(WORD Dict[], int n)
{
	int choice, wordCount;
	printf("---Delete Word---\n");
	printf("1 : �˻� �� ����\n");
	printf("2 : ��� �� ����\n");
	printf("�Է� >> ");
	scanf("%d", &choice);

	if (choice == 1) {
		SearchWord(Dict, n);
		printf("\n������ �ܾ��ȣ >> ");
		scanf("%d", &wordCount);
		for (int i = wordCount; i < n; i++) {
			Dict[wordCount - 1] = Dict[wordCount];
		}
	}
	else if (choice == 2)
	{
		outputWord(Dict, n);
		printf("\n������ �ܾ��ȣ >> ");
		scanf("%d", &wordCount);
		for (int i = wordCount; i < n; i++) {
			Dict[wordCount - 1] = Dict[wordCount];
		}
	}
	printf("�����Ϸ�\n");
	printf("Ż���Ϸ��� �ƹ�Ű�� ��������.\n");
	getch();
	return n - 1;
}

void saveWord(WORD Dict[], int n)
{
	FILE *fp = fopen("C:/Users/Secret/Desktop/Eng.dic", "wt");
	char buf[81];
	for (int i = 0; i < n; i++) {
		fputs(Dict[i].word, fp); fputc('\n', fp);
		fputs(Dict[i].mean, fp); fputc('\n', fp);
		fputs(Dict[i].similar, fp); fputc('\n', fp);
		fputs(Dict[i].verse, fp); fputc('\n', fp);
		fputs(Dict[i].example, fp); fputc('\n', fp);
		fputs(Dict[i].import, fp); fputc('\n', fp);
	}
	fclose(fp);
}

int openWord(WORD Dict[])
{
	char buf[81];
	int i = 0;
	int c = 0;
	FILE *fp = fopen("C:/Users/Secret/Desktop/Eng.dic", "rt");
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		switch (i)
		{
		case 0: strcpy(Dict[c].word, buf); i++;
			for (int i = 0; i < sizeof(Dict[c].word); i++)
				if (Dict[c].word[i] == '\n')
					Dict[c].word[i] = '\0';
			break;
		case 1: strcpy(Dict[c].mean, buf); i++;
			for (int i = 0; i < sizeof(Dict[c].mean); i++)
				if (Dict[c].mean[i] == '\n')
					Dict[c].mean[i] = '\0';
			break;
		case 2: strcpy(Dict[c].similar, buf); i++;
			for (int i = 0; i < sizeof(Dict[c].similar); i++)
				if (Dict[c].similar[i] == '\n')
					Dict[c].similar[i] = '\0';
			break;
		case 3: strcpy(Dict[c].verse, buf); i++;
			for (int i = 0; i < sizeof(Dict[c].verse); i++)
				if (Dict[c].verse[i] == '\n')
					Dict[c].verse[i] = '\0';
			break;
		case 4: strcpy(Dict[c].example, buf); i++;
			for (int i = 0; i < sizeof(Dict[c].example); i++)
				if (Dict[c].example[i] == '\n')
					Dict[c].example[i] = '\0';
			break;
		case 5: strcpy(Dict[c].import, buf);
			for (int i = 0; i < sizeof(Dict[c].import); i++)
				if (Dict[c].import[i] == '\n')
					Dict[c].import[i] = '\0';
			i = 0; c++;
			break;
		}
	}
	return c;
}

void printMenu(void)
{
	system("cls");
	printf("******************************\n");
	printf("[Word Trainer Program] Ver 0.1\n");
	printf("           - Menu -           \n");
	printf("   1. Input Words             \n");
	printf("   2. Print Words             \n");
	printf("   3. Search Words            \n");
	printf("   4. Delete Words            \n");
	printf("   5. Open Words            \n");
	printf("   0. Quit                    \n");
	printf("   => Input your choice: ");
}					//�޴��� ����ϴ� �Լ�

int main(void)
{
	WORD Dict[50];
	int wordCount = 0, choice;
	do {
		do {
			printMenu();
			scanf("%d", &choice);
		} while (choice != 0 && choice != 1 && choice != 2 &&
			choice != 3 && choice != 4 && choice != 5);
		switch (choice) {
		case 1:
			wordCount = inputWord(Dict, wordCount);
			break;
		case 2:
			outputWord(Dict, wordCount);
			break;
		case 3:
			SearchWord(Dict, wordCount);
			break;
		case 4:
			wordCount = DeleteWord(Dict, wordCount);
			break;
		case 5:
			wordCount = openWord(Dict);
			break;
		}
	} while (choice != 0);
	saveWord(Dict, wordCount);
	return 0;
}