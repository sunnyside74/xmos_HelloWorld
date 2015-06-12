/**
 * @file	dspQFormatConvert.c
 *
 * @date	2015. 6. 10.
 * @author	i04055dt
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dspFilter.h"
#include "dspQFormatConvert.h"

const float	g_twoPi	= 6.283185307179586476925286766559;
const float	g_fs	= SAMPLE_RATE;

const unsigned char str2ndLoShelfFilter[] = 	"2nd Order Low Shelf Filter:\0";
const unsigned char str2ndHiShelfFilter[] = 	"2nd Order High Shelf Filter:\0";
const unsigned char strPeakFilter[] 		= 	"Peaking Filter:\0";
const unsigned char strPeqFilter[] 		=	"Parametric EQ Filter:\0";
const unsigned char str1stLoShelfFilter[] = 	"1st Order Low Shelf Filter:\0";

/**
 * @brief Floating Point Filter Coefficient convert to Fixed Point Q Format Qm.n\n
 * 			- Input/Output is the Structure of Filter Coefficients & Q Format Coefficients
 *
 * @param param_tFiltCoef		Src: Floating Point Filter Coefficient
 * @param param_tFiltQForm		Des: Q Format Integer Filter Coefficient
 * @param fixNum				Q Format Fixed Bit Number
 * @param fracNum				Q Format Fraction Bit Number
 * @return No Error: 0, Error: -1
 */
int Float2QFormatConvert(
		_FILT_COEF param_tFiltCoef,
		_Q_FORMAT *param_tFiltQForm,
		unsigned int fixNum,
		unsigned int fracNum
		)
{
	int ret = 0;

	_FILT_COEF tFiltCoef;
	_Q_FORMAT tFiltQForm;

	tFiltCoef = param_tFiltCoef;

	if (tFiltCoef.b0 < 0.0) 	tFiltQForm.b0 = ~((int)(tFiltCoef.b0 * (pow(-2, fracNum) - 1))) + 1;
	else 						tFiltQForm.b0 = (int)(tFiltCoef.b0 * (pow(2, fracNum) - 1));

	if (tFiltCoef.b1 < 0.0) 	tFiltQForm.b1 = ~((int)(tFiltCoef.b1 * (pow(-2, fracNum) - 1))) + 1;
	else 						tFiltQForm.b1 = (int)(tFiltCoef.b1 * (pow(2, fracNum) - 1));

	if (tFiltCoef.b2 < 0.0) 	tFiltQForm.b2 = ~((int)(tFiltCoef.b2 * (pow(-2, fracNum) - 1))) + 1;
	else 						tFiltQForm.b2 = (int)(tFiltCoef.b2 * (pow(2, fracNum) -1));

	if (tFiltCoef.a1 < 0.0) 	tFiltQForm.a1 = ~((int)(tFiltCoef.a1 * (pow(-2, fracNum) - 1))) + 1;
	else 						tFiltQForm.a1 = (int)(tFiltCoef.a1 * (pow(2, fracNum) - 1));

	if (tFiltCoef.a2 < 0.0) 	tFiltQForm.a2 = ~((int)(tFiltCoef.a2 * (pow(-2, fracNum) - 1))) + 1;
	else 						tFiltQForm.a2 = (int)(tFiltCoef.a2 * (pow(2, fracNum) - 1));

	*param_tFiltQForm = tFiltQForm;

	return ret;
}

/**
 * @brief
 * @param param_filtQForm	Src: Q Format Integer Filter Coefficient
 * @param param_filtCoef	Des: Floating Point Filter Coefficient
 * @param fixNum			Q Format Fixed Bit Number
 * @param fracNum			Q Format Fraction Bit Number
 * @return
 */
int QFormat2FloatConvert(
		_Q_FORMAT param_filtQForm,
		_FILT_COEF *param_filtCoef,
		unsigned int fixNum,
		unsigned int fracNum
		)
{
	int ret = 0;

	return ret;
}

