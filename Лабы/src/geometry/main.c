#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <libgeometry/parse.h>
#include <ctype.h>

#define CIRCLE "circle"
#define circleFlag 1
const float PI = 3.14159265358979323846;
int lineLenght = 255, circleArguments = 3, dataSize = 9, columnNum = 0;
int main()
{
	char firstLine[lineLenght];
	int n;
	int read = sscanf(fgets(firstLine, lineLenght, stdin), "%d", &n);
	if (read < 1)
	{
		printf("ERROR in column %d: figures count did not read\n", columnNum);
		return 1;
	}
	float figures[n][dataSize];
	int i;
	for (i = 0; i < n; i++)
	{
		columnNum++;
		char text[lineLenght];
		char *written = fgets(text, lineLenght, stdin);
		if (written == NULL)
		{
			printf("ERROR in column %d: input error\n", columnNum);
			return 1;
		}

		float *result = (float *)calloc(dataSize, sizeof(float));
		float *data = parse(text, result, columnNum, circleArguments);
		if (data == NULL)
		{
			printf("ERROR in column %d: parse error\n", columnNum);
			return 1;
		}
		memcpy(figures[i], data, dataSize * sizeof(float));
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		switch ((int)figures[i][0])
		{
		case circleFlag:
			printf("circle(%.2f %.2f, %.2f)\n", figures[i][1], figures[i][2], figures[i][3]);
			printf("perimetr = %.2f\n", 2 * PI * figures[i][3]);
			printf("area = %.2f\n", PI * pow(figures[i][3], 2));
			break;
		}
		printf("\n");
	}
	return 0;
}
