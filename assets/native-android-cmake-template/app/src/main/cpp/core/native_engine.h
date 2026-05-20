#pragma once

#include <cstdint>
#include <vector>

namespace nativeengine {

std::vector<std::uint8_t> process_bytes(
    const std::uint8_t* input,
    int length
);

}  // namespace nativeengine
