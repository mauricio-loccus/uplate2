
#define  TOUCH_RELEASE_DELAY 10

#define TOUCH_KEY_DELAY    1
#define TOUCH_KEY_REPEAT   2


#define KEY_DELAY    1
#define KEY_REPEAT   15





#define EXT_KEY_START  0x01
#define EXT_KEY_STOP   0x08
#define EXT_KEY_INOUT  0x02





#ifndef _TOUCH_KEY_H
#define _TOUCH_KEY_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif



    enum
    {
        KEY_PROTOCOL_MEASURE=1,
        KEY_PROTOCOL_SHAKE,
        KEY_PROTOCOL_INTER,
        KEY_PROTOCOL_LAYOUT,
        KEY_PROTOCOL_CALCULATE,
        KEY_PROTOCOL_QUALITY,
    };



//5.????
    typedef struct
    {
        unsigned  short   KeyStatus;        //???
        unsigned  short   KeyStatusBack;    //?????
        unsigned  short   KeyValue;         //??
        unsigned  short   KeyValueBack;     //????
        unsigned  short   KeyPressDelay;    //????
        unsigned  short   KeyPressTimes;    //?????
    } TOUCH_KEY;

    extern TOUCH_KEY  TouchKey;



//5.外部按键
    typedef struct
    {
        unsigned  short   KeyStatus;        //键状态
        unsigned  short   KeyStatusBack;    //键状态备份
        unsigned  short   KeyValue;         //键值
        unsigned  short   KeyValueBack;     //键值备份
        unsigned  short   KeyPressDelay;    //键值延时
        unsigned  short   KeyPressTimes;    //键值按计数
    } EXT_KEY;

    extern EXT_KEY  Key;

    void KeyProcess(void);
    void TouchKeyScan(void);
    void KeyScan(void);

#if defined(__cplusplus)
}
#endif

#endif
