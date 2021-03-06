#include <vector>
#include <iostream>
#include <stdint.h>

#include "print.hpp"
#include "model/gameState.hpp"

#include "protocol/deserializer.hpp"
#include "protocol/header.hpp"
#include "protocol/buffer.hpp"
#include "protocol/v8_0/protocol.hpp"
#include "protocol/v7_6/protocol.hpp"

// const uint8_t buffer[] {0x00, -1, 0x01, -1, 0x73, -1, -1};
// uint8_t buffer[] {
//     0x00, 0x05, 0x76, 0x20, 0x37, 0x2e, 0x36, 0x00,
//     0x00, 0x01, 0x73,

//     0xa6,
//     0x01, 0x00, 0x00, 0x0c, 0x10, 0x01, 0x3a, 0x03, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
//     0x00, 0x03, 0x14, 0x00, 0x01, 0x01, 0x00, 0x03, 0x03, 0x01, 0x06, 0x05, 0x01, 0x00, 0x00, 0x00,
//     0x03, 0x00, 0x01, 0x03, 0x02, 0x04, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
//     0x06, 0x00, 0x00, 0x08, 0x35, 0x33, 0x37, 0x31, 0x36, 0x34, 0x30, 0x32, 0x0a, 0x00, 0x00, 0x08,
//     0x51, 0x52, 0x57, 0x55, 0x56, 0x54, 0x53, 0x50, 0x0b, 0x00, 0x00, 0x08, 0x5c, 0x5f, 0x58, 0x5d,
//     0x5e, 0x5b, 0x59, 0x5a, 0x0d, 0x00, 0x00, 0x08, 0x6c, 0x68, 0x6f, 0x6d, 0x69, 0x6e, 0x6b, 0x6a,
//     0x06, 0x01, 0x52, 0x6f, 0x62, 0x69, 0x6e, 0x20, 0x61, 0x64, 0x73, 0x66, 0xe1, 0x06, 0x00, 0x0c,
//     0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x04, 0x00, 0x04, 0x06,
//     0x01, 0x00, 0x31, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x0e, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00
// };
uint8_t buffer[] {
    0x00, 0x05, 0x76, 0x20, 0x37, 0x2e, 0x36, 0x00, 0x00, 0x01, 0x73,
    0x8a,
    0x01,
    0x00, 0x00, 0x0c, 0x12, 0x01, 0x3a, 0x03, 0x01,
    0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x03, 0x14, 0x00, 0x01, 0x01, 0x00, 0x03, 0x03,
    0x01, 0x06, 0x05, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x03, 0x02, 0x04, 0x03, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x00, 0x00, 0x08, 0x35, 0x33, 0x37, 0x31, 0x36,
    0x34, 0x30, 0x32, 0x0a, 0x00, 0x00, 0x08, 0x51, 0x52, 0x57, 0x55, 0x56, 0x54, 0x53, 0x50, 0x0b,
    0x00, 0x00, 0x08, 0x5c, 0x5f, 0x58, 0x5d, 0x5e, 0x5b, 0x59, 0x5a, 0x0d, 0x00, 0x00, 0x08, 0x6c,
    0x68, 0x6f, 0x6d, 0x69, 0x6e, 0x6b, 0x6a, 0x02, 0x01, 0x52, 0x6f, 0x62, 0x69, 0x6e, 0x20, 0x61,
    0x64, 0x73, 0x66, 0xe1, 0x06, 0x00, 0x0b, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x80, 0x04, 0x00, 0x04, 0x06, 0x01, 0x00, 0x31, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00
};
// const uint8_t buffer[] {0x00, -1, 0x01, -1, 0x73, -1, -1, 0x00, -1, 0x05, 0x76, -1, 0x20, 0x37, -1, 0x2e, 0x36};
// const uint8_t buffer[] {0xa0, -1, 0x01};
// const uint8_t buffer[] { 0x00, 0x03, 'a', 'b', 'c'};
// const uint8_t buffer[] {0xa0, -1, 0x01, -1, -1, 0xa0, -1, 0x01, 0xa0, 0x01};

int main()
{
    std::size_t bufferSize = sizeof(buffer);

    uint8_t *bufferPos = buffer;

    uint8_t outputBuffer[1024];

    ghh::protocol::Buffer b(bufferPos, bufferSize);

    while(true){
        ghh::protocol::Header head;
        auto ok = ghh::protocol::readHeader(head, b);
        if(ok)
        {
            std::cout << "Event: " << head.event
                      << ", payload: " << head.payload
                      << ", data length: " << head.length << "\n";
            if (head.event == "s"){
                if (head.length <= b.getPosition()){
                    ghh::GameState s;
                    int32_t message_number = b.readFullInt();
                    ghh::protocol::v7_6::readGameState(s, b);
                }
                else
                {
                    std::cout << head.length << " > " <<  b.getPosition() << "\n";
                    std::cout << "incomplete game state\n";
                    break;
                }
            }
        }
        else
        {
            break;
        }

    }

    std::cout << "readBytes: " << b.getPosition() << "\n";
}
