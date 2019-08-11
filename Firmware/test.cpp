#include <vector>
#include <stdint.h>

#include "gameState.hpp"
#include "message.hpp"
#include "print.hpp"
#include "inputStream.hpp"
#include "packet.hpp"
#include "utils.hpp"

// const std::vector<const int32_t> input_buffer{0x00, -1, 0x01, -1, 0x73, -1, -1};
const std::vector<int32_t> input_buffer{
    0x00, -1, 0x05, 0x76, -1, 0x20, 0x37, -1, 0x2e, 0x36, -1, 0x00, 0x00, 0x01, 0x73, -1,
    0xa6,
    0x01, 0x00, 0x00, 0x0c, 0x10, 0x01, 0x3a, 0x03, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
    0x00, 0x03, 0x14, 0x00, 0x01, 0x01, 0x00, 0x03, 0x03, 0x01, 0x06, 0x05, 0x01, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x01, 0x03, 0x02, 0x04, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
    0x06, 0x00, 0x00, 0x08, 0x35, 0x33, 0x37, 0x31, -1, 0x36, 0x34, 0x30, 0x32, 0x0a, 0x00, 0x00, 0x08,
    0x51, 0x52, 0x57, 0x55, 0x56, 0x54, 0x53, 0x50, 0x0b, 0x00, 0x00, 0x08, 0x5c, 0x5f, 0x58, 0x5d,
    0x5e, 0x5b, 0x59, 0x5a, 0x0d, 0x00, 0x00, 0x08, 0x6c, 0x68, 0x6f, 0x6d, 0x69, 0x6e, 0x6b, 0x6a,
    0x06, 0x01, 0x52, 0x6f, 0x62, 0x69, 0x6e, 0x20, 0x61, 0x64, 0x73, 0x66, 0xe1, 0x06, 0x00, 0x0c,
    0x0c, 0x07, 0x00, 0x00, 0x00, -1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x04, 0x00, 0x04, 0x06,
    0x01, 0x00, 0x31, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0e, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00

};
// const std::vector<const int32_t> input_buffer{0x00, -1, 0x01, -1, 0x73, -1, -1, 0x00, -1, 0x05, 0x76, -1, 0x20, 0x37, -1, 0x2e, 0x36};
// const std::vector<const int32_t> input_buffer{0xa0, -1, 0x01};
// const std::vector<const int32_t> input_buffer{0xa0, -1, 0x01, -1, -1, 0xa0, -1, 0x01, 0xa0, 0x01};
std::size_t input_buffer_index = 0;

void on_packet(std::string event, std::string payload, uint8_t *data, std::size_t dataLength)
{
    ghr::print("Event: ", event, ", payload: ", payload, ", data length: ", dataLength, "\n");
    ghr::Message msg(data, dataLength);
    if (event[0] == 's')
    {
        ghr::GameState state;

        // 4 bytes representing message number. Throw away for now
        msg.readByte();
        msg.readByte();
        msg.readByte();
        msg.readByte();

        state.round = msg.readInt(true);
        state.scenario_number = msg.readInt(true);
        state.scenario_level = msg.readInt(true);
        state.track_standees = msg.readBoolean();
        state.random_standees = msg.readBoolean();
        state.elites_first = msg.readBoolean();
        state.expire_conditions = msg.readBoolean();
        state.solo = msg.readBoolean();
        state.hide_stats = msg.readBoolean();
        state.calculate_stats = msg.readBoolean();
        state.can_draw = msg.readBoolean();
        state.needs_shuffle = msg.readBoolean();
        state.player_init = msg.readEnum(ghr::getPlayerInitValues());
        msg.readEnumArray(state.attackModifiers, ghr::getAttackModifierValues());
        state.attackModifier1 = msg.readEnumOrNull(ghr::getAttackModifierValues());
        state.attackModifier2 = msg.readEnumOrNull(ghr::getAttackModifierValues());
        state.fire = msg.readEnum(ghr::getElementStateValues());
        state.ice = msg.readEnum(ghr::getElementStateValues());
        state.air = msg.readEnum(ghr::getElementStateValues());
        state.earth = msg.readEnum(ghr::getElementStateValues());
        state.light = msg.readEnum(ghr::getElementStateValues());
        state.dark = msg.readEnum(ghr::getElementStateValues());

        ghr::print(state);
    }
}

const int32_t read_dummy_data()
{
    if (input_buffer_index < input_buffer.size())
    {
        return input_buffer[input_buffer_index++];
    }
    return -1;
}
const std::size_t bufferCapacity = 1024;
uint8_t buffer[bufferCapacity];
ghr::InputStream input(&read_dummy_data, buffer, bufferCapacity);
ghr::Packet packet(on_packet, input);

int main()
{
    // input.queueReadVarint([](int32_t result) {
    //     std::cout << "Result: \"" << result << "\"\n";
    // });
    // input.queueReadVarint([](int32_t result) {
    //     std::cout << "Result: \"" << result << "\"\n";
    // });
    // input.queueReadVarint([](int32_t result) {
    //     std::cout << "Result: \"" << result << "\"\n";
    // });
    // input.queueReadUTFString([](std::string result) {
    //     std::cout << "Result: \"" << result << "\"\n";
    // });

    // input.onData([]() {

    // });

    for (auto i = 0; i < 10; i++)
    {
        packet.update();
    }
}
