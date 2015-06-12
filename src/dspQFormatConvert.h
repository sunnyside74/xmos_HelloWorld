/**
 * @file	dspQFormatConvert.h
 *
 * @date	2015. 6. 12.
 * @author	i04055dt
 */

#ifndef DSPQFORMATCONVERT_H_
#define DSPQFORMATCONVERT_H_

#define		SAMPLE_RATE 		48000		///< Audio Sampling Rate = 48000Hz

#ifndef M_LN2
	#define M_LN2 0.69314718055994530942	///<
#endif	/* M_LN2 */

#ifndef M_PI
	#define M_PI 3.14159265358979323846		///< Pi Value
#endif /* M_PI */

//#include "dspFilter.h"

extern int Float2QFormatConvert( _FILT_COEF param_tFiltCoef, _Q_FORMAT *param_tFiltQForm,
										unsigned int fixNum, unsigned int fracNum );

extern void PrintCoef( int mode, 	_FILT_COEF param_tFiltCoef, _Q_FORMAT param_tFiltQForm,
							float valFreq, float valQ, float valGain );

extern int QFormatConvert( float param_filtCoef, int *param_filtQForm, unsigned int fracNum );

#endif /* DSPQFORMATCONVERT_H_ */
