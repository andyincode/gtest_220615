// 17_Mocking4.cpp
#include <stdio.h>

struct Packet
{
};

class PacketStream
{
public:
  void AppendPacket(Packet *newPacket)
  {
    printf("PacketStream::AddPacket\n");
  }

  const Packet *GetPacket(size_t packetNumber) const
  {
    printf("PacketStream::GetPacket\n");
    return nullptr;
  }
};

class PacketReader
{
public:
  // Template을 이용한 의존성 주입 설계 방법입니다.
  template <typename PacketStream>
  void ReadPacket(PacketStream *stream, size_t packetNumber)
  {
    // stream->AppendPacket(nullptr);
    // stream->GetPacket(10);
  }
};

#include <gmock/gmock.h>

class MockPacketStream
{
public:
  MOCK_METHOD(void, AppendPacket, (Packet * newPacket));
  MOCK_METHOD(const Packet *, GetPacket, (size_t packetNumber), (const));
};

TEST(PacketReaderTest, Sample)
{
  MockPacketStream mock;
  PacketReader reader;

  EXPECT_CALL(mock, AppendPacket);
  EXPECT_CALL(mock, GetPacket);

  reader.ReadPacket(&mock, 10);
}