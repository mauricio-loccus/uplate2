

#define SPLINE_POINT_MAX 12
#define LINEAR_EQUATION_VARIABLE_MAX 12
//#define ANALYSIS_SUCCESS 0
#define ANALYSIS_ERROR 1


#define INT_MAX       2147483647    /* maximum (signed) int value */

/*
//LeastSquareMethod begin
enum
{
     ANALYSIS_SUCCESS = 0,
	 ANALYSIS_ERROR_CALIBRATOR_NUMBER = 1,
	 ANALYSIS_ERROR_FITTING_FAIL = 2,
	 ANALYSIS_ERROR_LOGX_FAIL = 3,
	 ANALYSIS_ERROR_LOGY_FAIL = 4,
	 ANALYSIS_ERROR_DISABLE_CONCENTRATION = 5,
	 ANALYSIS_ERROR_DISABLE_LOG_CONCENTRATION = 6,
	 ANALYSIS_ERROR_LOG_CONCENTRATION = 7,
	 ANALYSIS_ERROR_ABS_NEGATIVE = 8,
	 ANALYSIS_ERROR_MAX = 9,
};

//LeastSquareMethod end
*/


#ifndef __CALC_LIB_H
#define __CALC_LIB_H

/*

//线性方程,x,y和Total
double aa[LINEAR_EQUATION_VARIABLE_MAX][LINEAR_EQUATION_VARIABLE_MAX];
double bb[LINEAR_EQUATION_VARIABLE_MAX];
int N;


//LeastSquareMethod begin
//double* m_pXLsm;
//double* m_pYLsm;
double m_pXLsm[SD_MAX];//12
double m_pYLsm[SD_MAX];
int m_nTotal;



//四参数开始
	double a, b, c, d;
	double a_lm, b_lm, c_lm, d_lm;
	double m_dA[4][4];
	double m_dB[4];
	double m_pX[SD_MAX];
	double m_pY[SD_MAX]; //double*
	double m_pXInit[SD_MAX]; //获取a、b、c、d初值x、y变换值
	double m_pYInit[SD_MAX];
	int m_nSerial[4]; //最大4个误差
	double m_dRR;
	double m_dRRBack;
	double m_dYAverage;
	double m_dYMax;
	double m_dYMin;
	double rss, tss;
    double* r2;

    double* J;
	double* H;
    double* dc;
    double* ycal_lm;
    double* dc_lm;
//四参数结束


//三次样条开始
	double m_pXSpline[SD_MAX];
	double m_pYSpline[SD_MAX];
//	int m_nTotal;
	double m_dDerivative[SPLINE_POINT_MAX];
	double m_dH[SPLINE_POINT_MAX];
	double m_dM[SPLINE_POINT_MAX];
	double m_dD[SPLINE_POINT_MAX];
	double m_dMiu[SPLINE_POINT_MAX];
	double m_dLamda[SPLINE_POINT_MAX];
	double m_dAB[SPLINE_POINT_MAX * SPLINE_POINT_MAX];
	int loopCount;
//三次样条结束

*/
typedef struct
{
    double d_tmp1[4*4];
    //线性方程,x,y和Total
    double aa[LINEAR_EQUATION_VARIABLE_MAX][LINEAR_EQUATION_VARIABLE_MAX];
    double bb[LINEAR_EQUATION_VARIABLE_MAX];
    int N;


    double a, b, c, d;
    double a_lm, b_lm, c_lm, d_lm;

    //LeastSquareMethod begin
    double m_pXLsm[SD_MAX];
    double m_pYLsm[SD_MAX];




    double p_dX[SD_MAX];
    double p_dY[SD_MAX];

    double p_dY2[SD_MAX];
    double p_dY_Lable[SD_MAX];
    double p_dY_Base; //基准吸光度
    // Factor
    double resultK;
    //四参数开始
    double ret;
    double m_dA[4][4];
    double m_dB[4];
    double m_pX[SD_MAX];
    double m_pY[SD_MAX]; //double*
    double m_pXInit[SD_MAX]; //获取a、b、c、d初值x、y变换值
    double m_pYInit[SD_MAX];
    int   m_nSerial[4]; //最大4个误差
    double m_dRR;
    double m_dRRBack;
    double m_dYAverage;
    double m_dYMax;
    double m_dYMin;
    double rss, tss;


    // double m_pX[SD_MAX];
    // double m_pY[SD_MAX];
    //double m_pXInit[SD_MAX]; //获取a、b、c、d初值x、y变换值
    //double m_pYInit[SD_MAX];
    double r2[SD_MAX];  //这里为1
    double JReserve[SD_MAX*4];
    double H[4*4];
    double H_lm[4*4];
    double a2[4*4];
    double a3[SD_MAX*4];
    double a4[SD_MAX*4];
    double a5[SD_MAX*4];
    double dp[4];
    double J[SD_MAX*4];
    double dc[SD_MAX];
    double ycal_lm[SD_MAX];
    double dc_lm[SD_MAX];
    double value[8];


    //三次样条开始
    double m_pXSpline[SD_MAX];
    double m_pYSpline[SD_MAX];
    int m_nTotal;
    double m_dDerivative[SPLINE_POINT_MAX];
    double m_dH[SPLINE_POINT_MAX];
    double m_dM[SPLINE_POINT_MAX];
    double m_dD[SPLINE_POINT_MAX];
    double m_dMiu[SPLINE_POINT_MAX];
    double m_dLamda[SPLINE_POINT_MAX];
    double m_dAB[SPLINE_POINT_MAX * SPLINE_POINT_MAX];
    int loopCount;
    unsigned char upDownFlag;//0, 不单调；1，Up; 2, Down
//		float x1;
//		float x;
//		float x2;
    //三次样条结束
		
		 double p,p0,p1;
		 double dTemp;
		 double q0, q1;
		 double h,res,x1,x2;
		 double dMid,x,dFa,dFb,d_tmp;

				
				
				
				
} CALCU_PARA;

