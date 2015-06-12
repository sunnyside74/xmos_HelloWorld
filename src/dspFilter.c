/**
 * @file	dspFilter.c
 *
 *  Created on: 2015. 6. 10.
 *      Author: i04055dt
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "dspFilter.h"

extern const float g_twoPi;
extern const float g_fs;

/**
 * @brief 2nd Order Low Frequency Shelving Filter Coefficient Calculation Function
 *
 * @param param_FiltCoef
 * @param param_freq
 * @param param_qValue
 * @param param_gainDb
 */
void ShelvingFilter2ndLow(
		_FILT_COEF *param_FiltCoef,
		float param_freq,
		float param_qValue,
		float param_gainDb
		)
{
	float w0;
	float A;
	float alpha;
	float cosW0;
	float b0, b1, b2, a0, a1, a2;

	float f0;
	float gainDb;
	float qValue;

	f0 = param_freq;
	gainDb = param_gainDb;
	qValue = param_qValue;

	w0 = (float)g_twoPi * f0 / (float)g_fs;
	A = pow(10.0, (gainDb / 40.0));
	cosW0 = cos(w0);
	alpha = sin(w0)/(2.0 * qValue);
//	printf("alpha2 = %f\n", alpha);

	b0 = A *((A + 1.0) - ((A - 1.0) * cosW0) + (2.0 * pow(A, 0.5) * alpha));
	b1 = 2.0 * A * ((A - 1.0) - ((A + 1.0) * cosW0));
	b2 = A *((A + 1.0) - ((A - 1.0) * cosW0) - (2.0 * pow(A, 0.5) *alpha));
	a0 = (A + 1.0) + ((A - 1.0) * cosW0) + (2.0 * pow(A, 0.5) * alpha);
	a1 = -2.0 * ((A - 1.0) + ((A + 1.0) * cosW0));
	a2 = (A + 1.0) + ((A - 1.0) * cosW0) - (2.0 * pow(A, 0.5) * alpha);

//	param_FiltCoef->b0 = (b0 * 0.25) / a0;
//	param_FiltCoef->b1 = (b1 * 0.25) / a0;
//	param_FiltCoef->b2 = (b2 * 0.25) / a0;
	param_FiltCoef->b0 = (b0 * 0.0625) / a0;
	param_FiltCoef->b1 = (b1 * 0.0625) / a0;
	param_FiltCoef->b2 = (b2 * 0.0625) / a0;
	param_FiltCoef->a1 = (a1 * (-0.5)) / a0;
	param_FiltCoef->a2 = (a2 * (-0.5)) / a0;
}

/**
 * @brief 2nd Order High Frequency Shelving Filter Coefficient Calculation
 * @param param_FiltCoef
 * @param param_freq
 * @param param_gainDb
 * @param param_qValue
 */
void ShelvingFilter2ndHigh(
		_FILT_COEF *param_FiltCoef,
		float param_freq,
		float param_qValue,
		float param_gainDb
		)
{
	float w0;
	float A;
	float alpha;
	float cosW0;
	float b0, b1, b2, a0, a1, a2;

	float f0;
	float gainDb;
	float qValue;

	f0 = param_freq;
	gainDb = param_gainDb;
	qValue = param_qValue;

	w0 = (float)g_twoPi * f0 / (float)g_fs;
	A = pow(10.0, (gainDb / 40.0));
	cosW0 = cos(w0);
	alpha = sin(w0)/(2.0 * qValue);

	b0 = A * ((A + 1.0) + ((A - 1.0) * cosW0) + (2.0 * pow(A,0.5) * alpha));
	b1 = -2.0 * A * ((A - 1.0) + ((A + 1.0) * cosW0));
	b2 = A * ((A + 1.0) + ((A - 1.0) * cosW0) - (2.0 * pow(A,0.5) * alpha));
	a0 = (A + 1.0) - ((A - 1.0) * cosW0) + (2.0 * pow(A,0.5) * alpha);
	a1 = 2.0 * ((A - 1.0) - ((A + 1.0) * cosW0));
	a2 = (A + 1.0) - ((A - 1.0) * cosW0) - (2.0 * pow(A,0.5) * alpha);

//	param_FiltCoef->b0 = (b0 * 0.25) / a0;
//	param_FiltCoef->b1 = (b1 * 0.25) / a0;
//	param_FiltCoef->b2 = (b2 * 0.25) / a0;
	param_FiltCoef->b0 = (b0 * 0.0625) / a0;
	param_FiltCoef->b1 = (b1 * 0.0625) / a0;
	param_FiltCoef->b2 = (b2 * 0.0625) / a0;
	param_FiltCoef->a1 = (a1 * (-0.5)) / a0;
	param_FiltCoef->a2 = (a2 * (-0.5)) / a0;
}

/**
 * 2nd Order Peaking Filter Coefficient Calculation Function
 * @param param_FiltCoef
 * @param param_freq
 * @param param_qValue
 * @param param_gainDb
 */
