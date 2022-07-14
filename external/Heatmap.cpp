#include "Heatmap.hpp"

SYCL_EXTERNAL std::array<float, 3> HSVtoRGB(float h, float s, float v) {
    float c = v * s;
    double scaledH = sycl::fmod(h / 60.0, 6.0);
    float x = c * (1 - sycl::fabs(sycl::fmod(scaledH, 2.0) - 1));
    float m = v - c;

    std::array<float, 3> rgb = {};
    
    if (0 <= scaledH && scaledH < 1) { rgb[0] = c; rgb[1] = x; rgb[2] = 0; }
    else if (1 <= scaledH && scaledH < 2) { rgb[0] = x; rgb[1] = c; rgb[2] = 0; }
    else if (2 <= scaledH && scaledH < 3) { rgb[0] = 0; rgb[1] = c; rgb[2] = x; }
    else if (3 <= scaledH && scaledH < 4) { rgb[0] = 0; rgb[1] = x; rgb[2] = c; }
    else if (4 <= scaledH && scaledH < 5) { rgb[0] = x; rgb[1] = 0; rgb[2] = c; }
    else if (5 <= scaledH && scaledH < 6) { rgb[0] = c; rgb[1] = 0; rgb[2] = x; }
    else { rgb[0] = 0; rgb[1] = 0; rgb[2] = 0; }
    
    return rgb;
}

SYCL_EXTERNAL std::array<float, 3> findColor(float val) {
    float h = (1.0f - val) * 120.0f;
    return HSVtoRGB(h, 100, 50);
}
