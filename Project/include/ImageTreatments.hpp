#ifndef PROJECTCPP_IMAGETREATMENTS_HPP
#define PROJECTCPP_IMAGETREATMENTS_HPP

#include "Image.hpp"
#include "ImageIterator.hpp"

Image genericFilter(const Image &img, std::vector<std::vector<float>> filter,bool normalizeFilterByEffactive = false);

inline Image sobelFilter(const Image &img) {
    std::vector<std::vector<float>> sobelFilterMatrix =
            {
                    {-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}
            };
    return genericFilter(img, sobelFilterMatrix);
}

template<int N>
inline Image medianBlur(const Image &img) {
    std::vector<std::vector<float>> filter(N, std::vector<float>(N,1.f));
    return genericFilter(img, filter,true);
}
template<int N> Image erode(const Image& img);
template<int N> Image dilate(const Image& img);

#endif //PROJECTCPP_IMAGETREATMENTS_HPP
