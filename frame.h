#ifndef FRAME_H
#define FRAME_H

class Frame
{
public:
    Frame() {}
    virtual ~Frame() {}
public:
    static const char FRAME_START = '(';
    static const char FRAME_SEPARATOR = ',';
    static const char FRAME_END = ')';
    static const char FRAME_TYPE_GET = 'G';
    static const char FRAME_TYPE_SET = 'S';
    static const char FRAME_TYPE_RESPONSE = 'R';
    static const char FRAME_TYPE_ERROR = 'E';
    static const char FRAME_TYPE_ECHO = '?';
};

#endif // FRAME_H
