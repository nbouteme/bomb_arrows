#ifndef FOLPHIN_H
#define FOLPHIN_H

typedef unsigned char u8;
typedef char s8;
typedef int s32;
typedef unsigned u32;
typedef unsigned short u16;

typedef s32 OSPriority;
typedef int BOOL;

struct OSThreadQueue;
typedef struct OSThreadQueue OSThreadQueue;

struct PADStatus;
typedef struct PADStatus PADStatus;

typedef struct {
	u8 __pad[0x318];
} OSThread;

void OSReport(const char*, ...);
void OSYieldThread();
BOOL OSCreateThread(OSThread*  thread,
					void*    (*func)(void*),
					void*      param,
					void*      stack,
					u32        stackSize,
					OSPriority priority,
					u16        attr );
void       OSSleepThread       ( OSThreadQueue* queue );
s32        OSResumeThread      ( OSThread* thread );

typedef struct PADStatus
{
    u16 button;         
    s8  stickX;         
    s8  stickY;         
    s8  substickX;      
    s8  substickY;      
    u8  triggerLeft;    
    u8  triggerRight;   
    u8  analogA;        
    u8  analogB;        
    s8  err;            
} PADStatus;

#define PAD_BUTTON_LEFT         0x0001
#define PAD_BUTTON_RIGHT        0x0002
#define PAD_BUTTON_DOWN         0x0004
#define PAD_BUTTON_UP           0x0008
#define PAD_TRIGGER_Z           0x0010
#define PAD_TRIGGER_R           0x0020
#define PAD_TRIGGER_L           0x0040
#define PAD_BUTTON_A            0x0100
#define PAD_BUTTON_B            0x0200
#define PAD_BUTTON_X            0x0400
#define PAD_BUTTON_Y            0x0800
#define PAD_BUTTON_MENU         0x1000
#define PAD_BUTTON_START        0x1000

#endif /* FOLPHIN_H */