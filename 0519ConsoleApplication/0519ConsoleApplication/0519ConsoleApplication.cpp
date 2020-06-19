//#include "stdafx.h"
//#include <stdlib.h>
//#include <string.h>
//
//int main()
//{
	/*char c = 'A';
	char *cp = NULL;

	cp = &c;
	printf("%x %c %c\n", &c, c, *&c);
	printf("%x %x %x\n", &cp, cp, *&cp);

	printf("%c :   %c \n", c, *cp);*/

	/*int a = 0, b = 0, c = 0;
	int *ip = NULL;

	ip = &a;
	*ip = 10;

	printf("%d %d %d %d \n", a, b, c, *ip);

	ip = &b;
	*ip = 20;

	printf("%d %d %d %d \n", a, b, c, *ip);

	ip = &c;
	*ip = 30;

	printf("%d %d %d %d \n", a, b, c, *ip);*/

	/*int num = 10;
	int *ip = NULL;
	ip = &num;

	printf("%x %x %d\n", &*&ip, *&ip, **&ip);
	printf("%x %x %d\n", &ip, ip, *ip);

	int num2 = 0;
	num2 = *ip + num;
	printf("%d\n", num2);*/

	/*int arr[3] = { 10,20,30 };
	
	//printf("%x %x %x\n", arr, arr + 1, &arr[2]);
	//printf("%d %d %d", sizeof(arr), sizeof(arr + 0), sizeof(arr[0]));
	printf("%d %d %d \n", *arr, *(arr + 1), *&arr[2]);

	int *p = NULL;
	p = arr;

	printf("%x %x %x \n", p, p + 0, &p[0]);

	for (int i = 0; i < 3; i++)
	{
		printf("%d %d %d\n", *(arr + i), *&arr[i], arr[i]);
		printf("%d %d %d\n", *(p + i), *&p[i], p[i]);
	}

	printf("배열 크기 : %d 포인터 크기 : %d\n", sizeof(arr), sizeof(p));	//포인터 - 자료형에 대한 크기를 가리킴

	p = arr + 1; // = &arr[1]*/

	/*char szBuffer[16] = { "Hello" };
	char *pszData = szBuffer;
	int nLength = 0;

	while (*pszData != '\0')
	{
		pszData++;
		nLength++;
	}

	printf("Length : %d\n", nLength);
	printf("Length : %d\n", strlen(szBuffer));
	printf("Length : %d\n", strlen("Wolrd"));*/

	/*int *pList = NULL, i = 0;

	pList = (int*)malloc(sizeof(int) * 3);

	pList[0] = 10; 
	pList[1] = 20;
	pList[2] = 30;

	memset(pList, 0, sizeof(int) * 3);

	for (i = 0; i < 3; i++)
	{
		printf("%d\n", pList[i]);
	}
	free(pList);*/

	/*int nInput = 0, sum = 0, cnt = 0;
	int *pList = NULL;

	printf("몇 개 입력 받으시겠습니까? : ");
	scanf("%d", &nInput);

	pList = (int*)malloc(sizeof(int)*nInput);

	for (int i = 0; i < nInput; i++)
	{
		scanf("%d", &pList[i]);
		sum += pList[i];

		printf("입력 no.%d > %d\n", cnt + 1, pList[i]);
		cnt++;
	}

	printf("입력받은 수는");

	for (int j = 0; j < nInput; j++)
	{
		printf(" %d ", pList[j]);
	}
	printf("이고 합은 %d입니다.\n", sum);*/

//char szBuffer[12] = { "HelloWorld" };
//char szNewBuffer[12] = { 0 };
//
//memcpy(szNewBuffer, szBuffer, 4);
//puts(szNewBuffer);
//
//memcpy(szNewBuffer, szBuffer, 6);
//puts(szNewBuffer);
//
//memcpy(szNewBuffer, szBuffer, sizeof(szBuffer));
//puts(szNewBuffer);

//char szBuffer[12] = { "HelloWorld" };
//char *pszData = NULL;
//
//pszData = (char*)malloc(sizeof(char) * 12);
//memcpy(pszData, szBuffer, sizeof(szBuffer));
//puts(pszData);
//
//free(pszData);

//int nInput = 0, sum = 0, cnt = 0;
//int i = 0;
//int *pList = NULL; 
//int *arr = NULL;
//
//pList = (int*)malloc(sizeof(int)*2);
//arr = (int*)malloc(sizeof(int)*2);
//
//while (nInput != -1)
//{
//	scanf("%d", &nInput);
//
//	if (nInput == -1)
//	{
//		break;
//	}
//	sum += nInput;
//
//	if (cnt % 2 == 1)
//	{
//		arr[cnt] = nInput;
//		memcpy(pList, arr, _msize(arr));
//		if (arr != NULL)
//			free(arr);
//
//		arr = (int*)malloc(sizeof(int)*(cnt + 3));
//	}
//	else
//	{
//		pList[cnt] = nInput;
//		memcpy(arr, pList, _msize(pList));
//		if(pList != NULL)
//			free(pList);
//
//		pList = (int*)malloc(sizeof(int)*(cnt + 3));
//	}
//	cnt++;
//}
//
//printf("입력받은 수는");
//
//for (i = 0; i < cnt; i++)
//{
//	if(cnt % 2 == 1)
//		printf(" %d ", arr[i]);
//	else
//		printf(" %d ", pList[i]);
//}
//printf("이고 합은 %d입니다.\n", sum);
//
//free(pList);
//free(arr);
//
//    return 0;
//}

