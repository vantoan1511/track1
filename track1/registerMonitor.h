/*
 * registerMonitor.h
 *
 *  Created on: May 18, 2023
 *      Author: gogoCow
 */

#ifndef REGISTERMONITOR_H
#define REGISTERMONITOR_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "resetRegister.h"
extern int baseAddr;
extern int regBufferRx[255];
extern int regBufferTx[255];
extern int regStatus;
extern int dataLen;


extern int mirro_regBufferRx[256];
extern int mirro_regBufferTx[256];

#define someTp_FMT_01   0b00
#define someTp_FMT_02   0b01
#define someTp_FMT_03   0b10
#define someTp_FMT_04   0b11

#define CB_FUNC \
{\
    rxHandling, \
    txHandling, \
    errorHandling,\
}\

#define RLIN_Rx3_REGISTERCONFIG \
{  \
    baseAddr,\
    regBufferRx,\
    regBufferTx,\
    dataLen,\
    regStatus,\
    CB_FUNC,\
}

extern void checkRegisterErr (void);
extern void receiveDataHandling (void);
extern void errorHandling (void);
extern void resetHandling (void);
extern void rxHandling(void);
extern void txHandling(void);
extern void someTp(void);
#endif /*REGISTERMONITOR_H*/ 
