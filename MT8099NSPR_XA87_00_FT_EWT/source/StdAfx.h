// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3811CD50_B7B0_42B9_9E73_805A91708537__INCLUDED_)
#define AFX_STDAFX_H__3811CD50_B7B0_42B9_9E73_805A91708537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#define DUT_API extern "C" __declspec(dllexport)
#include <string>
using namespace std;
#include "usertype.h"
#include "userres.h"

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3811CD50_B7B0_42B9_9E73_805A91708537__INCLUDED_)

// TEST FLOW ***********************************************
// test0 : Continuity
// test1 : RegulatorV
// test2 : UVLO
// test3 : SupplyCurrent
// test4 : FunctionEN
// test5 : ReferenceVoltage
// test6 : CurrentFB
// test7 : HSMOS
// test8 : LSMOS
// test9 : Switching
// test10: BOOST
// test11: PPTrim
// test12: postContinuity
// ******************************************************************* PIN DESCTIPTION ST *******************************************************************
// PACKAGE TYPE: SOP8L w/EP
// PIN01:	EN  (Non-K)
// PIN02:	VCC
// PIN03:	RT  (Non-K)
// PIN04:	FB
// PIN05:	BST (Non-K)
// PIN06:	SW
// PIN07:	GND
// PIN08:	VIN
// ******************************************************************* PIN DESCTIPTION END *******************************************************************
// ******************************************************************* RELAY CONTROL ******************************************************************
// IDC1, SITE1, SITE2
// CAP
#define CapVCC					  0, 64		// K1	, VCC (#2) connect 1uF to GND
#define CapVIN	  		    1, 65   // K2	, VIN (#8) connect 0.1uF to GND
#define VIN1KSW 	  		  3, 67		// K4 , SW-1K-VIN   
#define SW10KGND 	  			4, 68   // K5 , SW-10K-GND
#define FB100					    8, 72   // K9	, FB  (#4) series 100K to FOVI9
#define RT500K						9, 73   // K10, RT  (#3) series 500K to GND
#define ViRT					   10, 74   // K11,	RT  (#3) FOVI6
#define ViVIN		         11, 75   // K12, VIN (#8) FPVI0
#define ViVCC				     12, 76   // K13, VCC (#2) FOVI10
#define ViEN					   13, 77   // K14, normal close: FOVI2-40K-EN(#1)
                                  //      normal open : FOVI2-EN(#1)
#define ViFB		         14, 78		// K15, FOVI8-FB  (#4)
#define ViBST			       15, 79		// K16, FOVI7-BST (#5)
// IDC2
// BST voltage boost(FPVI3+FOVI12)
#define bridgeBST				 35, 99   // K20, SW(#6) series FOVI12
#define ViSW					   36,100	  // K21, FPVI3-SW  (#6)
#define BST2_SERV			   33, 97   // K18, FOVI12-BST(#5)
// VIN voltage boost(FPVI1+FOVI13)
#define CapBST           41,105		// K26, SW-BST 0.1uF
#define VIN2_SERV        42,106		// K27, FOVI13-VIN(#8)
// Timing relay setting
#define qtmuFB					 45,109   // K30, FB(#4) connect QTMU_CH0B
#define REN40K		       46,110   // K31, EN(#1) series 40K to GND
#define qtmuSWAP				 47,111	  // K32, QTMU_CH0A swap QTMU_CH0B

// ****************************************************************************** S1
#define VccCapS1  						0
#define VinCapS1  						1
#define Vin1KSWS1  						3

#define oviFB100S1					  8
#define RT500S1 							9
#define oviRTS1 						 10
#define pviVinS1						 11
#define oviVccS1						 12
#define oviENS1						   13
                               
#define oviFBS1			         14
#define oviBstS1						 15
// IDC2
#define bridgeBstS1				   35
#define pviSW_S1						 36
#define serBstS1						 33

#define bridgeVinS1			     34
#define pviSWS1					     38
#define oviVinS1  		       42
// Timing relay setting
#define qtmuFBS1						 45
#define REN40S1						   46
#define qtmuSwapS1					 47
// ****************************************************************************** S2
#define VccCapS2					   64
#define VinCapS2  					 65
#define Vin1KSWS2  					 67

#define oviFB100S2			  	 72
#define RT500S2 						 73
#define oviRTS2 						 74
#define pviVinS2		         75
#define oviVccS2					   76
#define oviENS2							 77
                             
#define oviFBS2			         78
#define oviBstS2						 79
// IDC2
#define bridgeBstS2					 99
#define pviSW_S2						 100
#define serBstS2					   97

#define bridgeVinS2				   98
#define pviSWS2							 102
#define oviVinS2  		       106
// Timing relay setting
#define qtmuFBS2					   109
#define REN40S2		           110
#define qtmuSwapS2				   111
/*
// VBG accuracy
int  TBit1[SITENUM]  = { 0, 0 };    // 4.5mv
int  TBit2[SITENUM]  = { 0, 0 };    // -9.0mv
int  TBit3[SITENUM]  = { 0, 0 };    // -8.0mv
int  TBit4[SITENUM]  = { 0, 0 };    // 36.0mv
// IPK1, IPK2
int  TBit5[SITENUM]  = { 0, 0 };    // +10%
int  TBit6[SITENUM]  = { 0, 0 };    // -10%
// IQ
int  TBit7[SITENUM]  = { 0, 0 };    // -5uA
// IValley1
int  TBit8[SITENUM]  = { 0, 0 };    // +10%
// TBTADD
int  TBit9[SITENUM]  = { 0, 0 };    // CLKH
int  TBit10[SITENUM] = { 0, 0 };    // FPWM
int  TBit11[SITENUM] = { 0, 0 };    
int  TBit12[SITENUM] = { 0, 0 };    
int  TBit13[SITENUM] = { 0, 0 };    
int  TBit14[SITENUM] = { 0, 0 };    // EA BIAS current +2uA
int  TBit15[SITENUM] = { 0, 0 };
*/
