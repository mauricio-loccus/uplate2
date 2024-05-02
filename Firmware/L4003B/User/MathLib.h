

#define SPLINE_POINT_MAX 12
#define LINEAR_EQUATION_VARIABLE_MAX 12
//#define ANALYSIS_SUCCESS 0
#define ANALYSIS_ERROR 1

float aa[LINEAR_EQUATION_VARIABLE_MAX][LINEAR_EQUATION_VARIABLE_MAX];
float bb[LINEAR_EQUATION_VARIABLE_MAX];
int N;

//返回0说明OK， 返回1说明失败。
int LinearEquationCreate(float* a1, float* b1, int N1);
//返回0说明OK， 返回1说明失败。
int LinearEquationGetSolution(float* x1);
int GaussianElimination(int n);


//LeastSquareMethod begin
float* m_pXLsm;
float* m_pYLsm;
int m_nTotal;
/*
int ANALYSIS_SUCCESS = 0, ANALYSIS_ERROR_CALIBRATOR_NUMBER = 1, ANALYSIS_ERROR_FITTING_FAIL = 2
		, ANALYSIS_ERROR_LOGX_FAIL = 3, ANALYSIS_ERROR_LOGY_FAIL = 4, ANALYSIS_ERROR_DISABLE_CONCENTRATION = 5
		, ANALYSIS_ERROR_DISABLE_LOG_CONCENTRATION = 6, ANALYSIS_ERROR_LOG_CONCENTRATION = 7, ANALYSIS_ERROR_ABS_NEGATIVE = 8
		, ANALYSIS_ERROR_MAX = 9;*/
//LeastSquareMethod end

//四参数开始
float a, b, c, d;
float a_lm, b_lm, c_lm, d_lm;
float m_dA[4][4];
float m_dB[4];
float* m_pX;
float* m_pY;
float* m_pXInit; //获取a、b、c、d初值x、y变换值
float* m_pYInit;
int m_nSerial[4]; //最大4个误差
float m_dRR;
float m_dRRBack;
float m_dYAverage;
float m_dYMax;
float m_dYMin;
float rss, tss;
float* r2;

float* J;
float* H;
float* dc;
float* ycal_lm;
float* dc_lm;
//四参数结束

//三次样条开始
float* m_pXSpline;
float* m_pYSpline;
//	int m_nTotal;
float m_dDerivative[SPLINE_POINT_MAX];
float m_dH[SPLINE_POINT_MAX];
float m_dM[SPLINE_POINT_MAX];
float m_dD[SPLINE_POINT_MAX];
float m_dMiu[SPLINE_POINT_MAX];
float m_dLamda[SPLINE_POINT_MAX];
float m_dAB[SPLINE_POINT_MAX * SPLINE_POINT_MAX];
int loopCount;
//三次样条结束

/*

float *GetComplement(float *a2, int n, int nx, int ny);
float CalculateDeterminantN(float *a2, int n);
float *getInverseMatrix(float *a2, int n);
float *MatrixMulty(float* a1, int m, int n, float* b1, int k);
float *MatrixReverse(float* a1, int m, int n);


int LsmCreate(float* pX, float* pY, int nTotal);
float GetAverageX(void);
float GetAverageY(void);
float GetAverageXX(void);
float GetAverageYY(void);
float GetAverageXY(void);
float LsmGetRR(int* nErrorCode);
float LsmGetSlope(int* nErrorCode);
float LsmGetIntercept(int* nErrorCode);


void GetCoef(float* dCoef);
float GetY(float& dX);
float LogisticGetRR();
float GetDYDA(float& dX);
float GetDYDD(float& dX);
float GetDYDC(float& dX);
float GetDYDB(float& dX);
bool GetInitBC();
bool InitPara();
bool LogisticCreate(float* pX, float* pY, int nTotal);
float LogisticCalculateXValue(float f);



bool InitSplinePara();
float calculateDerivative(float dx);
bool SplineCreate(float* pX, float* pY, int nTotal);
void GetM(float* dM);
void GetH(float* dH);
float SplineCalculateYValue(float dx);
float ErFenFa_CalculateXValue(float dy);
float NewTonCalculateXValue(float dy);
float GeXianFaCalculateXValue(float dy);
void setLoopCount(int value);
*/