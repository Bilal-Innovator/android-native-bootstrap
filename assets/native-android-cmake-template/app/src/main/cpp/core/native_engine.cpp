#include "native_engine.h"

namespace nativeengine {

std::vector<std::uint8_t> process_bytes(
    const std::uint8_t* input,
    int length
) {
    if (input == nullptr || length <= 0) {
        return {};
    }

    std::vector<std::uint8_t> output(input, input + length);
    return output;
}

}  // namespace nativeengine
