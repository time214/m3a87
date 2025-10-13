/* *********************************************************************************************************************************
888b     d888 88888888888 .d8888b.   .d8888b.   .d8888b.   .d8888b.  888b    888  .d8888b.  8888888b.  8888888b.  
8888b   d8888     888    d88P  Y88b d88P  Y88b d88P  Y88b d88P  Y88b 8888b   888 d88P  Y88b 888   Y88b 888   Y88b 
88888b.d88888     888    Y88b. d88P 888    888 888    888 888    888 88888b  888 Y88b.      888    888 888    888 
888Y88888P888     888     "Y88888"  888    888 Y88b. d888 Y88b. d888 888Y88b 888  "Y888b.   888   d88P 888   d88P 
888 Y888P 888     888    .d8P""Y8b. 888    888  "Y888P888  "Y888P888 888 Y88b888     "Y88b. 8888888P"  8888888P"  
888  Y8P  888     888    888    888 888    888        888        888 888  Y88888       "888 888        888 T88b   
888   "   888     888    Y88b  d88P Y88b  d88P Y88b  d88P Y88b  d88P 888   Y8888 Y88b  d88P 888        888  T88b  
888       888     888     "Y8888P"   "Y8888P"   "Y8888P"   "Y8888P"  888    Y888  "Y8888P"  888        888   T88b
   ********************************************************************************************************************************* */
// ****** This project is 100V process and FPVI_PLUS is necessary. ******************************
// ****** This project is 100V process and FPVI_PLUS is necessary. ******************************
// ****** This project is 100V process and FPVI_PLUS is necessary. ******************************
// ****** This project is 100V process and FPVI_PLUS is necessary. ******************************
// ****** This project is 100V process and FPVI_PLUS is necessary. ******************************
// ****** This project is 100V process and FPVI_PLUS is necessary. ******************************
#include "stdafx.h"
#include "math.h"
#define SITENUM	2

void packagetrim(int time);
short site = 0, flag[SITENUM] = { 0, 0 };
short DebugConsole = 1;
float vj = 0;
double adresult[SITENUM][1000] = { 0.0f };

BYTE sitesta[SITENUM] = { 0 };
// ******************************************************************* VI SOURCE DEFINITION *******************************************************************
// FPVI
FPVI10 VIN_FPVI0		(0,	 "VINKelvin");      // VIN  PIN8, high side in
FPVI10 SW2_FPVI3		(3,  "SWSeriesDN");
// FOVI
FOVI EN_FOVI2				(2,  "ENNonK");         // EN   PIN1
FOVI RT_FOVI6				(6,  "RTNonK");         // RT   PIN3
FOVI FB_FOVI8				(8,  "FBKelvin");       // FB   PIN4
FOVI FB100_FOVI9		(9,	 "FBSeries100K");  
FOVI VCC_FOVI10			(10, "VCCKelvin");      // VCC  PIN2
FOVI BST_FOVI7			(7,  "BSTNonK");        // BST  PIN5
FOVI BST2_FOVI12		(12, "BSTKelvin");      // BST  PIN5, VBSTs	=Vsw+Vbst     
FOVI VIN2_FOVI13		(13, "VINSeriesUP");    //						VINs	=Vsw+Vvin  
// OTHER
QTMU_PLUS qtmu0			(0);
CBIT128 rlyC;

////short Trimbit1[SITENUM] = { 0, 0 };		// vbg -4.5mv
////short Trimbit2[SITENUM] = { 0, 0 };		// vbg -9.0mv
////short Trimbit3[SITENUM] = { 0, 0 };		// vbg -8.0mv
////short Trimbit4[SITENUM] = { 0, 0 };		// vbg 36.0mv
////short Trimbit5[SITENUM] = { 0, 0 };		// IPK1 10%
////short Trimbit6[SITENUM] = { 0, 0 };		// IPK2 -10%
////short Trimbit7[SITENUM] = { 1, 1 };		// IQ -5uA
////short Trimbit8[SITENUM] = { 0, 0 };		// Valley1 10%
////short Trimbit9[SITENUM] = { 0, 0 };		// TBTADD, CLKH
////short Trimbit10[SITENUM]= { 0, 0 };		// FPWM
////short Trimbit11[SITENUM]= { 0, 0 };		// BSTCMP
////short Trimbit12[SITENUM]= { 0, 0 };		// DISACLK
////short Trimbit13[SITENUM]= { 0, 0 };		// BSTSLP
////short Trimbit14[SITENUM]= { 0, 0 };		// EABAIS
////short Trimbit15[SITENUM]= { 1, 1 };		// WAIT
////short Trimbit16[SITENUM]= { 1, 1 };		// FREEZE BIT

DUT_API void HardWareCfg()	{
	/*For example: four channels dvi to config two sites*/
	/*StsSetModuleToSite(MD_DVI400, SITE_1, 0, 1, -1);
		StsSetModuleToSite(MD_DVI400, SITE_2, 2, 3, -1);*/
	// FPVI
	StsSetModuleToSite(MD_FPVI10, SITE_1, 0, 1, 2, 3, -1);	// SITE1, IDC1,2
	StsSetModuleToSite(MD_FPVI10, SITE_2, 4, 5, 6, 7, -1);	// SITE2, IDC3,4 
	// FOVI
	StsSetModuleToSite(MD_FOVI, SITE_1,  0,  1,  2,	 3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, -1);
	StsSetModuleToSite(MD_FOVI, SITE_2, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, -1);
	// QTMU
	StsSetModuleToSite(MD_QTMUPLUS, SITE_1, 0, 1 , -1);
	StsSetModuleToSite(MD_QTMUPLUS, SITE_2, 2, 3 , -1);
}

