#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "CppStun.h"
void CppStun::displayHeader(const StunHeader &header)
{
    const unsigned char *p = reinterpret_cast<const unsigned char *>(&header);
    displayBuff(p, sizeof(header));
}
void CppStun::displayBuff(const unsigned char *p, int len)
{
    std::cout << std::hex;
    for (int i = 0; i < len; ++i)
    {
        std::cout << std::setw(2) << static_cast<unsigned>(p[i]) << " " << std::ends;
        if ((i + 1) % 4 == 0)
            std::cout << std::endl;
    }
    std::cout << std::dec;
}


void CppStun::test(int s, const StunHeader &header, const sockaddr *ad)
{
    sendto(s, &header, sizeof(header), 0, ad, sizeof(sockaddr));
}

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in ad;
    ad.sin_family = AF_INET;
    ad.sin_port = htons(3478);
    ad.sin_addr.s_addr = inet_addr("217.10.68.152");

    StunHeader header;
    header.msgType = htons((unsigned short)MsgType::BindingRequest);
    header.length = 0;
    header.id[0] = 1;
    header.id[1] = 2;
    header.id[2] = 2;
    header.id[3] = 3;

    CppStun::test(s, header, (sockaddr *)&ad);
    unsigned char recvBuff[1024];
    socklen_t len = sizeof(ad);
    int i = recvfrom(s, recvBuff, 1024, 0, (sockaddr *)&ad, &len);
    CppStun::displayBuff(recvBuff, i);
    return 0;
}