#pragma once
#include <netinet/in.h>
//https://tools.ietf.org/html/rfc3489
enum class MsgType : unsigned short
{
    BindingRequest = 0x0001,
    BindingResponse = 0x0101,
    BindingErrorResponse = 0x0111,
    SharedSecretRequest = 0x0002,
    SharedSecretResponse = 0x0102,
    SharedSecretErrorResponse = 0x0112
};
enum class AttrType : unsigned short
{
    // stun attributes
    /*
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |x x x x x x x x|    Family     |           Port                |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |                             Address                           |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * 
     */
    MappedAddress = 0x0001,
    ResponseAddress = 0x0002,
    ChangeRequest = 0x0003,
    SourceAddress = 0x0004,
    ChangedAddress = 0x0005,
    Username = 0x0006,
    Password = 0x0007,
    MessageIntegrity = 0x0008,
    ErrorCode = 0x0009,
    UnknownAttribute = 0x000A,
    ReflectedFrom = 0x000B,
    XorOnly = 0x0021,
    XorMappedAddress = 0x8020,
    ServerName = 0x8022,
    SecondaryAddress = 0x8050 // Non standard extension
};
//sizeof(StunHeader)=20UL
struct StunHeader
{
    unsigned short msgType;
    unsigned short length;
    unsigned int id[4];
};

class CppStun
{
  public:
    void sar(int s);
    static void displayHeader(const StunHeader &header);
    static void displayBuff(const unsigned char *p, int len);
    static void test(int s, const StunHeader &header, const sockaddr *ad);
};
