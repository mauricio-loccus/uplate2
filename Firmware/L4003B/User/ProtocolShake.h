





#define COLOR_SHAKE_BK   0x51320c//0xe7a362 //滤光片-数字的底色
#define COLOR_SHAKE_TXT  0xffffff//0xf8e1c6 //滤光片-数字的颜色

#define COLOR_TXT_DISABLE  0x515151

#define COLOR_SHAKE_TIME_BK  0x51320c//0x796e6b
//#define COLOR_TIME_BK      0xe7a362  //模式项-选中时的背景色
//#define COLOR_TIME_TXT     0xffffff  //模式项-选中时的文字

#define COLOR_PAINT_TXT          0xf7f1ef


//振动模式
enum
{
    SHAKE_FIRST = 0,
    SHAKE_EACH,
};

#ifndef __PROTOCOL_SHAKE_H
#define __PROTOCOL_SHAKE_H


void ProtocolShake_Interface(void);
void ProtocolShake_Scan(void);
void ProtocolShake_Go(void);
#endif
