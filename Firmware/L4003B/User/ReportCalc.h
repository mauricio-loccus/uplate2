

#ifndef __REPORT_CALC_H
#define __REPORT_CALC_H

void GetAxisMin(float *dX);
void GetAxisMax(float *dX);
void GetAxisLimits(float *dXMin, float *dXMax, float *dYMin, float *dYMax, double *p_dX, double *p_dY);
void GetAxisLimits2(float *dYMin, float *dYMax,double *p_dY);
void GetAxisLimitsKinetic(float *dXMin, float *dXMax, float *dYMin, float *dYMax, double *p_dX, double *p_dY);
unsigned char PreCalOK(void);
void SearchForBlanks(void);
void SearchForStandards(unsigned char nStandard);
int SearchForNCPC(signed char wcCurrentFilter);
int SearchForQC(unsigned char wcCurrentFilter);
void GetResultABS(unsigned char nChannel, unsigned char nCycle);///////////////////////
void GetCalibrationPara(void);
void MakeABSCalibration(void);
void MeasureFinishProcess(void);


void Preproccessing(unsigned char wcCycle);
void GetKineticABS(unsigned char wcCycle);/////////////////////////////////

int DoFactorAnalysis(unsigned char  wcCurrentFilter);
int DoLinearAnalysis(unsigned char  wcCurrentFilter);
int DoLogitlogAnalysis(unsigned char wcCurrentFilter);
int DoPtoPAnalysis(unsigned char wcCurrentFilter);
int DoSplineAnalysis(unsigned char  wcCurrentFilter);
unsigned char DoSplineAnalysisFullBoard(unsigned char  wcCurrentFilter);
void SearchForPlateLimits(unsigned char wcCurrentFilter, float *dYMin, float *dYMax);
int DoLogisticAnalysis(unsigned char wcCurrentFilter);//////////////////////



#endif
