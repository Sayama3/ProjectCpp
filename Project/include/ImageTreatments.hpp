#ifndef PROJECTCPP_IMAGETREATMENTS_HPP
#define PROJECTCPP_IMAGETREATMENTS_HPP

#include "Image.hpp"
#include "ImageIterator.hpp"

template<int N>
Image genericFilter(const Image &img, std::array<std::array<float, N>, N> filter);

inline Image sobelFilter(const Image &img) {
//std::array<std::array<float,static_cast<size_t>(3)>,static_cast<size_t>(3)> sobelFilterMatrix;
    //={
    //        {-1, 0, 1},
    //        {-2, 0, 2},
    //        {-1, 0, 1}
    //};
    return Image();// genericFilter(img, sobelFilterMatrix);
}

template<int N>
inline Image medianBlur(const Image &img) {
    std::array<std::array<float, N>, N> filter;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            filter[i][j] = 1.f / (N * N);
        }
    }
    return genericFilter(img, filter);
}

#endif //PROJECTCPP_IMAGETREATMENTS_HPP
