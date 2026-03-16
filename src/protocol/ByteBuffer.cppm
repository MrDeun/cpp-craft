module;
#include <cstdint>
#include <string_view>
#include <vector>
export module mc.protocol.buffer;

export class Buffer {
public:
  void writeByte(uint8_t byte);
  void writeVarInt(int32_t value);
  void writeString(std::string_view);

  uint8_t readByte();
  uint8_t readVarInt();
  std::string readString();

  protected:
  std::vector<uint8_t> buffer;
  size_t read_pos = 0;

};