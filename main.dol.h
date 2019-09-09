#pragma once

typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef short    wchar_t;
typedef struct dCcD_Sph dCcD_Sph, *PdCcD_Sph;

typedef struct cCcD_Obj cCcD_Obj, *PcCcD_Obj;

typedef struct dCcD_Stts dCcD_Stts, *PdCcD_Stts;

typedef struct dCcD_GObjAt dCcD_GObjAt, *PdCcD_GObjAt;

typedef struct cXyz cXyz, *PcXyz;

typedef struct dCcD_GObjTg dCcD_GObjTg, *PdCcD_GObjTg;

typedef struct cM3dGSph cM3dGSph, *PcM3dGSph;

typedef struct cCcD_SrcObj cCcD_SrcObj, *PcCcD_SrcObj;

typedef struct cCcD_Stts cCcD_Stts, *PcCcD_Stts;

typedef struct dCcD_GStts dCcD_GStts, *PdCcD_GStts;

typedef struct dCcD_SrcGObjTg dCcD_SrcGObjTg, *PdCcD_SrcGObjTg;

typedef struct Vec *PVec;

typedef struct dCcD_SrcGObjAt dCcD_SrcGObjAt, *PdCcD_SrcGObjAt;

struct cCcD_Stts { /* PlaceHolder Structure */
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined4 field_0x18;
};

struct dCcD_GStts { /* PlaceHolder Class Structure */
    ulong (** field_0x0)(void);
    byte field_0x4;
    byte field_0x5;
    byte field_0x6;
    undefined field_0x7;
    undefined2 field_0x8;
    undefined field_0xa;
    undefined field_0xb;
    undefined4 field_0xc;
    undefined4 field_0x10;
    undefined4 field_0x14;
    undefined4 field_0x18;
    undefined4 field_0x1c;
};

struct dCcD_Stts { /* PlaceHolder Class Structure */
    struct cCcD_Stts base;
    struct dCcD_GStts field_0x1c;
};

struct Vec { /* PlaceHolder Structure */
    float x;
    float y;
    float z;
};

struct cM3dGSph { /* PlaceHolder Class Structure */
    struct Vec center;
    float radius;
};

struct dCcD_SrcGObjAt { /* PlaceHolder Structure */
    byte field_0x0;
    byte field_0x1;
    byte field_0x2;
    undefined field_0x3;
    uint field_0x4;
};

struct cCcD_SrcObj { /* PlaceHolder Structure */
    struct cCcD_SrcObj * base;
    ulong (* field_0x4)(void);
    byte field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    uint field_0xc;
    uint field_0x10;
    uint collmask_a; /* Created by retype action */
    uint onCo; /* Created by retype action */
    struct dCcD_SrcGObjAt field_0x1c;
};

struct dCcD_SrcGObjTg { /* PlaceHolder Structure */
    byte field_0x0;
    byte field_0x1;
    byte field_0x2;
    byte field_0x3;
    undefined4 field_0x4;
};

struct cCcD_Obj { /* PlaceHolder Structure */
    uint collisionMode;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    ulong (* field_0x10)(void);
    byte field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    uint collMask_a;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    uint field_0x28;
    uint onCo;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    ulong (** field_0x3c)(void);
    struct cCcD_SrcObj * field_0x40;
};

struct dCcD_GObjAt { /* PlaceHolder Class Structure */
    uint field_0x0;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    byte field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    byte field_0x1c;
    byte field_0x1d;
    byte field_0x1e;
    byte field_0x1f;
};

struct cXyz { /* PlaceHolder Class Structure */
    float x;
    float y;
    float z;
};

struct dCcD_GObjTg { /* PlaceHolder Class Structure */
    undefined4 field_0x0;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    byte field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    struct dCcD_SrcGObjTg field_0x1c;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    struct cXyz pos;
    undefined4 field_0x44;
};

struct dCcD_Sph {
    struct cCcD_Obj base;
    struct dCcD_Stts * collisionStatus; /* Created by retype action */
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    struct dCcD_GObjAt objat;
    undefined field_0x70;
    undefined field_0x71;
    undefined field_0x72;
    undefined field_0x73;
    undefined field_0x74;
    undefined field_0x75;
    undefined field_0x76;
    undefined field_0x77;
    undefined field_0x78;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    struct cXyz movementVec;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    struct dCcD_GObjTg field_0x90;
    undefined field_0xd8;
    undefined field_0xd9;
    undefined field_0xda;
    undefined field_0xdb;
    undefined field_0xdc;
    undefined field_0xdd;
    undefined field_0xde;
    undefined field_0xdf;
    undefined field_0xe0;
    undefined field_0xe1;
    undefined field_0xe2;
    undefined field_0xe3;
    undefined field_0xe4;
    undefined field_0xe5;
    undefined field_0xe6;
    undefined field_0xe7;
    byte field_0xe8;
    undefined field_0xe9;
    undefined field_0xea;
    undefined field_0xeb;
    undefined field_0xec;
    undefined field_0xed;
    undefined field_0xee;
    undefined field_0xef;
    undefined1 shape_attr; /* Created by retype action */
    undefined field_0xf1;
    undefined field_0xf2;
    undefined field_0xf3;
    undefined field_0xf4;
    undefined field_0xf5;
    undefined field_0xf6;
    undefined field_0xf7;
    undefined1 shape_attr2; /* Created by retype action */
    undefined field_0xf9;
    undefined field_0xfa;
    undefined field_0xfb;
    undefined field_0xfc;
    undefined field_0xfd;
    undefined field_0xfe;
    undefined field_0xff;
    undefined field_0x100;
    undefined field_0x101;
    undefined field_0x102;
    undefined field_0x103;
    undefined field_0x104;
    undefined field_0x105;
    undefined field_0x106;
    undefined field_0x107;
    ulong (* field_0x108)(void);
    ulong (** field_0x10c)(void);
    ulong (** field_0x110)(void);
    ulong (** field_0x114)(void);
    struct cM3dGSph spheredef; /* Created by retype action */
    ulong (** field_0x128)(void);
    ulong (* field_0x12c)(void);
};

