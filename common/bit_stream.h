#ifndef _BUF_BIT_STREAM_H_
#define _BUF_BIT_STREAM_H_

#include "common/typedefs.h"

class BitReader
{
public:
    explicit BitReader(const char* srcBuf, int startByte = 0, int startBit = 0)
        : src_buf_(srcBuf), byte_pos_(0), bit_pos_(0)
    {

    }

    BitReader(const BitReader& other)
    {
        this->src_buf_ = other.src_buf_;
        this->byte_pos_ = other.byte_pos_;
        this->bit_pos_ = other.bit_pos_;
    }

    const BitReader& operator=(const BitReader& other)
    {
        this->src_buf_ = other.src_buf_;
        this->byte_pos_ = other.byte_pos_;
        this->bit_pos_ = other.bit_pos_;
        return *this;
    }

    const char* SrcBuf() const { return src_buf_; }

    void SetBytePos(int bytePos) { byte_pos_ = bytePos; }

    int BytePos() const { return byte_pos_; }

    void SetBitPos(int bitPos) { bit_pos_ = bitPos; }

    int BitPos() const { return bit_pos_; }

    void Align()
    {
        if (bit_pos_ != 0)
        {
            byte_pos_++;
            bit_pos_ = 0;
        }
    }

    void SkipBits(int bitN)
    {
        for (int i = 0; i != bitN; ++i)
        {
            bit_pos_++;
            if (bit_pos_ == 8)
            {
                byte_pos_++;
                bit_pos_ = 0;
            }
        }
    }

    void SkipBytes(int byteN)
    {
        byte_pos_ += byteN;
    }

    vp_uint8_t ReadBit1()
    {
        vp_uint8_t val = 0;
        int shift_len = 7 - bit_pos_;
        if (shift_len)
        {
            val = (src_buf_[byte_pos_] >> shift_len) & 0x01;
        }
        else
        {
            val = src_buf_[byte_pos_] & 0x01;
        }
        bit_pos_++;
        if (bit_pos_ == 8)
        {
            byte_pos_++;
            bit_pos_ = 0;
        }
        return val;
    }

    vp_uint8_t ReadBitUI08(int bitN)
    {
        vp_uint8_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        return val;
    }

    vp_uint16_t ReadBitUI16(int bitN)
    {
        vp_uint16_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        return val;
    }

    vp_uint32_t ReadBitUI32(int bitN)
    {
        vp_uint32_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        return val;
    }

    vp_uint64_t ReadBitUI64(int bitN)
    {
        vp_uint64_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        return val;
    }

    //////////////////////////////////////////////////////////////////////////

    vp_uint8_t ShowBitUI08(int bitN)
    {
        int last_byte_pos = BytePos();
        int last_bit_pos = BitPos();

        vp_uint8_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        SetBytePos(last_byte_pos);
        SetBitPos(last_bit_pos);

        return val;
    }

    vp_uint16_t ShowBitUI16(int bitN)
    {
        int last_byte_pos = BytePos();
        int last_bit_pos = BitPos();

        vp_uint16_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        SetBytePos(last_byte_pos);
        SetBitPos(last_bit_pos);

        return val;
    }

    vp_uint32_t ShowBitUI32(int bitN)
    {
        int last_byte_pos = BytePos();
        int last_bit_pos = BitPos();

        vp_uint32_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        SetBytePos(last_byte_pos);
        SetBitPos(last_bit_pos);

        return val;
    }

    vp_uint64_t ShowBitUI64(int bitN)
    {
        int last_byte_pos = BytePos();
        int last_bit_pos = BitPos();

        vp_uint64_t val = 0;

        for (int i = 0; i != bitN; ++i)
        {
            val <<= 1;
            val |= ReadBit1();
        }

        SetBytePos(last_byte_pos);
        SetBitPos(last_bit_pos);

        return val;
    }

private:
    const char* src_buf_;
    int byte_pos_;
    int bit_pos_;
};

#endif // _BUF_BIT_STREAM_H_
