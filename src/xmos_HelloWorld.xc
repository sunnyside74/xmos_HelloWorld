/**
 * @file    xmos_HelloWorld.xc
 *
 * @date    2015. 1. 17.
 * @author  iMacHome
 */

#include <stdio.h>

void call_reference_sample(int&);

int main(void)
{
	int k = 10;

	printf("Hello XMOS World!!\n");
	printf("Hello AVB World!!\n");
	printf("Hello Git World!!\n");

	printf("Before k is %d\n", k);

	call_reference_sample(k);

	printf("after k is %d\n", k);

	return 0;
}

/**
 *
 * @param value
 */
void call_reference_sample(int &value)
{
	int i;
	int &x = i;
	int a[5] = { 1, 2, 3, 4, 5 };
	int &y = a[0];

	i = value;

	printf("The Value of i is %d\n", i);
	printf("The Value of x is %d\n", x);

	x = 7;
	printf("x has been updated to %d\n", x);
	printf("i has also been updated to %d\n", i);

	printf("y has value %d\n", y);

//	*value = i;
	value = i;

}
