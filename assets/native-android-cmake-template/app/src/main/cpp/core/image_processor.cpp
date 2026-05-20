#include "image_processor.h"

#include <algorithm>

namespace nativeimage {

std::vector<std::uint8_t> invert_rgba(
    const std::uint8_t* pixels,
    int width,
    int height,
    int stride_bytes
) {
    if (pixels == nullptr || width <= 0 || height <= 0 || stride_bytes < width * 4) {
        return {};
    }

    std::vector<std::uint8_t> output(static_cast<std::size_t>(width * height * 4));

    for (int y = 0; y < height; ++y) {
        const std::uint8_t* row = pixels + static_cast<std::size_t>(y * stride_bytes);
        for (int x = 0; x < width; ++x) {
            const std::size_t src = static_cast<std::size_t>(x * 4);
            const std::size_t dst = static_cast<std::size_t>((y * width + x) * 4);
            output[dst] = static_cast<std::uint8_t>(255 - row[src]);
            output[dst + 1] = static_cast<std::uint8_t>(255 - row[src + 1]);
            output[dst + 2] = static_cast<std::uint8_t>(255 - row[src + 2]);
            output[dst + 3] = row[src + 3];
        }
    }

    return output;
}

}  // namespace nativeimage
