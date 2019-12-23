#ifndef SHARE_H
#define SHARE_H

#define STD_CFG_NAME "config.conf"
#define STD_MAX_LEN_CFG_STR 64

enum Doffs {
    DOFF1 = 0x100000,
    DOFF2 = 0x010000,
    DOFF3 = 0x001000,
    DOFF4 = 0x000100,
    DOFF5 = 0x000010,
    DOFF6 = 0x000001,
    DOFF_ALL = DOFF1 | DOFF2 | DOFF3 | DOFF4 | DOFF5 | DOFF6
};

enum Constraints {
    CSTR0 = 0x111111,
    CSTR1 = 0x000000
};

#endif