void PeakingFilter(
		_FILT_COEF *param_FiltCoef,
		float param_freq,
		float param_qValue,
		float param_gainDb
		)
{
	float w0;
	float A;
	float alpha;
	float cosW0;
	float b0, b1, b2, a0, a1, a2;

	float f0;
	float gainDb;
	float qValue;

	f0 = param_freq;

	gainDb = param_gainDb;
	qValue = param_qValue;

	w0 = (float)g_twoPi * f0 / (float)g_fs;
	A = pow(10.0, (gainDb / 40.0));
	cosW0 = cos(w0);
	alpha = sin(w0) / (2.0 * qValue);

	b0 = 1.0 + alpha * A;
	b1 = -2.0 * cos(w0);
	b2 = 1.0 - alpha * A;
	a0 = 1 + alpha / A;
	a1 = -2.0 * cos(w0);
	a2 = 1.0 - alpha / A;

//	param_FiltCoef->b0 = (b0 * 0.25) / a0;
//	param_FiltCoef->b1 = (b1 * 0.25) / a0;
//	param_FiltCoef->b2 = (b2 * 0.25) / a0;
	param_FiltCoef->b0 = (b0 * 0.0625) / a0;
	param_FiltCoef->b1 = (b1 * 0.0625) / a0;
	param_FiltCoef->b2 = (b2 * 0.0625) / a0;
	param_FiltCoef->a1 = (a1 * (-0.5)) / a0;
	param_FiltCoef->a2 = (a2 * (-0.5)) / a0;
}

/**
 * 2nd Order Biquad PEQ Filter Coefficient Calculation Function
 * @param param_FiltCoef
 * @param param_freq
 * @param param_gainDb
 * @param param_qValue
 */
void PeqFilter(
		_FILT_COEF *param_FiltCoef,
		float param_freq,
		float param_qValue,
		float param_gainDb
		)
{
	float wc, w3;
	float Qb;
	float gainLin;
	float sinWc64, cosWc;
	float den, opa2, gtoma2;
	float b0, b1, b2, a1, a2;

	float f0;
	float gainDb;
	float qValue;

	f0 = param_freq;
	gainDb = param_gainDb;
	qValue = param_qValue;

	wc = (float)g_twoPi * f0 / (float)g_fs;
	sinWc64 = sin(wc) / 64.0;
	cosWc = cos(wc);
	w3 = wc * (sqrt((qValue / 32.0 * qValue / 32.0 + 1.0 / 4096.0)) - 1.0 / 64.0) / (qValue /32.0);
	Qb = sin(w3) * sinWc64 / (cos(w3) - cosWc);
	gainLin = pow(10.0, gainDb/20.0);

	if (gainDb < 0.0)
	{
		Qb *= gainLin;
	}

	den = (Qb + sinWc64);
	a1 = (Qb * cosWc) / (den);
	a2 = (-Qb + sinWc64) / (den * 2.0);
//	opa2 = (1.0 / 2.0 - a2);
//	gtoma2 = gainLin * (1.0 / 2.0 + a2);
//	b0 = (opa2 + gtoma2) / 4.0;
//	b1 = -a1 / 2.0;
//	b2 = (opa2 - gtoma2) / 4.0;
	opa2 = (0.5 - a2);
	gtoma2 = gainLin * (0.5 + a2);
	b0 = (opa2 + gtoma2) * 0.25;
	b1 = -a1 * 0.5;
	b2 = (opa2 - gtoma2) * 0.25;

//	param_FiltCoef->b0 = b0;
//	param_FiltCoef->b1 = b1;
//	param_FiltCoef->b2 = b2;
	param_FiltCoef->b0 = b0 * 0.25;
	param_FiltCoef->b1 = b1 * 0.25;
	param_FiltCoef->b2 = b2 * 0.25;
	param_FiltCoef->a1 = a1;
	param_FiltCoef->a2 = a2;
}

/**
 * 1st Order Low Frequency Shelving Filter Coefficient Calculation Function
 * @param param_FiltCoef
 * @param param_freq
 * @param param_gainDb
 * @param param_qValue
 */
void ShelvingFilter1stLow(
		_FILT_COEF *param_FiltCoef,
		float param_freq,
		float param_qValue,
		float param_gainDb
		)
{
	float w0;
	float A;
	float alpha;
	float cosW0;
	float b0, b1, b2, a0, a1, a2;
	float ggg, aaa;
	float tanWc;

	float f0;
	float gainDb;
	float qValue;

	f0 = param_freq;
	gainDb = param_gainDb;
	qValue = param_qValue;

	w0 = (float)g_twoPi * f0 / (float)g_fs;
	A = pow(10.0, (gainDb / 40.0));
	cosW0 = cos(w0);
	alpha = sin(w0)/(2.0 * qValue);

	a0 = (A + 1.0) + ((A - 1.0) * cosW0) + (2.0 * pow(A, 0.5) * alpha);

	tanWc = tan(w0 * 0.5);
/*	Compute coefficients */
	ggg = pow(10, gainDb / 20);

	if (ggg < 1)
	{
		tanWc = tanWc / ggg;
	}

	aaa = (tanWc - 1) / (tanWc + 1);
/*	Compute low shelf coefficients a_1/2, b_0/4 and b_1/4 */
	a1 = aaa;
	a2 = 0.0;
	b0 = (((1 + aaa) / 2) * (ggg / 4) + (1 - aaa) / 8) * 4;
	b1 = (((1 + aaa) / 2) * (ggg / 4) - (1 - aaa) / 8) * 4;
	b2 = 0.0;

/*	Scale coefficients to match DSP implemention */
	b0 = (b0 * 0.25) / a0;
	b1 = (b1 * 0.25) / a0;
	b2 = (b2 * 0.25) / a0;
	a1 = (a1 * (-0.5)) / a0;
	a2 = (a2 * (-0.5)) / a0;

	param_FiltCoef->b0 = b0;
	param_FiltCoef->b1 = b1;
	param_FiltCoef->b2 = b2;
	param_FiltCoef->a1 = a1;
	param_FiltCoef->a2 = a2;

}

