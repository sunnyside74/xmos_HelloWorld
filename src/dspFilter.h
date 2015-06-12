/**
 * dspFilter.h
 *
 *  Created on: 2015. 6. 10.
 *      Author: i04055dt
 */

#ifndef DSPFILTER_H_
#define DSPFILTER_H_

/**
 * @brief	Floating point Filter Coefficient Structures
 * @remarks	All Member type is float(floating Point)
 */
typedef struct __FILT_COEF
{
	float b0;
	float b1;
	float b2;
	float a1;
	float a2;
} _FILT_COEF;

/**
 * @brief	Q Formatted Filter Coefficient Sturctures
 * @remarks	All Member type is int(integer)
 */
typedef struct __Q_FORMAT
{
	int b0;
	int b1;
	int b2;
	int a1;
	int a2;
} _Q_FORMAT;


void ShelvingFilter2ndLow( _FILT_COEF *param_FiltCoef, float param_freq,
								float param_qValue, float param_gainDb	);

void ShelvingFilter2ndHigh( _FILT_COEF *param_FiltCoef, float param_freq,
								float param_qValue, float param_gainDb	);

void PeakingFilter( _FILT_COEF *param_FiltCoef, float param_freq, float param_qValue, float param_gainDbc );

void PeqFilter( _FILT_COEF *param_FiltCoef, float param_freq, float param_qValue, float param_gainDb );

void ShelvingFilter1stLow( _FILT_COEF *param_FiltCoef, float param_freq,
								float param_qValue, float param_gainDb	);


#endif /* DSPFILTER_H_ */
