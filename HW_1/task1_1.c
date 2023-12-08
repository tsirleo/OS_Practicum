#include <stdio.h>

//подсчет количества символов в двоичном виде числа
int Digits(unsigned int a)
{	
	int i=0;
	while (a!=0)
	{
		a >>= 1;
		i+=1;
	}
	return i;
}

//получение значение заданного бита числа
int Take_bit(unsigned int a, int n)
{
	return ((a>>n)&1);
}

//печать двоичного числа 
void Printer(unsigned int a)
{
	int i=(sizeof(a)*8-1);
	while (i>=0)
	{
			printf("%d", Take_bit(a,i));
			i-=1;
	}
	printf("\n");
}

unsigned int Transformation(unsigned x)
{ 
	int n=sizeof(x)*8;
	int flag=1;
	for(int i=0;i<8;i++)
	{
		if (Take_bit(x,i)==Take_bit(x,(n-8+i)))
			continue;
		else
		{
			flag=0;
		}
	}
	if (flag)
		return x;
	else
	{
		for(int i=0;i<8;i++)
		{
			if (Take_bit(x,i)==Take_bit(x,(n-8+i)))
				continue;
			else
			{
				x = x^(1<<i);
				x = x^(1<<(n-8+i));
			}
		}
		int i=8;
		while(i<(n-8))
		{
			x = x^(1<<i);
			i+=2;
		}
	}
	return x;
}

int main()
{
	unsigned x;
	scanf("%u", &x);
	printf("число X в двоичном виде = ");
	Printer(x);
	printf("число X в 16-ричном виде = %x \n", x);
	printf("число X после вызова функции = ");
	Printer(Transformation(x));
	return 0;
}
