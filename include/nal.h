#ifndef NAL_H_
#define NAL_H_

#include <cstdint>
#include <cstddef>

namespace rtpinfo {

struct NALUnit {

    
    explicit NALUnit(std::size_t size) m_size(size) {
        m_data.reset(new std::uint8_t[m_size]);
    }

    // disable copy
    NALUnit & operator=(const NALUnit&)=delete;
    NALUnit(const NALUnit&)=delete;

    std::unique_ptr<std::uint8_t[]> m_data;
    std::size_t m_size;


};

} // namespace rtpinfo

#endif  // NAL_H_
