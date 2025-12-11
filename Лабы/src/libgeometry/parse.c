#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <libgeometry/parse.h>
#include <ctype.h>

#define CIRCLE "circle"
#define circleFlag 1

float *parseCircle(char *str, float *data, int columnNum, int circleArguments)
{
	int read = sscanf(str, "(%f %f, %f)", &data[1], &data[2], &data[3]);
	if (read != circleArguments)
	{
		printf("ERROR in column %d: there're possibly not enough arguments or brackets\n", columnNum);
		return NULL;
	}
	if (data[3] < 0)
	{
		printf("ERROR in column %d: negative radius\n", columnNum);
		return NULL;
	}

	return data;
}

float *parse(char *input, float *data, int columnNum, int circleArguments)
{
	if (strlen(input) <= 1)
	{
		printf("ERROR in column %d: empty input\n", columnNum);
		return NULL;
	}
	char *firstBracket = strchr(input, '(');
	if (firstBracket == NULL)
	{
		printf("ERROR in column %d: expected '('\n", columnNum);
		return NULL;
	}
	char *secondBracket = strrchr(input, ')');
	if (secondBracket == NULL)
	{
		printf("ERROR in column %d: expected ')'\n", columnNum);
		return NULL;
	}
	if (strlen(secondBracket) > 2)
	{
		printf("ERROR in column %d: unexpected data after statement\n", columnNum);
		return NULL;
	}
	int bracketsCount = 0;
	size_t i;
	for (i = 1; i < strlen(firstBracket); i++)
	{
		if (firstBracket[i] == '(')
		{
			bracketsCount += 1;
		}
		else if (firstBracket[i] == ')')
		{
			bracketsCount -= 1;
		}
	}

	if (bracketsCount > 0)
	{
		printf("ERROR in column %d: brackets are not closed\n", columnNum);
		return NULL;
	}

	int prefixLen = strlen(input) - strlen(firstBracket);
	char prefixBuf[prefixLen];
	char *copied = strncpy(prefixBuf, input, prefixLen);
	if (copied == NULL)
	{
		printf("ERROR in column %d: read prefix error\n", columnNum);
		return NULL;
	}
	if (strlen(CIRCLE) == prefixLen && strncmp(input, CIRCLE, strlen(CIRCLE)) == 0)
	{
		data[0] = circleFlag;
		return parseCircle(firstBracket, data, columnNum, circleArguments);
	}
	printf("ERROR in column %d: unexpected prefix: expected <circle>\n", columnNum);
	return NULL;
}