extern CALCU_PARA CalcuPara;
//四参数结束







//返回0说明OK， 返回1说明失败。
int LinearEquationCreate(double* a1, double* b1, int N1);
//返回0说明OK， 返回1说明失败。
int LinearEquationGetSolution(double* x1);
int GaussianElimination(int n);



double *GetComplement(double *val,double *a2, int n, int nx, int ny);//lugj171202
double  CalculateDeterminantN(double *a2, int n);
double *getInverseMatrix(double *val,double *a2, int n);
double *MatrixMulty(double* val,double* a1, int m, int n, double* b1, int k);
double *MatrixReverse(double *val,double* a1, int m, int n);


int LsmCreate(double* pX, double* pY, int nTotal);
double GetAverageX(void);
double GetAverageY(void);
double GetAverageXX(void);
double GetAverageYY(void);
double GetAverageXY(void);
double LsmGetRR(int* nErrorCode);
double LsmGetSlope(int* nErrorCode);
double LsmGetIntercept(int* nErrorCode);
//Factor
double LinearViaZeroCalculateK(int* nErrorCode);
double LinearViaZeroGetRR(int* nErrorCode);





void GetCoef(double* dCoef);
//double GetY(double& dX);
double LogisticGetRR(void);
//double GetDYDA(double& dX);
//double GetDYDD(double& dX);
//double GetDYDC(double& dX);
//double GetDYDB(double& dX);
void SetYMin(double dYMin);
void SetYMax(double dYMax);
double GetY(double dX);
double GetDYDA(double dX);
double GetDYDD(double dX);
double GetDYDC(double dX);
double GetDYDB(double dX);
unsigned char GetInitBC(void);
unsigned char InitPara(void);
unsigned char LogisticCreate(double* pX, double* pY, int nTotal);
double LogisticCalculateXValue(double f);



unsigned char InitSplinePara(void);
//double calculateDerivative(double dx);
unsigned char SplineCreate(double* pX, double* pY, int nTotal);
void GetM(double* dM);
void GetH(double* dH);
float SplineCalculateYValue(float dx);
float ErFenFa_CalculateXValue(float dy, unsigned char *nErrorCode); //二分法
float NewTonCalculateXValue(float dy, unsigned char *nErrorCode);   //牛顿法
float GeXianFaCalculateXValue(float dy, unsigned char *nErrorCode); //割线法
//void setLoopCount(int value);

#endif



