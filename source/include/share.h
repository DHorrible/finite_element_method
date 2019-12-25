#ifndef SHARE_H
#define SHARE_H

#define STD_CFG_NAME "config.conf"
#define STD_MAX_LEN_CFG_STR 64
#define STD_SIZE_FIN_ELEM_MTX 12

enum Doffs {
    DOFF1 = 0x100000,
    DOFF2 = 0x010000,
    DOFF3 = 0x001000,
    DOFF4 = 0x000100,
    DOFF5 = 0x000010,
    DOFF6 = 0x000001,
    DOFF_ALL = DOFF1 | DOFF2 | DOFF3 | DOFF4 | DOFF5 | DOFF6,
    DOFF_NONE = ~DOFF_ALL
};

enum Constraints {
    CSTR1 = 0x011111,
    CSTR2 = 0x101111,
    CSTR3 = 0x110111,
    CSTR4 = 0x111011,
    CSTR5 = 0x111101,
    CSTR6 = 0x111110,
    CSTR_ALL = CSTR1 & CSTR2 & CSTR3 & CSTR4 & CSTR5 & CSTR6,
    CSTR_NONE = ~CSTR_ALL
};

#endif