/**
 * Print Filter Coefficient Floating Value And Q1.31 Format
 * @param mode				EQ Filter Mode\n
 *  							- 0: Low Pass Shelving Filter\n
 *  							- 1: High Pass Shelving Filter\n
 *  							- 2: Peak Filter\n
 *  							- 3: Parametric EQ Filter\n
 *  							- 4: 1st order Low Pass Shelving Filter
 * @param param_tFiltCoef
 * @param param_tFiltQForm
 * @param valFreq
 * @param valQ
 * @param valGain
 */
void PrintCoef(
		int mode,
		_FILT_COEF param_tFiltCoef,
		_Q_FORMAT param_tFiltQForm,
		float valFreq,
		float valQ,
		float valGain
		)
{
	unsigned char *str;

	switch (mode)
	{
		case 0:
			str = (unsigned char*)str2ndLoShelfFilter;
			break;

		case 1:
			str = (unsigned char*)str2ndHiShelfFilter;
			break;

		case 2:
			str = (unsigned char*)strPeakFilter;
			break;

		case 3:
			str = (unsigned char*)strPeqFilter;
			break;

		case 4:
			str = (unsigned char*)str1stLoShelfFilter;
			break;

		default:
			break;

	}

	printf("\n");
	printf("%s %f Hz, Q: %f, %f dB\n", str, valFreq, valQ, valGain);
//	printf("b0 = %f\n", param_tFiltCoef.b0);
//	printf("b1 = %f\n", param_tFiltCoef.b1);
//	printf("b2 = %f\n", param_tFiltCoef.b2);
//	printf("a1 = %f\n", param_tFiltCoef.a1);
//	printf("a2 = %f\n", param_tFiltCoef.a2);
//
//	printf("\n");
//
//	printf("b0 = 0x%08x\n", param_tFiltQForm.b0);
//	printf("b1 = 0x%08x\n", param_tFiltQForm.b1);
//	printf("b2 = 0x%08x\n", param_tFiltQForm.b2);
//	printf("a1 = 0x%08x\n", param_tFiltQForm.a1);
//	printf("a2 = 0x%08x\n", param_tFiltQForm.a2);

	printf("a1 = %f\n", param_tFiltCoef.a1);
	printf("b2 = %f\n", param_tFiltCoef.b2);
	printf("b0 = %f\n", param_tFiltCoef.b0);
	printf("b1 = %f\n", param_tFiltCoef.b1);
	printf("a2 = %f\n", param_tFiltCoef.a2);

	printf("\n");

	printf("a1 = 0x%08x\n", param_tFiltQForm.a1);
	printf("b2 = 0x%08x\n", param_tFiltQForm.b2);
	printf("b0 = 0x%08x\n", param_tFiltQForm.b0);
	printf("b1 = 0x%08x\n", param_tFiltQForm.b1);
	printf("a2 = 0x%08x\n", param_tFiltQForm.a2);

//	scanf("");

}


/**
 * @brief Q Format Converter Function
 * @param param_filtCoef	Src: Floating Point Filter Coefficient
 * @param param_filtQForm	Des: Q Format Integer Filter Coefficient
 * @param fracNum			Q Format Fraction Bit Number (n number of Qm.n format)
 * @return Error -1, Normal: 0
 */
int QFormatConvert(
		float param_filtCoef,
		int *param_filtQForm,
		unsigned int fracNum
		)
{
	int ret = 0;

	float filtCoef;
	int *filtQForm = param_filtQForm;

	filtCoef = param_filtCoef;

	/* Negative Filter Coefficient */
	if (filtCoef < 0.0)
	{
		filtQForm = (int*)(~((int)(filtCoef * (pow(-2, fracNum) - 1))) + 1);
	}
	/* Positive Filter Coefficient */
	else
	{
		filtQForm = (int*)((int)(filtCoef * (pow(2, fracNum) - 1)));
	}

	return ret;
}

/**
 *
 * @param param_filtQForm
 * @param param_filtCoef
 * @param fracNum
 * @return Error
 */
int QForm2FloatConverter(
		int param_filtQForm,
		float *param_filtCoef,
		unsigned int fracNum
		)
{
	return 0;
}

