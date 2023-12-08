#include <stdio.h>
#include <stdlib.h>

char* Read_unsigned_string(void)
{
	unsigned basis=4;
	unsigned size=0;
	unsigned i=0;
	char c;
	char* str;
	str = (char*)malloc(size+=basis);
	while ((c=getchar())!='\n')
	{
		str[i++]=c;
		if (i==size)
			str = (char*)realloc(str, size+=basis);
	}
	str[i] = '\0';
	return str;
}

int main()
{
	char *ch=Read_unsigned_string();
	printf("%s \n", ch);
	return 0;
}

