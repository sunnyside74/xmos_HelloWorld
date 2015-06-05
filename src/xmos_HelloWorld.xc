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
 * @brief	Main �Լ�
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

	{l, m, n} = multi_return_sample(1, 2, 3);		/**< 1,2,3�� �Է��Ͽ��� ��, 3,2,1�� Return */

	printf("l = %d, m = %d, n = %d \n", l, m, n);

	return 0;
}

/**
 * @brief	������ ����(reference) ����
 * @param 	value 	������
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
 * @brief	xc���� �����ϴ� Multi-Return ����\n
 * 			�Է°� x, y, z�� z, y, x�� ������ �����Ͽ� �ѹ��� return�ϰ� ��
 * @param 	x
 * @param 	y
 * @param	z
 * @return
 */
{int, int, int} multi_return_sample(int x, int y, int z)
{

	return {z, y, x};
}

