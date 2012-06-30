#define DLL_EXPORT // for export

#include "dll.h"

#ifdef __cplusplus
extern "C" {
#endif

void CColorImage(void* buffer, int width, int height,
  BYTE b, BYTE g, BYTE r) {
    int x, y;
    BYTE* buf = (BYTE*)buffer;

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x) {
            *buf = (BYTE)((b + *buf) >> 1); ++buf;
            *buf = (BYTE)((g + *buf) >> 1); ++buf;
            *buf = (BYTE)((r + *buf) >> 1); ++buf;
            ++buf;
        }
    }
}

int Lim(double x, double y, int limit) {
    int i, c = 0;
    double px = 0, py = 0, nx, ny;

    for (i = 0; i < limit; ++i) {
        nx = px * px - py * py + x;
        ny = 2 * px * py + y;
        if (nx * nx + ny * ny > 4.0) {
            c = i + 1;
            break;
        } else {
            px = nx;
            py = ny;
        }
    }
    if (c == 0) { c = limit; }
    return c;
}

void CCalcMandel(void* buf, int width, int height, int limit, double scale) {
    BYTE* data = (BYTE*)buf;
    int t, x, y;

    for (y = 0; y < height; ++y) {
        for (x = 0; x < width; ++x) {
            t = Lim(x / scale - 2, y / scale - 1, limit);
            if (t < limit) {
                t <<= 4;
                if (t > 0xff) {
                    t = 0xff;
                }
            } else {
                t = 0;
            }
            *data = t; ++data;
            *data = 0; ++data;
            *data = 0; ++data;
            ++data;
       }
    }
}

#ifdef __cplusplus
}
#endif