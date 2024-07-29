#ifndef __ENCODER_H
#define __ENCODER_H

//PA4&5 一组编码器
//PA6&7 另一组编码器 

void Encoder_Init(void);
void GetCount(void);
uint16_t Encoder_GetM1(void);
uint16_t Encoder_GetM2(void);

#endif