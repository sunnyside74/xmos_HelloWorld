/**
 * @file    xmos_HelloWorld.xc
 *
 * @date    2015. 1. 17.
 * @author  iMacHome
 */

#include <stdio.h>
#include <stdlib.h>
#include <xs1.h>

void call_reference_sample(int*);
{int, int, int} multi_return_sample(int, int, int);

/**
 * @brief	Main 함수
 * @return	Success: 0, Error: -1
 */
int main(void)
{
	int k = 10;
	int l = 0;
	int m = 0;
	int n = 0;

	printf("Hello XMOS World!!\n");
//	printf("Hello AVB World!!\n");
//	printf("Hello Git World!!\n");

	printf("Before k is %d\n", k);

	call_reference_sample(&k);

	printf("after k is %d\n", k);

	{l, m, n} = multi_return_sample(1, 2, 3);		/**< 1,2,3을 입력하였을 때, 3,2,1을 Return */

	printf("l = %d, m = %d, n = %d \n", l, m, n);

	return 0;
}

/**
 * @brief	참조형 변수(reference) 예제
 * @param 	value 	포인터
 */
void call_reference_sample(int *value)
{
	int i;
	int &x = i;
	int a[5] = { 1, 2, 3, 4, 5 };
	int &y = a[0];

	i = *value;

	printf("The Value of i is %d\n", i);
	printf("The Value of x is %d\n", x);

	x = 7;
	printf("x has been updated to %d\n", x);
	printf("i has also been updated to %d\n", i);

	printf("y has value %d\n", y);

	*value = i;

}

/**
 * @brief	xc에서 지원하는 Multi-Return 샘플\n
 * 			입력값 x, y, z를 z, y, x로 순서를 변경하여 한번에 return하게 함
 * @param 	x
 * @param 	y
 * @param	z
 * @return
 */
{int, int, int} multi_return_sample(int x, int y, int z)
{

	return {z, y, x};
}

