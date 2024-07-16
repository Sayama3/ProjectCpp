#ifndef PROJECTCPP_IMAGETREATMENTS_HPP
#define PROJECTCPP_IMAGETREATMENTS_HPP
#include "Image.hpp"
#include "ImageIterator.hpp"
const float sobelFilterMatrix[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
};
template<int N>
Image genericFilter(const Image &img,const float (&filter)[N][N]);
inline Image sobelFilter(const Image &img){
    return genericFilter(img, sobelFilterMatrix);
}
template<int N>
inline Image medianBlur(const Image &img){
    const float filter[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            filter[i][j] = 1.f/(N*N);
        }
    }
    return genericFilter(img, filter);
}
#endif //PROJECTCPP_IMAGETREATMENTS_HPP
