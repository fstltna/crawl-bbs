#pragma once

class PcgRNG
{
    public:
        PcgRNG();
        PcgRNG(uint64_t init_key[], int key_length);
        uint32_t get_uint32();
        uint64_t get_uint64();
        uint32_t operator()() { return get_uint32(); }

        typedef uint32_t result_type;
        static constexpr uint32_t min() { return 0; }
        static constexpr uint32_t max() { return 0xffffffffU; }

    private:
        uint64_t state_;
        uint64_t inc_;
};
