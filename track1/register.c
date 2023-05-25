/*
 * register.c
 *
 *  Created on: May 18, 2023
 *      Author: gogoCow
 */

#include "resetRegister.h"
#include "registerMonitor.h"

static RLIN_Register LIN_Rx3;
int baseAddr;
int regBufferRx[255];
int regBufferTx[255];
int dataLen;
int regStatus;

int mirro_regBufferRx[256];
int mirro_regBufferTx[256];

void configureRegister(void)
{
    LIN_Rx3 = RLIN_Rx3_REGISTERCONFIG;
    return;
}

void checkRegisterErr(void)
{

    return;
}

void receiveDataHandling(void)
{
    int l_fmt__u8;
    int idx;
    l_fmt__u8 = (int)(mirro_regBufferRx[0] >> 6);
    switch (l_fmt__u8)
    {
    case someTp_FMT_01:
    case someTp_FMT_02:
    {
        mirro_regBufferTx[0] = (int)(l_fmt__u8 << 6);
        mirro_regBufferTx[1] = dataLen;
        for (idx = 2; idx < dataLen; idx++)
        {
            /* code */
            mirro_regBufferTx[idx + 2] = mirro_regBufferRx[idx] & 0x55;
        }
        mirro_regBufferTx[idx + 2] = 0xFE;
        break;
    }
    case default:
    {
        /* Do not support*/
        break;
    }
    }

    return;
}
void errorHandling(void)
{
    int idx;
    if (LIN_Rx3.registerStatus & TX_ERROR)
    {
        /* clear TX buffer */
        for (idx = 0; idx < 255; idx++)
        {
            LIN_Rx3.regBufferRx[idx] = 0x00;
            mirro_regBufferTx[idx] = 0x00;
        }
    }
    else if (LIN_Rx3.registerStatus & RX_ERROR)
    {
        /* clear RX buffer */
        for (idx = 0; idx < 255; idx++)
        {
            LIN_Rx3.regBufferRx[idx] = 0x00;
            mirro_regBufferRx[idx] = 0x00;
        }
    }

    return;
}
void resetHandling(void)
{
    if (LIN_Rx3.registerStatus && 0xFF)
    {
        LIN_Rx3.registerStatus = 0x00;
    }
    errorHandling();
    return;
}

void rxHandling(void)
{
    int idx = 0;

    idx = LIN_Rx3.length;
    /* copy data to the mirror*/
    do
    {
        mirro_regBufferRx[idx] = LIN_Rx3.regBufferRx[idx];
        idx--;
    } while (idx > 0) return;
}

void txHandling(void)
{
    int idx = 0;

    idx = LIN_Rx3.length;
    /* copy data to the mirror*/
    do
    {
        LIN_Rx3.regBufferTx[idx] = mirro_regBufferTx[idx];
        idx--;
    } while (idx > 0) return;
}

void someTp(void)
{
    int idx = 0;
    int calCS = 0;
    /*Calculate checksum*/
    for (idx = 0; i < (LIN_Rx3.length - 1); i++)
    {
        calCS = calCS + LIN_Rx3.regBufferRx[idx];
    }

    if (calCS != LIN_Rx3.regBufferRx[idx])
    {
        resetHandling();
    }
    else
    {
        /*Handling the data received*/
        receiveDataHandling();
    }
    return;
}