// ******************************************* USER ROUTINE *******************************************
// ******************************************* USER ROUTINE *******************************************
// ******************************************* USER ROUTINE *******************************************
void packagetrim(int time)  { // TM5, FB CLK
	////////////// XA87AA change PPT input to FB pin //////////////
	// Rising edge trimming, the trim power is from VCC regulator when there is a VCC pin
	int t = 0;
	for(t = 0; t < time; t = t + 1) {
		FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_us(150);
		FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_us(150);
	}
	// END rising edge, HoldingTimeForWriting, > 3ms
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(150);	
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(8); // **********
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(5);
}
void pwr0v(void)	{
	VIN_FPVI0.Set			(FV,	float(0), FPVI10_5V, FPVI10_10MA, RELAY_ON);
	SW2_FPVI3.Set			(FV,	float(0), FPVI10_5V, FPVI10_10MA, RELAY_ON);
	
	EN_FOVI2.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
	RT_FOVI6.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
	BST_FOVI7.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
	FB_FOVI8.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
	FB100_FOVI9.Set	  (FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
	VCC_FOVI10.Set		(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
	BST2_FOVI12.Set		(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
	VIN2_FOVI13.Set		(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_ON);
}
void pwr_off(void)	{
	VIN_FPVI0.Set			(FV,	float(0), FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	SW2_FPVI3.Set			(FV,	float(0), FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	
	EN_FOVI2.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
	RT_FOVI6.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
	BST_FOVI7.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
	FB_FOVI8.Set			(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
	FB100_FOVI9.Set	  (FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
	VCC_FOVI10.Set		(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
	BST2_FOVI12.Set		(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
	VIN2_FOVI13.Set		(FV,  float(0), FOVI_5V,	FOVI_10MA,		RELAY_OFF);
}
void FreshSiteFlagInit(void)	{
	short z = 0;
	for (z = 0; z < SITENUM; z++) 
		flag[site] = 1;
  StsGetSiteStatus(sitesta, SITENUM);
  for (z = 0; z < SITENUM; z++) {
		if (sitesta[z]) 
			flag[z] = 0;
  }
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//initialize function will be called before all the test functions.
DUT_API void InitBeforeTestFlow()	{
 	qtmu0.Init();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//initializefunction will be called after all the test functions.
DUT_API void InitAfterTestFlow()	{		
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Fail site hardware set function will be called after failed params, it can be called for serveral times. 
DUT_API void SetupFailSite(const unsigned char*byFailSite)	{			
}

// test0, Continuity
// ******************************************************************* Continuity *******************************************************************
// ******************************************************************* Continuity *******************************************************************
// ******************************************************************* Continuity *******************************************************************
DUT_API int Continuity(short funcindex, LPCTSTR funclabel)	{
  //{{AFX_STS_PARAM_PROTOTYPES
  CParam *EN_GND = StsGetParam(funcindex,"EN_GND");
  CParam *VCC_GND = StsGetParam(funcindex,"VCC_GND");
  CParam *RT_GND = StsGetParam(funcindex,"RT_GND");
  CParam *FB_GND = StsGetParam(funcindex,"FB_GND");
  CParam *BST_GND = StsGetParam(funcindex,"BST_GND");
  CParam *SW_GND = StsGetParam(funcindex,"SW_GND");
  CParam *VIN_GND = StsGetParam(funcindex,"VIN_GND");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
 	pwr0v();
 	delay_ms(1);
	rlyC.SetOn(ViEN, ViVCC, ViRT, ViFB, ViBST, ViSW, ViVIN, -1);
 	delay_ms(2);
 	
 	// EN(#1)
 	EN_FOVI2.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	EN_FOVI2.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		EN_GND->SetTestResult(site, 0, EN_FOVI2.GetMeasResult(site, MVRET));
 	EN_FOVI2.Set(FV, 0.0f, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// VCC(#2)
 	VCC_FOVI10.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	VCC_FOVI10.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		VCC_GND->SetTestResult(site, 0, VCC_FOVI10.GetMeasResult(site, MVRET));
 	VCC_FOVI10.Set(FV, 0.0, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// RT(#3)
 	RT_FOVI6.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	RT_FOVI6.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		RT_GND->SetTestResult(site, 0, RT_FOVI6.GetMeasResult(site, MVRET));
 	RT_FOVI6.Set(FV, 0.0, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// FB(#4)
 	FB_FOVI8.Set(FI, -160.0e-6, FOVI_2V, FOVI_1MA, RELAY_ON);
 	delay_us(500);
 	FB_FOVI8.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		FB_GND->SetTestResult(site, 0, FB_FOVI8.GetMeasResult(site, MVRET));
 	FB_FOVI8.Set(FV, 0.0f, FOVI_2V, FOVI_1MA, RELAY_ON);
 	// BST(#5)
 	BST_FOVI7.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	BST_FOVI7.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		BST_GND->SetTestResult(site, 0, BST_FOVI7.GetMeasResult(site, MVRET));
 	BST_FOVI7.Set(FV, 0.0, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// SW(#6)
 	SW2_FPVI3.Set(FI, -1.0e-3, FPVI10_2V, FPVI10_10MA, RELAY_ON);
 	delay_us(500);
 	SW2_FPVI3.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		SW_GND->SetTestResult(site, 0, SW2_FPVI3.GetMeasResult(site, MVRET));
 	SW2_FPVI3.Set(FV, 0.0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
 	// VIN(#8)
 	VIN_FPVI0.Set(FI, -0.5e-3, FPVI10_2V, FPVI10_10MA, RELAY_ON);
 	delay_us(500);
 	VIN_FPVI0.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		VIN_GND->SetTestResult(site, 0, VIN_FPVI0.GetMeasResult(site, MVRET));
 	VIN_FPVI0.Set(FV, 0.0, FPVI10_2V, FPVI10_10MA, RELAY_ON);

 	pwr_off();
 	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}

// test1, RegulatorV
// ******************************************************************* RegulatorV *******************************************************************
// ******************************************************************* RegulatorV *******************************************************************
// ******************************************************************* RegulatorV *******************************************************************
DUT_API int RegulatorV(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *Vreg = StsGetParam(funcindex,"Vreg");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	double RegVCC[SITENUM] = { 0.0f };
	 
 	rlyC.SetOn(RT500K, CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, ViVCC, -1);
 	delay_ms(2);
	// VIN = 12v
	VIN_FPVI0.Set(FV, 12.0f, FPVI10_20V, FPVI10_10MA, RELAY_ON);
	delay_us(300);
	// VCC measurement, HIZ
 	VCC_FOVI10.Set(FI, -0.01e-6f, FOVI_10V, FOVI_10UA, RELAY_ON);
 	delay_us(300);
	// EN = 5v
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(300);
	// FB = 1.5v
 	FB_FOVI8.Set(FV, 1.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(300);
	
	VCC_FOVI10.MeasureVI(100, 5);
	for(site = 0; site < SITENUM; site++)	{
		RegVCC[site] = VCC_FOVI10.GetMeasResult(site, MVRET);
		Vreg->SetTestResult(site, 0, RegVCC[site]);
	}
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_20V, FPVI10_10MA, RELAY_ON);
	VCC_FOVI10.Set(FI, -0.0e-6f, FOVI_10V, FOVI_10UA, RELAY_ON);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
	VCC_FOVI10.Set(FI, -0.0e-6f, FOVI_10V, FOVI_10UA, RELAY_OFF);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);

 	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}
// test2, UVLO
// ******************************************************************* UVLO *******************************************************************
// ******************************************************************* UVLO *******************************************************************
// ******************************************************************* UVLO *******************************************************************
DUT_API int UVLO(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *UVLO_Rising = StsGetParam(funcindex,"UVLO_Rising");
  CParam *UVLO_Falling = StsGetParam(funcindex,"UVLO_Falling");
  CParam *UVLO_VHYS = StsGetParam(funcindex,"UVLO_VHYS");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	double UVLO_ON[SITENUM] = { 0.0f }, UVLO_OFF[SITENUM] = { 0.0f }, TMPV[SITENUM] = { 0.0f };
	double GNG = UVLO_Rising->GetConditionCurSelDouble("goPassFail");	// 0: ramp	1:P/F
	 
	FreshSiteFlagInit();
  rlyC.SetOn(RT500K, CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, ViVCC, -1);
 	delay_ms(2);
	// EN = 5v
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(300);
	// FB100 = 3.0v
 	FB100_FOVI9.Set(FV, 3.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(300);
	VCC_FOVI10.Set(FV, 3.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(300);
	
	// ************************************** UVLO ON **************************************
	// ************************************** UVLO ON **************************************
	// ************************************** UVLO ON **************************************
	// FB monitor
 	FB_FOVI8.Set(FI, -0.001e-6f, FOVI_5V, FOVI_10UA, RELAY_ON);
 	delay_ms(1);
	// *********************************** GONOGO, UVLO HIGH ***********************************
	if(GNG)	{
	}
	// *********************************** RAMPING, UVLO HIGH ***********************************
	else	{
		for(vj = 3.0f; vj  < 5.0f;)	{
			for(site = 0; site < SITENUM; site++)	{
				VCC_FOVI10.Set(FV, vj, FOVI_10V, FOVI_10MA, RELAY_ON);
 				delay_ms(1);
		
				FB_FOVI8.MeasureVI(10, 10);
				TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
				if(TMPV[site] > float(2.9))	{
					VCC_FOVI10.MeasureVI(10, 10);
					UVLO_ON[site] = VCC_FOVI10.GetMeasResult(site, MVRET);
					flag[site] = 1;
				}
				vj += float(20e-3);
			}
			if(flag[0] && flag[1])
				break;
		}
	}
	// ************************************** UVLO OFF **************************************
	// ************************************** UVLO OFF **************************************
	// ************************************** UVLO OFF **************************************
	FreshSiteFlagInit();
	// *********************************** GONOGO, UVLO OFF ***********************************
	if(GNG)	{
	}
	// *********************************** RAMPING, UVLO OFF ***********************************
	else	{
		for(vj = 4.3f; vj  > 3.6f;)	{
			for(site = 0; site < SITENUM; site++)	{
				VCC_FOVI10.Set(FV, vj, FOVI_10V, FOVI_10MA, RELAY_ON);
 				delay_ms(1);
		
				FB_FOVI8.MeasureVI(10, 10);
				TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
				if(TMPV[site] < float(0.5))	{
					VCC_FOVI10.MeasureVI(10, 10);
					UVLO_OFF[site] = VCC_FOVI10.GetMeasResult(site, MVRET);
					flag[site] = 1;
				}
				vj += float(-20e-3);
			}
			if(flag[0] && flag[1])
				break;
		}
	}

	for(site = 0; site < SITENUM; site++)	{
		if(DebugConsole)
			fprintf(stderr, "UVLO_ON:%3.4f\n", UVLO_ON[site]);
		UVLO_Rising	->SetTestResult(site, 0, UVLO_ON[site]);
		UVLO_Falling->SetTestResult(site, 0, UVLO_OFF[site]);
		UVLO_VHYS		->SetTestResult(site, 0, (UVLO_ON[site] - UVLO_OFF[site])*1e3);
	}
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
 	FB100_FOVI9.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	VCC_FOVI10.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	FB_FOVI8.Set(FI, 0.0e-6f, FOVI_5V, FOVI_10UA, RELAY_ON);
	delay_ms(1);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
 	FB100_FOVI9.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	VCC_FOVI10.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	FB_FOVI8.Set(FI, 0.0e-6f, FOVI_5V, FOVI_10UA, RELAY_OFF);

 	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}

// test3, SupplyCurrent
// ******************************************************************* SupplyCurrent *******************************************************************
// ******************************************************************* SupplyCurrent *******************************************************************
// ******************************************************************* SupplyCurrent *******************************************************************
DUT_API int SupplyCurrent(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *iCL_vcc = StsGetParam(funcindex,"iCL_vcc");
  CParam *Quiescent = StsGetParam(funcindex,"Quiescent");
  CParam *Shutdown = StsGetParam(funcindex,"Shutdown");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	double IVCC[SITENUM] = { 999.0f }, IQ[SITENUM] = { 999.0f }, ISD[SITENUM] = { 999.0f };
	double vvtemp[SITENUM]= { 0.0f};

	// ************************************** IQ **************************************
	// ************************************** IQ **************************************
	// ************************************** IQ **************************************
	// VCC
	VCC_FOVI10.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(2);
	VCC_FOVI10.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_OFF);
	delay_ms(2);

	// EN
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_ms(2);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_20V, FPVI10_100MA, RELAY_ON);
 	delay_ms(10);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_1MA, RELAY_OFF);
	delay_ms(2);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_20V, FPVI10_100MA, RELAY_OFF);
 	delay_ms(1);
	
	rlyC.SetOn(-1);
	delay_ms(1);
	rlyC.SetOn(CapVCC, CapBST, ViVIN, ViEN, ViFB, -1);
 	delay_ms(2);

	// VIN
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_1MA, RELAY_ON, 10);
 	delay_ms(2);
	// EN
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	// FB 1ST
	FB_FOVI8.Set(FV, 1.35f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_ms(1);

	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_1MA, RELAY_ON, 20);
	delay_ms(2);
	// FB 2NDs
	FB_FOVI8.Set(FV, 1.35f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	
	VIN_FPVI0.MeasureVI(20, 10);
	for(site = 0; site < SITENUM; site++)	{
		vvtemp[site] = VIN_FPVI0.GetMeasResult(site, MVRET);
		if(vvtemp[site] > float(23.8))	{
			VIN_FPVI0.MeasureVI(2000, 5);
			IQ[site] = VIN_FPVI0.GetMeasResult(site, MIRET);
			IQ[site] += float(20e-6);			// @.@"		offset!!!
		}
	}

	FreshSiteFlagInit();
	rlyC.SetOn(ViVCC, ViEN, ViVIN, CapVCC, CapVIN, CapBST, -1);
 	delay_ms(2);

	// VIN
 	VIN_FPVI0.Set(FV,  5.0f, FPVI10_20V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV,  8.0f, FPVI10_20V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 10.0f, FPVI10_20V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 11.0f, FPVI10_20V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 12.0f, FPVI10_20V, FPVI10_100MA, RELAY_ON);
 	delay_ms(1);
	// EN
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_100MA, RELAY_ON);

	// ************************************** IVCC **************************************
	// ************************************** IVCC **************************************
	// ************************************** IVCC **************************************
	// VCC
	VCC_FOVI10.Set(FV, 0.0f, FOVI_5V, FOVI_1A, RELAY_ON);
	delay_ms(10);
	VCC_FOVI10.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(20);

	VCC_FOVI10.MeasureVI(120, 5);
	for(site = 0; site < SITENUM; site++)
		IVCC[site] = VCC_FOVI10.GetMeasResult(site, MIRET);
	// ************************************** ISD **************************************
	// ************************************** ISD **************************************
	// ************************************** ISD **************************************
	rlyC.SetOn(CapVIN, ViEN, bridgeBST, ViSW, VIN2_SERV, -1);
 	delay_ms(2);
	
	// VIN = 48.0v
 	SW2_FPVI3.Set(FV, 24.0f, FPVI10_50V, FPVI10_1MA, RELAY_ON);
	VIN2_FOVI13.Set(FV, 24.0f, FOVI_50V, FOVI_1MA, RELAY_ON);
 	delay_ms(2);
	// EN
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(50);

	VIN2_FOVI13.MeasureVI(100, 10);
	for(site = 0; site < SITENUM; site++)
		ISD[site] = VIN2_FOVI13.GetMeasResult(site, MIRET);

	for(site = 0; site < SITENUM; site++)	{
		iCL_vcc->SetTestResult	(site, 0, IVCC[site]*-1e3);
		Quiescent->SetTestResult(site, 0, IQ[site]	*1e6);
		Shutdown->SetTestResult	(site, 0, ISD[site]	*1e6);
	}
 	SW2_FPVI3.Set(FV, 0.0f, FPVI10_50V, FPVI10_1MA, RELAY_ON);
	VIN2_FOVI13.Set(FV, 0.0f, FOVI_50V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	SW2_FPVI3.Set(FV, 0.0f, FPVI10_50V, FPVI10_1MA, RELAY_OFF);
	VIN2_FOVI13.Set(FV, 0.0f, FOVI_50V, FOVI_1MA, RELAY_OFF);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_OFF);

 	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}

// test4, FuncEN
// ******************************************************************* FunctionEN *******************************************************************
// ******************************************************************* FunctionEN *******************************************************************
// ******************************************************************* FunctionEN *******************************************************************
DUT_API int FuncEN(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *VENH = StsGetParam(funcindex,"VENH");
  CParam *VNEL = StsGetParam(funcindex,"VNEL");
  CParam *VENHYS = StsGetParam(funcindex,"VENHYS");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	double VEN_ON[SITENUM]	= { 0.0f }, VEN_OFF[SITENUM]		= { 0.0f }, VEN_HYS[SITENUM] = { 0.0f };
	double VC1[SITENUM]			= { 0.0f, 0.0f }, VC2[SITENUM]	= { 0.0f, 0.0f };
	double TMPV[SITENUM]		= { 0.0f };
	double GNG = VENH->GetConditionCurSelDouble("goPassFail");
	 
	FreshSiteFlagInit();
  float vv = 0.0f;
	// VCC & VinCap, FPVI-VIN, FOVI-EN, FOVI-FB
	rlyC.SetOn(CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, -1);
 	delay_ms(2);
	
	for(vv = 0.0f; vv <= 12.0f;)	{
		// VIN
 		VIN_FPVI0.Set(FV, vv, FPVI10_20V, FPVI10_10MA, RELAY_ON);
 		delay_us(300);
		vv += float(0.5);
	}
	// EN
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	// FB
	FB_FOVI8.Set(FV, 1.5f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	// ************************************** EN ON **************************************
	// ************************************** EN ON **************************************
	// ************************************** EN ON **************************************
	// FB = 3
 	FB100_FOVI9.Set(FV, 3.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_ms(1);
	// FB
 	FB_FOVI8.Set(FI, -0.1e-6f, FOVI_5V, FOVI_10UA, RELAY_ON);
 	delay_ms(1);
	// **************************** VEN_ON, GONOGO *****************************
	if(GNG)	{
	}
	// **************************** VEN_ON, RAMPING ****************************
	else	{
		for(vj = 0.8f; vj  < 1.5f;)	{
			for(site = 0; site < SITENUM; site++)	{
				EN_FOVI2.Set(FV, vj, FOVI_10V, FOVI_10MA, RELAY_ON);
 				delay_ms(1);
			
				FB_FOVI8.MeasureVI(10, 10);
				TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
				if(TMPV[site] > float(2.9))	{
					EN_FOVI2.MeasureVI(10, 10);
					VEN_ON[site] = EN_FOVI2.GetMeasResult(site, MVRET);
					flag[site] = 1;
				}
				vj += float(10e-3);
			}
			if(flag[0] && flag[1])
				break;
		}
	}
	// ************************************** EN OFF **************************************
	// ************************************** EN OFF **************************************
	// ************************************** EN OFF **************************************
	FreshSiteFlagInit();
	// **************************** VEN_OFF, GONOGO *****************************
	if(GNG)	{
	}
	// **************************** VEN_OFF, RAMPING ****************************
	else	{
		for(vj = 1.5f; vj  > 0.9f;)	{
			for(site = 0; site < SITENUM; site++)	{
				EN_FOVI2.Set(FV, vj, FOVI_10V, FOVI_10MA, RELAY_ON);
 				delay_us(300);
			
				FB_FOVI8.MeasureVI(10, 10);
				TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
				if(TMPV[site] < float(0.8))	{
					EN_FOVI2.MeasureVI(10, 10);
					VEN_OFF[site] = EN_FOVI2.GetMeasResult(site, MVRET);
					flag[site] = 1;
				}
				vj += float(-10e-3);
			}
			if(flag[0] && flag[1])
				break;
		}
	}
	for(site = 0; site < SITENUM; site++)	{
		VENH		->SetTestResult(site, 0, VEN_ON[site]);
		VNEL		->SetTestResult(site, 0, VEN_OFF[site]);
		VENHYS	->SetTestResult(site, 0, ((VEN_ON[site] - VEN_OFF[site])*1e3));
	}
	VIN_FPVI0.Set(FV, 0.0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	FB_FOVI8.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
 	FB100_FOVI9.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_ms(2);
	VIN_FPVI0.Set(FV, 0.0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
	FB_FOVI8.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
 	FB100_FOVI9.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_OFF);

 	rlyC.SetOn(-1);
 	delay_ms(1);

	return 0;
}
// test5, ReferenceVoltage
// ******************************************************************* ReferenceVoltage *******************************************************************
// ******************************************************************* ReferenceVoltage *******************************************************************
// ******************************************************************* ReferenceVoltage *******************************************************************
DUT_API int ReferenceVoltage(short funcindex, LPCTSTR funclabel)	{
  //{{AFX_STS_PARAM_PROTOTYPES
  CParam *VREF = StsGetParam(funcindex,"VREF");
  CParam *VBG = StsGetParam(funcindex,"VBG");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	double Vbg[SITENUM] = { 0.0f }, Vref[SITENUM] = { 0.0f };

	// EnterTM, Vin = 24v
	rlyC.SetOn(CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, BST2_SERV, bridgeBST, -1);
 	delay_ms(2);
	// VIN=24
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
 	delay_ms(2);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(2);

	// FB
 	FB_FOVI8.Set(FI, -0.01e-6f, FOVI_2V, FOVI_10UA, RELAY_ON);
 	delay_ms(1);
	// ************************************** VREF **************************************
	// ************************************** VREF **************************************
	// ************************************** VREF **************************************
	// EN = 0, test mode1 set EN high for VREF
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_1MA, RELAY_ON, 2);
	delay_ms(1);
	
	FB_FOVI8.MeasureVI(60, 10);
	for(site = 0; site < SITENUM; site++)
		Vref[site] = FB_FOVI8.GetMeasResult(site, MVRET);
	// ************************************** VBG **************************************
	// ************************************** VBG **************************************
	// ************************************** VBG **************************************
	// EN = 5, test mode1 set EN low for VBG
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_1MA, RELAY_ON, 2);
	delay_ms(1);
	FB_FOVI8.MeasureVI(60, 10);
	for(site = 0; site < SITENUM; site++)	{
		Vbg[site] = FB_FOVI8.GetMeasResult(site, MVRET);
		VBG->SetTestResult(site, 0, Vbg[site] + float(0));
		VREF->SetTestResult(site, 0, Vref[site] + float(0));
	}
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_OFF);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_OFF);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(2);

 	rlyC.SetOn(-1);
 	delay_ms(1);

	return 0;
}

// test6, CurrentFB
// ******************************************************************* CurrentFB *******************************************************************
// ******************************************************************* CurrentFB *******************************************************************
// ******************************************************************* CurrentFB *******************************************************************
DUT_API int CurrentFB(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *FBCurrent = StsGetParam(funcindex,"FBCurrent");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	// ************************************** IFB **************************************
	// ************************************** IFB **************************************
	// ************************************** IFB **************************************
	double Ifb[SITENUM] = { 0.0f };
  float vv = 0.0f;
	// VCC & VinCap, FPVI-VIN, FOVI-EN, FOVI-FB
	rlyC.SetOn(CapVCC, CapVIN, ViVIN, ViEN, ViFB, -1);
 	delay_ms(2);
	for(vv = 0.0f; vv <= 5.0f;)	{
		// VIN
 		VIN_FPVI0.Set(FV, vv, FPVI10_10V, FPVI10_10MA, RELAY_ON);
 		delay_us(300);
		vv += float(0.5);
	}
	// EN
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON, 3);
	delay_us(500);
	// FB
	FB_FOVI8.Set(FV, 1.5f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
  // FB
	FB_FOVI8.Set(FV, 1.5f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	FB_FOVI8.Set(FV, 1.5f, FOVI_5V, FOVI_100UA, RELAY_ON);
	delay_us(500);
	FB_FOVI8.Set(FV, 1.5f, FOVI_5V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	FB_FOVI8.Set(FV, 1.5f, FOVI_5V, FOVI_1UA, RELAY_ON, 5);
	delay_ms(10);

	FB_FOVI8.MeasureVI(500, 5);
	for(site = 0; site < SITENUM; site++)	{
		Ifb[site] = fabs(FB_FOVI8.GetMeasResult(site, MIRET));
		FBCurrent->SetTestResult(site, 0, Ifb[site]*1e9);
	}
 	VIN_FPVI0.Set(FV, 0.0f, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	FB_FOVI8.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	FB_FOVI8.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
 
	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}

// test7, HSide
// ******************************************************************* HSMOS *******************************************************************
// ******************************************************************* HSMOS *******************************************************************
// ******************************************************************* HSMOS *******************************************************************
DUT_API int HSide(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *RON_HS = StsGetParam(funcindex,"RON_HS");
  CParam *iPK = StsGetParam(funcindex,"iPK");
  CParam *HSLkg1 = StsGetParam(funcindex,"HSLkg1");
  CParam *HSLkg2 = StsGetParam(funcindex,"HSLkg2");
  //}}AFX_STS_PARAM_PROTOTYPES

  double VDS[SITENUM] = { 0.0f }, ILOADING = 100e-3f, RonHS[SITENUM] = { 0.0f };
  double IPK[SITENUM] = { 999.0f }, IPK0[SITENUM] = { 999.0f }, IPK1[SITENUM] = { 999.0f };
  double HSLKG1[SITENUM] = { 999.0f }, HSLKG2[SITENUM] = { 999.0f };
	double TMPV[SITENUM] = { 0.0f }, i = 0;
	double iii[SITENUM] = { 0.0f };
  // TODO: Add your function code here
	rlyC.SetOn(CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, ViSW, BST2_SERV, bridgeBST, -1);
 	delay_ms(2);
	// VIN=24
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_1A, RELAY_ON);
 	delay_ms(2);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
  // FB = OFF
 	FB_FOVI8.Set(FV, 0.01f, FOVI_5V, FOVI_10MA, RELAY_OFF);
 	delay_ms(3);

	// EN = 0.0V		// *************************************************** TM1, 1ST EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(3);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(3);
	// EN = 0.0V		// *************************************************** TM2, 2ND EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(3);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(3);

	// BST-SW = 5.0
	BST2_FOVI12.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(3);

	// EN = 0.0V		// *************************************************** TM3, 3RD EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(3);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(3);
	// EN = 0.0V		// *************************************************** TM4, 4TH EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(3);
	
	// VIN=24
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
 	delay_ms(3);

  // SW sink 500mA loading
	SW2_FPVI3.Set(FI,	-1*ILOADING, FPVI10_50V, FPVI10_1A, RELAY_ON);
  delay_ms(1);

  SW2_FPVI3.MeasureVI(100, 10);
	// SW 0mA
	SW2_FPVI3.Set(FI,	-1.0e-6f, FPVI10_50V, FPVI10_1A, RELAY_ON);
  delay_ms(1);
	// **************************************** HSRon ****************************************
	// **************************************** HSRon ****************************************
	// **************************************** HSRon ****************************************
  for(site = 0; site < SITENUM; site++) {
    VDS[site] = SW2_FPVI3.GetMeasResult(site, MVRET);
		VDS[site] = float(24) - VDS[site];
    RonHS[site] = VDS[site] / ILOADING*1e3;
  }
	// ********************************************** EN=5 IPK1 **********************************************
	// ********************************************** EN=5 IPK1 **********************************************
	// ********************************************** EN=5 IPK1 **********************************************
	// ************************************************************ IPK1
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);

	FreshSiteFlagInit();
	// SW source 50mA
	SW2_FPVI3.Set(FI,	-50.0e-3f, FPVI10_50V, FPVI10_1A, RELAY_ON);
  delay_ms(1);

	// FB = 5V/1MA
	FB_FOVI8.Set(FV, 5.0f, FOVI_10V, FOVI_1MA, RELAY_ON);
 	delay_ms(1);

	for(i = 0.1f; i < 2.0f;)	{	
		for(site = 0; site < SITENUM; site++)	{
			SW2_FPVI3.Set(FI,	-i, FPVI10_50V, FPVI10_10A, RELAY_ON);
			delay_us(500);
			FB_FOVI8.MeasureVI(20, 20);
			SW2_FPVI3.MeasureVI(20, 10);
			delay_us(500);

			TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
			iii[site] = SW2_FPVI3.GetMeasResult(site, MIRET);
			// High to Low(FB)
      if( (TMPV[site] < 0.2f)&&(flag[site] == 0)&&(-iii[site] >= (i-0.01)) )	{
				flag[site] = 1;
				IPK1[site] = i;
				FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_1MA, RELAY_ON);
				break;
			}
		}
		if(flag[0]&&flag[1])
			break;

		i += 10e-3f;
	}
	SW2_FPVI3.Set(FI,	-0.5f, FPVI10_50V, FPVI10_10A, RELAY_ON);
  delay_us(300);
	SW2_FPVI3.Set(FI,	-0.4f, FPVI10_50V, FPVI10_10A, RELAY_ON);
  delay_us(300);
	SW2_FPVI3.Set(FI,	-0.3f, FPVI10_50V, FPVI10_10A, RELAY_ON);
  delay_us(300);
	SW2_FPVI3.Set(FI,	-0.1f, FPVI10_50V, FPVI10_10A, RELAY_ON);
  delay_us(300);
	SW2_FPVI3.Set(FI,	-0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
  delay_us(1000);
	
	VIN_FPVI0.Set		(FV, 0.0f, FPVI10_50V,	FPVI10_10A, RELAY_ON);
	EN_FOVI2.Set		(FV, 0.0f, FOVI_5V,			FOVI_10MA,	RELAY_ON);
	FB_FOVI8.Set		(FV, 0.0f, FOVI_10V,		FOVI_1MA,		RELAY_ON);
	BST2_FOVI12.Set	(FV, 0.0f, FOVI_10V,		FOVI_10MA,	RELAY_ON);
	SW2_FPVI3.Set		(FI, 0.0f, FPVI10_50V,	FPVI10_10A, RELAY_ON);
 	delay_ms(1);
	VIN_FPVI0.Set		(FV, 0.0f, FPVI10_50V,	FPVI10_10A,	RELAY_OFF);
	EN_FOVI2.Set		(FV, 0.0f, FOVI_5V,			FOVI_10MA,	RELAY_OFF);
	FB_FOVI8.Set		(FV, 0.0f, FOVI_10V,		FOVI_1MA,		RELAY_OFF);
	BST2_FOVI12.Set	(FV, 0.0f, FOVI_10V,		FOVI_10MA,	RELAY_OFF);
	SW2_FPVI3.Set		(FI, 0.0f, FPVI10_50V,	FPVI10_10A, RELAY_OFF);
 	delay_ms(1);
	// ********************************************** EN=0 IPK0 **********************************************
	// ********************************************** EN=0 IPK0 **********************************************
	// ********************************************** EN=0 IPK0 **********************************************
	// ************************************************************ IPK0, no transition high to low of FB
	FreshSiteFlagInit();
	rlyC.SetOn(CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, ViSW, BST2_SERV, bridgeBST, -1);
 	delay_ms(2);
	// VIN=24
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
	delay_ms(2);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	// BST-SW = 5.0
	BST2_FOVI12.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	// FB = 0V
	FB_FOVI8.Set(FV, 0.63f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	FB_FOVI8.Set(FV, 0.63f, FOVI_5V, FOVI_10UA, RELAY_ON);
	delay_ms(1);
	// EN = 0.0V		// *************************************************** TM1, 1ST EDGE
	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	// EN = 0.0V		// *************************************************** TM2, 2ND EDGE
	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);

	// FB = OFF
	FB_FOVI8.Set(FV, 0.63f, FOVI_5V, FOVI_10UA, RELAY_OFF);
	delay_us(100);

	// EN = 0.0V		// *************************************************** TM3, 3RD EDGE
	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);

	// EN = 0.0V		// *************************************************** TM4, 4TH EDGE
	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);

	FreshSiteFlagInit();
	// SW source 100mA
	SW2_FPVI3.Set(FI, -100.0e-3f, FPVI10_50V, FPVI10_1A, RELAY_ON);
	delay_ms(1);

	// FB = 5V/1MA
	FB_FOVI8.Set(FV, 5.0f, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(1);

	for(i = -0.100f; i < 0.3f;)	{	
		for(site = 0; site < SITENUM; site++)	{
			SW2_FPVI3.Set(FI,	i, FPVI10_50V, FPVI10_10A, RELAY_ON);
			delay_us(500);
			FB_FOVI8.MeasureVI(20, 10);
			SW2_FPVI3.MeasureVI(20, 10);
			delay_us(500);
			// Low to High(FB)
			TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
			iii[site] = fabs(SW2_FPVI3.GetMeasResult(site, MIRET));
			if( (TMPV[site] > 4.0f)&&(flag[site] == 0)&&(iii[site] >= (fabs(i)-0.01)) )	{
				flag[site] = 1;
				IPK0[site] = i;
				break;
			}
		}
		if(flag[0]&&flag[1])
			break;

		i += 10e-3f;
	}
	SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
	delay_us(300);
	// **************************************** VIN=100, SW=GND LEAKAGE ****************************************
	// **************************************** VIN=100, SW=GND LEAKAGE ****************************************
	// **************************************** VIN=100, SW=GND LEAKAGE ****************************************
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_1MA, RELAY_ON);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
 	delay_ms(1);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_OFF);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_1MA, RELAY_OFF);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_OFF);
 	delay_ms(1);

	rlyC.SetOn(ViVIN, ViEN, ViSW, -1);
 	delay_ms(2);
	// EN = 0.0V
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// VIN=100, FPVI_PLUS
	VIN_FPVI0.Set(FV, 100.0f, FPVI10_100V, FPVI10_100UA, RELAY_ON);
 	delay_ms(2);
	// VIN=100, FPVI_PLUS
	VIN_FPVI0.Set(FV, 100.0f, FPVI10_100V, FPVI10_10MA, RELAY_ON, 2);
 	delay_ms(2);

	// SW=0, FPVI_PLUS
	SW2_FPVI3.Set(FV, 0.0f, FPVI10_100V, FPVI10_100UA, RELAY_ON);
 	delay_ms(20);

	VIN_FPVI0.MeasureVI(50, 10);
	for(site = 0; site < SITENUM; site++)	{
		TMPV[site] = VIN_FPVI0.GetMeasResult(site, MVRET);
		if(TMPV[site] > float(99))	{
			// SW
			SW2_FPVI3.MeasureVI(200, 5);
			HSLKG2[site] = SW2_FPVI3.GetMeasResult(site, MIRET);
			// VIN
			//VIN_FPVI0.MeasureVI(200, 5);
			//HSLKG2[site] = VIN_FPVI0.GetMeasResult(site, MIRET);
		}
	}
	// **************************************** VIN=28, SW=GND LEAKAGE ****************************************
	// **************************************** VIN=28, SW=GND LEAKAGE ****************************************
	// **************************************** VIN=28, SW=GND LEAKAGE ****************************************
	// VIN=100, FPVI_PLUS
	VIN_FPVI0.Set(FV, 28.0f, FPVI10_100V, FPVI10_100UA, RELAY_ON);
 	delay_ms(20);

	VIN_FPVI0.MeasureVI(50, 10);
	for(site = 0; site < SITENUM; site++)	{
		TMPV[site] = VIN_FPVI0.GetMeasResult(site, MVRET);
		if(TMPV[site] > float(27.5))	{
			SW2_FPVI3.MeasureVI(200, 5);
			HSLKG1[site] = SW2_FPVI3.GetMeasResult(site, MIRET);
		}
	}
  for(site = 0; site < SITENUM; site++) {
		RON_HS->SetTestResult(site, 0, RonHS[site]);
		IPK[site] = IPK0[site] + 2 * (IPK1[site] - IPK0[site] );
		iPK   ->SetTestResult(site, 0, IPK[site]);
    HSLkg1->SetTestResult(site, 0, fabs(HSLKG1[site]*1e6));
    HSLkg2->SetTestResult(site, 0, fabs(HSLKG2[site]*1e6));
  }
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
 	delay_ms(1);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_OFF);
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
	SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_OFF);
 	delay_ms(1);

	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}

// test8, LSide
// ******************************************************************* LSMOS *******************************************************************
// ******************************************************************* LSMOS *******************************************************************
// ******************************************************************* LSMOS *******************************************************************
DUT_API int LSide(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *RON_LS = StsGetParam(funcindex,"RON_LS");
  CParam *Valley = StsGetParam(funcindex,"Valley");
  CParam *IZero = StsGetParam(funcindex,"IZero");
  CParam *LSLkg = StsGetParam(funcindex,"LSLkg");
  //}}AFX_STS_PARAM_PROTOTYPES
  double VDS[SITENUM] = { 0.0f }, ILOADING = 500e-3f, lsron[SITENUM] = { 0.0f };
  double IVALLEY[SITENUM] = { 999.0f }, IZX[SITENUM] = { 999.0f };
  double LSLKG[SITENUM] = { 999.0f };
	double TMPV_SW[SITENUM] = { 0.0f }, TMPV_VIN[SITENUM] = { 0.0f };
	double TMPV[SITENUM] = { 0.0f }, i = 0;
	double iii[SITENUM] = { 0.0f };

  // TODO: Add your function code here
	rlyC.SetOn(RT500K, CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, ViSW, BST2_SERV, bridgeBST, -1);
 	delay_ms(2);
	// VIN=24
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_1A, RELAY_ON);
 	delay_ms(2);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// FB = 0V
 	FB_FOVI8.Set(FV, 0.63f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(1);

	// EN = 0.0V		// *************************************************** TM1, 1ST EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	// EN = 0.0V		// *************************************************** TM2, 2ND EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);	

	// BST-SW = 5.0
	BST2_FOVI12.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(1);

	// EN = 0.0V		// *************************************************** TM3, 3RD EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(100);

  // SW
	SW2_FPVI3.Set(FI,	-ILOADING, FPVI10_50V, FPVI10_1A, RELAY_ON);
  delay_ms(1);
  SW2_FPVI3.MeasureVI(100, 10);
	// **************************************** LSRon ****************************************
	// **************************************** LSRon ****************************************
	// **************************************** LSRon ****************************************
  for(site = 0; site < SITENUM; site++) {
    VDS[site] = SW2_FPVI3.GetMeasResult(site, MVRET);
    lsron[site] = VDS[site] / -ILOADING*1e3;
  }
  // SW 0mA LOADING
	SW2_FPVI3.Set(FI,	float(0), FPVI10_50V, FPVI10_1A, RELAY_ON);
  delay_ms(1);

	// **************************************** IVALLEY ****************************************
	// **************************************** IVALLEY ****************************************
	// **************************************** IVALLEY ****************************************
	FreshSiteFlagInit();
  // FB = 5V/10uA
	FB_FOVI8.Set(FV, 5.0f, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
  // VIN = 12V
	VIN_FPVI0.Set(FV,	float(12), FPVI10_50V, FPVI10_10A, RELAY_ON);
  delay_ms(1);
	// EN = 0
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_ms(1);

	for(i = 0.1f; i < 0.7f;)	{	
		SW2_FPVI3.Set(FI,	-i, FPVI10_50V, FPVI10_10A, RELAY_ON);
		delay_us(500);
		i += float(100e-3);
	}

	for(i = 0.7f; i < 2.2f;)	{	
		for(site = 0; site < SITENUM; site++)	{
			SW2_FPVI3.Set(FI,	-i, FPVI10_50V, FPVI10_10A, RELAY_ON);
			delay_us(500);
			FB_FOVI8.MeasureVI(10, 5);
			SW2_FPVI3.MeasureVI(10, 5);
			delay_us(500);

			TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
			iii[site] = SW2_FPVI3.GetMeasResult(site, MIRET);
	
			SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
			delay_us(300);

			if( (TMPV[site] < 0.35f)&&(flag[site] == 0)&&(-iii[site] >= (i-0.01)) )	{
				flag[site] = 1;
				IVALLEY[site] = i;
				SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
				delay_us(300);
				break;
			}
		}
		if(flag[0]&&flag[1])
			break;

		i += 10e-3f;
	}
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_1A, RELAY_ON);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	SW2_FPVI3.Set(FI,	0.0, FPVI10_50V, FPVI10_10A, RELAY_ON);
	delay_ms(2);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_1A, RELAY_OFF);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	SW2_FPVI3.Set(FI,	0.0, FPVI10_50V, FPVI10_10A, RELAY_OFF);
 	delay_ms(1);
	// **************************************** IZX ****************************************
	// **************************************** IZX ****************************************
	// **************************************** IZX ****************************************
	rlyC.SetOn(CapVCC, CapVIN, ViVIN, ViEN, ViFB, ViSW, BST2_SERV, bridgeBST, -1);
 	delay_ms(2);
	// VIN=24
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_1A, RELAY_ON);
 	delay_ms(2);
	// BST-SW = 5.0
	BST2_FOVI12.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// FB = 0V
 	FB_FOVI8.Set(FV, 0.65f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(1);

	// EN = 0.0V		// *************************************************** TM1, 1ST EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	// EN = 0.0V		// *************************************************** TM2, 2ND EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);	
	// EN = 0.0V		// *************************************************** TM3, 3RD EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_us(100);
	// EN = 5.0V
	EN_FOVI2.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);

	FreshSiteFlagInit();
  // FB = 5V/10uA
	FB_FOVI8.Set(FV, 5.0f, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	// EN = 0
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	// SW
	SW2_FPVI3.Set(FI,	float(-0.12), FPVI10_50V, FPVI10_1A, RELAY_ON);
  delay_ms(1);

	for (i = -0.12f; i < 0.12f;)	{
		for (site = 0; site < SITENUM; site++)	{
			SW2_FPVI3.Set(FI, i, FPVI10_50V, FPVI10_1A, RELAY_ON);
			delay_us(500);
			FB_FOVI8.MeasureVI(10, 10);
			SW2_FPVI3.MeasureVI(10, 10);
			delay_us(500);

			TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
			iii[site] = fabs(SW2_FPVI3.GetMeasResult(site, MIRET));
			if ((TMPV[site] > 4.0) && (flag[site] == 0) && (iii[site] >= (i - 0.01)))	{
				flag[site] = 1;
				IZX[site] = i;
				break;
			}
		}
		if (flag[0] && flag[1])
			break;

		i += 2e-3f;
	}
	SW2_FPVI3.Set(FI,	0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
	delay_us(300);
  // VIN, EN, FB, SW=0A, BST-SW=5
	// **************************************** VIN=100, SW=100 LEAKAGE ****************************************
	// **************************************** VIN=100, SW=100 LEAKAGE ****************************************
	// **************************************** VIN=100, SW=100 LEAKAGE ****************************************
	pwr0v();
	pwr_off();
	delay_ms(2);

	double kkk = 0.0f;
	
	rlyC.SetOn(CapVIN, CapVCC, ViVIN, ViEN, ViSW, -1);
 	delay_ms(2);

	// VIN=100, FPVI_PLUS
	for(kkk = 0.0f; kkk <= 100.0f;)	{
		VIN_FPVI0.Set(FV, kkk, FPVI10_100V, FPVI10_10MA, RELAY_ON, 2);
		SW2_FPVI3.Set(FV, kkk, FPVI10_100V, FPVI10_10MA, RELAY_ON, 2);
		kkk += 5.0f;
	}
	VIN_FPVI0.Set(FV, 100.0f, FPVI10_100V, FPVI10_10MA, RELAY_ON);
	////VIN_FPVI0.Set(FV, 40.0f, FPVI10_100V, FPVI10_10MA, RELAY_ON);
	// EN = 0.0V
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100UA, RELAY_ON);
	delay_ms(5);
	// SW=100, FPVI_PLUS
	SW2_FPVI3.Set(FV, 100.0f, FPVI10_100V, FPVI10_10MA, RELAY_ON);
	////SW2_FPVI3.Set(FV, 40.0f, FPVI10_100V, FPVI10_10MA, RELAY_ON);
	
	// EN = 0.0V
	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100UA, RELAY_SENSE_ON);		// =.="			"Orz...87 oh ~.~"
	delay_ms(5);
	//for (volatile short x = 0; x < 2000; x++)	// do something but do nothing, fake NOP

	for(site = 0; site < SITENUM; site++)	{
		VIN_FPVI0.MeasureVI(10, 5);
		TMPV_VIN[site] = VIN_FPVI0.GetMeasResult(site, MVRET);
		SW2_FPVI3.MeasureVI(10, 5);
		TMPV_SW[site] = SW2_FPVI3.GetMeasResult(site, MVRET);
		
		if( (TMPV_SW[site] > float(99))&&(TMPV_VIN[site] > float(99)) )	{
		////if( (TMPV_SW[site] > float(39))&&(TMPV_VIN[site] > float(39)) )	{
			SW2_FPVI3.MeasureVI(500, 1);
			LSLKG[site] = SW2_FPVI3.GetMeasResult(site, MIRET);
			delay_us(1);
		}
	}
  for(site = 0; site < SITENUM; site++) {
		RON_LS->SetTestResult(site, 0, lsron[site]);
		IZero ->SetTestResult(site, 0, IZX[site]*1e3);
		Valley->SetTestResult(site, 0, IVALLEY[site]);
    LSLkg ->SetTestResult(site, 0, fabs(LSLKG[site]*1e6));
  }
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_1A, RELAY_ON);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	SW2_FPVI3.Set(FI,	0.0, FPVI10_50V, FPVI10_10A, RELAY_ON);
	delay_ms(2);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_1A, RELAY_OFF);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	SW2_FPVI3.Set(FI,	0.0, FPVI10_50V, FPVI10_10A, RELAY_OFF);
 	delay_ms(1);

	rlyC.SetOn(-1);
 	delay_ms(1);
 
  return 0;
}
		
// test9, Switching
// ******************************************************************* Switching *******************************************************************
// ******************************************************************* Switching *******************************************************************
// ******************************************************************* Switching *******************************************************************
DUT_API int Switching(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *Freq = StsGetParam(funcindex,"Freq");
  CParam *ON = StsGetParam(funcindex,"ON");
  CParam *OFF = StsGetParam(funcindex,"OFF");
  //}}AFX_STS_PARAM_PROTOTYPES

  double FREQ[SITENUM] = { 0.0f };
  double TON[SITENUM] = { 0.0f }, TOFF[SITENUM] = { 0.0f };
  // TODO: Add your function code here
	// ********************************* TestModeSettingSequenceStart *********************************
	// ********************************* TestModeSettingSequenceStart *********************************
	// ********************************* TestModeSettingSequenceStart *********************************
	// EnterTM, Vin = 24.0v
	// ResRT, VCC & VinCap, FPVI-VIN, FOVI-EN, FOVI-FB
	rlyC.SetOn(RT500K, CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, ViSW, BST2_SERV, bridgeBST, -1);
 	delay_ms(2);
	// VIN RAMP UP TO SETTING VALUE
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
 	delay_us(300);
	// EN = 5.0V, System startup
 	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_us(100);
	// BST-SW = 5.0V
	BST2_FOVI12.Set(FV, 5.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(1);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// ***************** TM1 *****************
	// ***************** TM1 *****************
	// EN = 0.0V, 1ST EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_us(100);

	// ***************** FB released for FREQ in TM *****************
	// ***************** FB released for FREQ in TM *****************
	// FB = floating
	FB_FOVI8.Set(FV, 0.63f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(1);
	
	// ***************** TM2 *****************
	// ***************** TM2 *****************
	// EN = 5.0V
 	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_us(100);
 	// EN = 0.0V, 2ND EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_us(100);
	
	rlyC.SetOn(RT500K, CapVCC, CapVIN, CapBST, VIN1KSW, ViVIN, ViEN, ViSW, ViFB, BST2_SERV, bridgeBST, qtmuFB, qtmuSWAP, -1);
 	delay_ms(2);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// ***************** FREQ measurement setting VEN=High *****************
	// EN = 5.0v for Frequency test
 	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_1MA, RELAY_ON);
 	delay_ms(1);
	// ********************************* TestModeSettingSequenceEnd *********************************
	// ********************************* TestModeSettingSequenceEnd *********************************
	// ********************************* TestModeSettingSequenceEnd *********************************
	// **************************************** FREQ ****************************************
	qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_10MHz);
	qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_10MHz);
	qtmu0.SetStartTrigger(2.5f, QTMU_PLUS_POS_SLOPE);
	qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE);
	qtmu0.Connect();
	delay_ms(1);
	
	qtmu0.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US);
  for(site = 0; site < SITENUM; site++)
		FREQ[site] = qtmu0.GetMeasureResult(site);
	// **************************************** ON TIME ****************************************
	qtmu0.SetStartTrigger(1.8f, QTMU_PLUS_POS_SLOPE);	
	qtmu0.SetStopTrigger(1.6f, QTMU_PLUS_NEG_SLOPE);	
	delay_ms(1);
	qtmu0.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US);
  for(site = 0; site < SITENUM; site++)
		TON[site] = qtmu0.GetMeasureResult(site);
	// **************************************** OFF TIME ****************************************
	qtmu0.SetStartTrigger(1.8f, QTMU_PLUS_NEG_SLOPE);	
	qtmu0.SetStopTrigger(2.5f, QTMU_PLUS_POS_SLOPE);	
	delay_ms(1);
	qtmu0.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US);
  for(site = 0; site < SITENUM; site++)
		TOFF[site] = qtmu0.GetMeasureResult(site);
	// **************************************** LOG ***************************************
	for(site = 0; site < SITENUM; site++) {
		//Freq  ->SetTestResult(site, 0, FREQ[site]);     // Khz
		Freq  ->SetTestResult(site, 0, 1000.0f/(TON[site] + TOFF[site] + 1e-15f));     // Khz
    ON    ->SetTestResult(site, 0, TON[site]);			// usec
    OFF   ->SetTestResult(site, 0, TOFF[site]);			// usec
  }
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_ON);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(1);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_10A, RELAY_OFF);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_OFF);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);

  return 0;
}

