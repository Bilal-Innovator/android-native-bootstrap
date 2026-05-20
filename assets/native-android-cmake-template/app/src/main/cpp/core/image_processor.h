#pragma once

#include <cstdint>
#include <vector>

namespace nativeimage {

std::vector<std::uint8_t> invert_rgba(
    const std::uint8_t* pixels,
    int width,
    int height,
    int stride_bytes
);

}  // namespace nativeimage
