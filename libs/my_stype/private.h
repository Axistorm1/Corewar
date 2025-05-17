#ifndef MY_STYPE_PRIVATE_H_
    #define MY_STYPE_PRIVATE_H_

enum cntrl1 {
    CNTRL1_MIN = 0x00,
    CNTRL1_MAX = 0x08
};
    #define TAB 0x09
enum cntrl2 {
    CNTRL2_MIN = 0x0A,
    CNTRL2_MAX = 0x0D
};
enum cntrl3 {
    CNTRL3_MIN = 0x0E,
    CNTRL3_MAX = 0x1F
};
    #define SPACE 0x20
enum operands {
    OPERANDS_MIN = 0x21,
    OPERANDS_MAX = 0x2F
};
enum digits {
    DIGITS_MIN = 0x30,
    DIGITS_MAX = 0x39
};
enum symbols {
    SYMBOLS_MIN = 0x3a,
    SYMBOLS_MAX = 0x40
};
enum x_up_char {
    X_UP_CHAR_MIN = 0x41,
    X_UP_CHAR_MAX = 0x46
};
enum up_char {
    UP_CHAR_MIN = 0x47,
    UP_CHAR_MAX = 0x5A
};
enum symbols2 {
    SYMBOLS2_MIN = 0x5B,
    SYMBOLS2_MAX = 0x60
};
enum x_low_char {
    X_LOW_CHAR_MIN = 0x61,
    X_LOW_CHAR_MAX = 0x66
};
enum low_char {
    LOW_CHAR_MIN = 0x67,
    LOW_CHAR_MAX = 0x7A
};
enum symbols3 {
    SYMBOLS3_MIN = 0x7B,
    SYMBOLS3_MAX = 0x7E
};
    #define DEL 0x7F

    #define UPPER_TO_LOWER_DIFF 32

#endif /* MY_STYPE_PRIVATE_H_ */