// test10, BOOST
// ******************************************************************* BOOST *******************************************************************
// ******************************************************************* BOOST *******************************************************************
// ******************************************************************* BOOST *******************************************************************
DUT_API int BOOST(short funcindex, LPCTSTR funclabel)	{
	//{{AFX_STS_PARAM_PROTOTYPES
  CParam *BSTOK_H = StsGetParam(funcindex,"BSTOK_H");
  CParam *BSTOK_L = StsGetParam(funcindex,"BSTOK_L");
  CParam *BSTOK_HYS = StsGetParam(funcindex,"BSTOK_HYS");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	double TMPV[SITENUM] = { 0.0f }, i = 0.0f, step_v = 10e-3f;
  double BSTOK_ON[SITENUM] = { 0.f }, BSTOK_OFF[SITENUM] = { 0.0f }, BSTOK_HYSV[SITENUM] = { 0.0f };
	double GNG = BSTOK_H->GetConditionCurSelDouble("goPassFail");	// 0: ramp	1:P/F
	
	FreshSiteFlagInit();
	rlyC.SetOn(CapVCC, CapVIN, CapBST, ViVIN, ViEN, ViFB, ViSW, BST2_SERV, bridgeBST, -1);
 	delay_ms(2);
	// VIN = 5V
	VIN_FPVI0.Set(FV, 5.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
 	delay_us(300);
	// FB = 6.5V
	FB_FOVI8.Set(FV, 6.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	// ************************************************************************************************************
	// EN = 5.0V
 	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_10MA, RELAY_ON, 5);
 	delay_us(100);
	// EN = 0.0V, 1ST FALLING EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_us(100);
	// ****************************************************************************************
	// ****************************************************************************************
	// FB = 0V/off
 	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF, 5);
 	delay_us(100);
	// ****************************************************************************************
	// ****************************************************************************************
	// EN = 5.0V
 	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_10MA, RELAY_ON, 5);
 	delay_us(100);
	// EN = 0.0V, 2ND FALLING EDGE
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
 	delay_us(100);
	// ************************************************************************************************************
	// ************************************** BSTOK_HIGH **************************************
	// ************************************** BSTOK_HIGH **************************************
	// ************************************** BSTOK_HIGH **************************************
	// BST (BST-SW Vdiff = 1.5 to 3.5, real 4.5v - 6.5v)
	BST2_FOVI12.Set(FV, 1.5f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(1);

	// VIN = 24v
 	VIN_FPVI0.Set(FV, 8.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 12.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 16.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 20.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 22.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
 	delay_us(500);
	// SW = 3V/100mA
	SW2_FPVI3.Set(FV, 3.0f, FPVI10_10V, FPVI10_100MA, RELAY_ON);
 	delay_ms(1);
	// FB = 5.0V/10uA
 	FB_FOVI8.Set(FV, 5.0f, FOVI_10V, FOVI_10UA, RELAY_ON);
 	delay_ms(1);

	// ********************************* BSTOK_ON, GONOGO *********************************
	if(GNG)	{
	}
	// ********************************* BSTOK_ON, RAMPING *********************************
	else	{
		for(site = 0; site < SITENUM; site++)	{
			for(i = 1.5f; i <= 3.5f;)	{
				// BST (BST-SW Vdiff = 1.5 to 3.5, real 4.5v - 6.5v)
				BST2_FOVI12.Set(FV, i, FOVI_10V, FOVI_10MA, RELAY_ON);
				delay_us(300);
				FB_FOVI8.MeasureVI(10, 5);
				delay_us(300);
				TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
				if(TMPV[site] > float(4.8))	{
					flag[site] = 1;
					BST2_FOVI12.MeasureVI(10, 5);
					BSTOK_ON[site] = BST2_FOVI12.GetMeasResult(site, MVRET);
				}
				i += step_v;
				if(flag[0] && flag[1])
					break;
			}
		}
	}
	// ************************************** BSTOK_LOW **************************************
	// ************************************** BSTOK_LOW **************************************
	// ************************************** BSTOK_LOW **************************************
	FreshSiteFlagInit();
	// ********************************* BSTOK_OFF, GONOGO *********************************
	if(GNG)	{
	}
	// ********************************* BSTOK_OFF, RAMPING *********************************
	else	{
		for(site = 0; site < SITENUM; site++)	{
			for(i = 3.5f; i >= 1.5f;)	{
				BST2_FOVI12.Set(FV, i, FOVI_10V, FOVI_10MA, RELAY_ON);
 				delay_us(300);
				FB_FOVI8.MeasureVI(20, 10);
				TMPV[site] = FB_FOVI8.GetMeasResult(site, MVRET);
				if(TMPV[site] < float(0.3))	{
					flag[site] = 1;
					BST2_FOVI12.MeasureVI(20, 10);
					BSTOK_OFF[site] = BST2_FOVI12.GetMeasResult(site, MVRET);
				}
				i += -step_v;
				if(flag[0] && flag[1])
					break;
			}
		}
	}
  for(site = 0; site < SITENUM; site++) {
		BSTOK_HYSV[site] = BSTOK_ON[site] - BSTOK_OFF[site];
		BSTOK_H     ->SetTestResult(site, 0, BSTOK_ON[site]);
    BSTOK_L     ->SetTestResult(site, 0, BSTOK_OFF[site]);
    BSTOK_HYS   ->SetTestResult(site, 0, BSTOK_HYSV[site]*1e3);
  }
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_100MA, RELAY_ON);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_ON);
 	delay_ms(2);
	VIN_FPVI0.Set(FV, 0.0f, FPVI10_50V, FPVI10_100MA, RELAY_OFF);
	FB_FOVI8.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
 	EN_FOVI2.Set(FV, 0.0f, FOVI_5V, FOVI_10MA, RELAY_OFF);
	BST2_FOVI12.Set(FV, 0.0f, FOVI_10V, FOVI_10MA, RELAY_OFF);
	
 	rlyC.SetOn(-1);
 	delay_ms(1);

	return 0;
}
// test11, PPTrim
DUT_API int PPTrim(short funcindex, LPCTSTR funclabel)  {
  //{{AFX_STS_PARAM_PROTOTYPES
  CParam *TB1 = StsGetParam(funcindex,"TB1");
  CParam *TB2 = StsGetParam(funcindex,"TB2");
  CParam *TB3 = StsGetParam(funcindex,"TB3");
  CParam *TB4 = StsGetParam(funcindex,"TB4");
  CParam *TB5 = StsGetParam(funcindex,"TB5");
  CParam *TB6 = StsGetParam(funcindex,"TB6");
  CParam *TB7 = StsGetParam(funcindex,"TB7");
  CParam *TB8 = StsGetParam(funcindex,"TB8");
  CParam *TB9 = StsGetParam(funcindex,"TB9");
  CParam *TB10 = StsGetParam(funcindex,"TB10");
  CParam *TB11 = StsGetParam(funcindex,"TB11");
  CParam *TB12 = StsGetParam(funcindex,"TB12");
  CParam *TB13 = StsGetParam(funcindex,"TB13");
  CParam *TB14 = StsGetParam(funcindex,"TB14");
  CParam *TB15 = StsGetParam(funcindex,"TB15");
  CParam *TB16 = StsGetParam(funcindex,"TB16");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
  FreshSiteFlagInit();

  rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}
