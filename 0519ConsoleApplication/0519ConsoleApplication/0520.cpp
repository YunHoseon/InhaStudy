#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char szBuffer[12] = { "TestString" };
	char *pszData = "TestString";

	printf("%d\n", memcmp(szBuffer, pszData, 10));
	printf("%d\n", memcmp("testSting", pszData, 10));
	printf("%d\n", memcmp("DataString", pszData, 10));
	return 0;
}