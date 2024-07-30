#ifndef __ENCODER_H
#define __ENCODER_H

//PA4&5 一组编码器
//PA6&7 另一组编码器 

void Encoder_Init(void);
void GetCount(void);
float Encoder_GetM1(void);
float Encoder_GetM2(void);
void Duty_change(void);
float Encoder_GetD1(void);
float Encoder_GetD2(void);
void Speed_Change(float speed_target_left, float speed_target_right);

#endif