// test12, pContinuity
// ******************************************************************* postContinuity *******************************************************************
// ******************************************************************* postContinuity *******************************************************************
// ******************************************************************* postContinuity *******************************************************************
DUT_API int pContinuity(short funcindex, LPCTSTR funclabel)	{
  //{{AFX_STS_PARAM_PROTOTYPES
  CParam *EN_GND = StsGetParam(funcindex,"EN_GND");
  CParam *VCC_GND = StsGetParam(funcindex,"VCC_GND");
  CParam *RT_GND = StsGetParam(funcindex,"RT_GND");
  CParam *FB_GND = StsGetParam(funcindex,"FB_GND");
  CParam *BST_GND = StsGetParam(funcindex,"BST_GND");
  CParam *SW_GND = StsGetParam(funcindex,"SW_GND");
  CParam *VIN_GND = StsGetParam(funcindex,"VIN_GND");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	pwr0v();
 	delay_ms(1);
 	rlyC.SetOn(ViEN, ViVCC, ViRT, ViFB, ViBST, ViSW, ViVIN, -1);
 	delay_ms(2);
 	// EN(#1)
 	EN_FOVI2.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	EN_FOVI2.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		EN_GND->SetTestResult(site, 0, EN_FOVI2.GetMeasResult(site, MVRET));
 	EN_FOVI2.Set(FV, 0.0f, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// VCC(#2)
 	VCC_FOVI10.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	VCC_FOVI10.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		VCC_GND->SetTestResult(site, 0, VCC_FOVI10.GetMeasResult(site, MVRET));
 	VCC_FOVI10.Set(FV, 0.0, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// RT(#3)
 	RT_FOVI6.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	RT_FOVI6.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		RT_GND->SetTestResult(site, 0, RT_FOVI6.GetMeasResult(site, MVRET));
 	RT_FOVI6.Set(FV, 0.0, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// FB(#4)
 	FB_FOVI8.Set(FI, -160.0e-6, FOVI_2V, FOVI_1MA, RELAY_ON);
 	delay_us(500);
 	FB_FOVI8.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		FB_GND->SetTestResult(site, 0, FB_FOVI8.GetMeasResult(site, MVRET));
 	FB_FOVI8.Set(FV, 0.0f, FOVI_2V, FOVI_1MA, RELAY_ON);
 	// BST(#5)
 	BST_FOVI7.Set(FI, -1.0e-3, FOVI_2V, FOVI_10MA, RELAY_ON);
 	delay_us(500);
 	BST_FOVI7.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		BST_GND->SetTestResult(site, 0, BST_FOVI7.GetMeasResult(site, MVRET));
 	BST_FOVI7.Set(FV, 0.0, FOVI_2V, FOVI_10MA, RELAY_ON);
 	// SW(#6)
 	SW2_FPVI3.Set(FI, -1.0e-3, FPVI10_2V, FPVI10_10MA, RELAY_ON);
 	delay_us(500);
 	SW2_FPVI3.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		SW_GND->SetTestResult(site, 0, SW2_FPVI3.GetMeasResult(site, MVRET));
 	SW2_FPVI3.Set(FV, 0.0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
 	// VIN(#8)
 	VIN_FPVI0.Set(FI, -0.5e-3, FPVI10_2V, FPVI10_10MA, RELAY_ON);
 	delay_us(500);
 	VIN_FPVI0.MeasureVI(10, 10);
 	for (site = 0; site < SITENUM; site++)
 		VIN_GND->SetTestResult(site, 0, VIN_FPVI0.GetMeasResult(site, MVRET));
 	VIN_FPVI0.Set(FV, 0.0, FPVI10_2V, FPVI10_10MA, RELAY_ON);

 	pwr_off();
 	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}

DUT_API int FuncEN2(short funcindex, LPCTSTR funclabel)	{
  //{{AFX_STS_PARAM_PROTOTYPES
  CParam *IEN1 = StsGetParam(funcindex,"IEN1");
  CParam *IEN2 = StsGetParam(funcindex,"IEN2");
  //}}AFX_STS_PARAM_PROTOTYPES

  // TODO: Add your function code here
	double IENUP1[SITENUM]	= { 0.0f }, IENUP2[SITENUM]			= { 0.0f };
  double vv = 0.0f, VC1[SITENUM]=  { 0.0f }, VC2[SITENUM] = { 0.0f };
	double freqq[SITENUM] = { 0.0f };
	 
	FreshSiteFlagInit();
	// ************************************** IENUP1(VEN=1V) **************************************
	// ************************************** IENUP1(VEN=1V) **************************************
	// ************************************** IENUP1(VEN=1V) **************************************
	rlyC.SetOn(CapVCC, CapVIN, ViVIN, ViEN, -1);
 	delay_ms(2);
	// VIN = 24
	VIN_FPVI0.Set(FV, 24.0f, FPVI10_50V, FPVI10_10MA, RELAY_ON);
	EN_FOVI2.Set(FV, 5.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	// EN = 1
	EN_FOVI2.Set(FV, 1.0f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	// EN = 1
	EN_FOVI2.Set(FV, 1.0f, FOVI_5V, FOVI_10UA, RELAY_ON);
	delay_ms(2);

	EN_FOVI2.MeasureVI(100, 10);
	for(site = 0; site < SITENUM; site++)
		IENUP1[site] = fabs(EN_FOVI2.GetMeasResult(site, MIRET));
	// ************************************** IENUP2(VEN=1.23V) **************************************
	// ************************************** IENUP2(VEN=1.23V) **************************************
	// ************************************** IENUP2(VEN=1.23V) **************************************
	pwr0v();
	pwr_off();
 	rlyC.SetOn(-1);
 	delay_ms(1);

	rlyC.SetOn(CapVCC, CapVIN, CapBST, SW10KGND, ViVIN, -1);
 	delay_ms(2);
	
	for(vv = 0.0f; vv <= 12.0f;)	{
		// VIN
 		VIN_FPVI0.Set(FV, vv, FPVI10_20V, FPVI10_100MA, RELAY_ON);
 		delay_us(5);
		vv += float(1.0);
	}

  // EN = 2.8
	EN_FOVI2.Set(FV, 2.8f, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStartTrigger(4.0f, QTMU_PLUS_POS_SLOPE);
	qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE);
	qtmu0.Connect();
	delay_ms(1);
	
	FreshSiteFlagInit();
  // Switching to Low
 	for(vj = 1.2f; vj  > 0.1f;)	{
		for(site = 0; site < SITENUM; site++)	{
			if(flag[site]==0)	{
				EN_FOVI2.Set(FV, vj, FOVI_2V, FOVI_10MA, RELAY_ON);
				qtmu0.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US);
				freqq[site] = qtmu0.GetMeasureResult(site);
 			
				if(freqq[site] == float(0))	{
					EN_FOVI2.MeasureVI(10, 10);
					VC1[site] = EN_FOVI2.GetMeasResult(site, MVRET);
					flag[site] = 1;
				}
			}
		}
		vj += float(-0.2);
		if(flag[0] && flag[1])
			break;
	}

  // Low to Switching
  FreshSiteFlagInit();
 	for(vj = 0.5; vj  < 1.5f;)	{
		for(site = 0; site < SITENUM; site++)	{
			if(flag[site] ==0)	{
				EN_FOVI2.Set(FV, vj, FOVI_2V, FOVI_10MA, RELAY_ON);
				qtmu0.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US);
				freqq[site] = qtmu0.GetMeasureResult(site);

				if(freqq[site] != float(0))	{
					EN_FOVI2.MeasureVI(10, 10);
					VC2[site] = EN_FOVI2.GetMeasResult(site, MVRET);
					flag[site] = 1;
				}
			}
		}
		vj += float(0.2);
		if(flag[0] && flag[1])
			break;
	}
  for(site = 0; site < SITENUM; site++) {
    IENUP2[site] = (VC2[site] - VC1[site])/40*1e3;    // uA
    IEN1->SetTestResult(site, 0, IENUP1[site]*1e6);
    IEN2->SetTestResult(site, 0, IENUP2[site]);
  }
	pwr0v();
	pwr_off();
 	rlyC.SetOn(-1);
 	delay_ms(1);

  return 0;
}