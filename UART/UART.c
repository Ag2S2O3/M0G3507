#include "UART.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"

uint8_t gEchoData;
uint8_t flag;
uint8_t stage;
uint8_t RollL;
uint8_t RollH;
uint8_t PitchL;
uint8_t PitchH;
uint8_t YawL;
uint8_t YawH;
uint8_t VL;
uint8_t VH;
uint8_t SUM;
uint8_t parity;

//初始化函数
void UART_Init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    stage=0;
    RollL=0;
    RollH=0;
    PitchL=0;
    PitchH=0;
    YawL=0;
    YawH=0;
    VL=0;
    VH=0;
    SUM=0;
}


//中断服务函数
void UART_0_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            flag=1;
            gEchoData = DL_UART_Main_receiveData(UART_0_INST);
            Data_Decoder(gEchoData);
            break;
        default:
            break;
    }
}

//返回接收的数据
uint8_t UART_Recive(void)
{
    return gEchoData;
}


//返回中断标志位
uint8_t UART_GetFlag(void)
{
    if(flag==1)
    {
        return 1;
        flag=0;
    }
    else {
        return 0;
    }
        
}

void Data_Decoder(uint8_t data)
{
    if(stage == 0)  //等待接收数据头（0x55）
    {
        if(data == 0x55)
            stage = 1;
    }
    else if (stage == 1)    //等待接收角度数据（0x53） 
    {
        if (data == 0x53) {
            stage = 2;
        }
        else 
            stage = 0;
    }
    else if(stage > 1 && stage < 10)
    {
        switch (stage) {
            case 2: RollL = data; break;
            case 3: RollH = data; break;
            case 4: PitchL = data; break;
            case 5: PitchH = data; break;
            case 6: YawL = data; break;
            case 7: YawH = data; break;
            case 8: VL = data; break;
            case 9: VH = data; break;
        }
        stage++;
    }
    else if(stage == 10)
    {
        SUM = (0x55+0x53+RollH+RollL+PitchH+PitchL+YawH+YawL+VH+VL) & 0x0F;
        if(data == SUM)
            parity = 0;
        else
            parity = 1;
        stage = 0;
    }
}

float UART_ReturnRoll(void)
{
    float Roll;
    Roll = (short)((short) RollH << 8 | RollL ) * 180.000 / 32768.000 ;
    return Roll;
}

float UART_ReturnPitch(void)
{
    float Pitch;
    Pitch = (short)((short) PitchH << 8 | PitchL ) * 180.000 / 32768.000 ;
    return Pitch;
}

float UART_ReturnYaw(void)
{
    float Yaw;
    Yaw = (short)((short) YawH << 8 | YawL ) * 180.000 / 32768.000 ;
    return Yaw;
}
