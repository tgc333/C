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
}WORD;					//단어  의미 유의어, 반의어, 예문, 중요도 멤버를 가진 구조체

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
}						//fflush 의 기능을 하는 함수

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
}						//trim 함수


int inputWord(WORD Dict[], int n)
{
	printf("\n단어 입력 >> ");
	scanf("%s", Dict[n].word);
	printf("의미 입력 >> ");
	scanf("%s", Dict[n].mean);
	printf("유의어 입력 >> ");
	scanf("%s", Dict[n].similar);
	printf("반의어 입력 >> ");
	scanf("%s", Dict[n].verse);
	flushStdin();					//입력버퍼를 지우기 위해서
	printf("예문 입력 >> ");
	fgets(Dict[n].example, 50, stdin);
	int len = strlen(Dict[n].example);
	if (Dict[n].example[len - 1] == '\n')
		Dict[n].example[len - 1] = '\0';    //fgets 쓰면 마지막문자를 널문자로 바꿔줌
	trim(Dict[n].example);				//trim 함수로 불필요한 공백 제거
	printf("중요도 입력 >> ");
	scanf("%s", Dict[n].import);
	n++;
	return n;
}						//단어의 정보를 입력받는 함수

void outputWord(WORD Dict[], int n)
{
	int i;
	for (i = 0; i < n; i++) {
		printf("\n==========================\n");
		printf("%d번 단어의 정보\n\n", i + 1);
		printf("단어 >> %s\n", Dict[i].word);
		printf("의미 >> %s\n", Dict[i].mean);
		printf("유의어 >> %s\n", Dict[i].similar);
		printf("반의어 >> %s\n", Dict[i].verse);
		printf("예문 >> %s\n", Dict[i].example);
		printf("중요도 >> %s\n", Dict[i].import);
		printf("==========================\n\n");
	}
	printf("탈출하려면 아무키나 누르세요.\n");
	getch();
}				//입력받은 모든 단어의 정보를 출력하는 함수

void SearchWord(WORD Dict[], int n)
{
	int i, j, count = 0;  //반복문을 위한 인덱스 i,j   일치하는갯수 count
	char searchWord1[20];    //입력받을 문장
	char lower1[20];		//입력받을 문장을 소문자로 변환
	char lower2[40];		//구조체에 들어있는 문장을 소문자로 변환
	printf("검색단어 입력 >> ");
	scanf("%s", searchWord1);
	strcpy(lower1, searchWord1);	//입력받은 단어를 lower1에 복사
	for (i = 0; i < strlen(lower1); i++)	//lower1의 알파벳을 소문자로 변환
		if ((lower1[i] <= 'Z') && (lower1[i] >= 'A'))
			lower1[i] += 32;

	printf("\n=========검색결과=========\n\n");
	for (i = 0; i < n; i++) {
		strcpy(lower2, Dict[i].word);	//구조체 멤버를 lower2에 복사
		for (j = 0; j < strlen(lower2); j++)	//lower2의 알파벳을 소문자로 변환
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {	//lower1 과 lower2 가 같다면
			printf("%d번째 단어 >> %s\n", i + 1, Dict[i].word);
			count++;
		}
		strcpy(lower2, Dict[i].mean);
		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {
			printf("%d번째 단어의 의미 >> %s\n", i + 1, Dict[i].mean);
			count++;
		}
		strcpy(lower2, Dict[i].similar);

		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {
			printf("%d번째 단어의 유의어 >> %s\n", i + 1, Dict[i].similar);
			count++;
		}
		strcpy(lower2, Dict[i].verse);
		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower1, lower2)) {
			printf("%d번째 단어의 반의어 >> %s\n", i + 1, Dict[i].verse);
			count++;
		}
		strcpy(lower2, Dict[i].example);
		for (j = 0; j < strlen(lower2); j++)
			if ((lower2[j] <= 'Z') && (lower2[j] >= 'A'))
				lower2[j] += 32;
		if (strstr(lower2, lower1) != NULL) {
			printf("%d번째 단어의 예문 >> %s\n", i + 1, Dict[i].example);
			count++;
		}
		if (count == 0)		//일치하는 문장이 없으면
			printf("일치하는 결과 없음\n");
		printf("\n");
	}
	printf("탈출하려면 아무키나 누르세요.\n");
	getch();
}

int DeleteWord(WORD Dict[], int n)
{
	int choice, wordCount;
	printf("---Delete Word---\n");
	printf("1 : 검색 후 삭제\n");
	printf("2 : 출력 후 삭제\n");
	printf("입력 >> ");
	scanf("%d", &choice);

	if (choice == 1) {
		SearchWord(Dict, n);
		printf("\n삭제할 단어번호 >> ");
		scanf("%d", &wordCount);
		for (int i = wordCount; i < n; i++) {
			Dict[wordCount - 1] = Dict[wordCount];
		}
	}
	else if (choice == 2)
	{
		outputWord(Dict, n);
		printf("\n삭제할 단어번호 >> ");
		scanf("%d", &wordCount);
		for (int i = wordCount; i < n; i++) {
			Dict[wordCount - 1] = Dict[wordCount];
		}
	}
	printf("삭제완료\n");
	printf("탈출하려면 아무키나 누르세요.\n");
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
}					//메뉴를 출력하는 함수

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