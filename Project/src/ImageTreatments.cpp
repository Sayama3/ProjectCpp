#include "ImageTreatments.hpp"

template<int N>
Image genericFilter(const Image &img,std::array<std::array<float,N>,N> filter){
    ImageIterator it(img);
    ImageIterator en = end(img);
    Image copy(img);
    for (; it != en; ++it) {
        int x = it.getRelativeCol();
        int y = it.getRelativeRow();
        int c = it.getRelativeChannel();
        float sum = 0;
        //N is odd, N/2 will floor
        auto [filterIt, endIterator] = it.filterIterators(N / 2);
        for (; filterIt != endIterator; ++filterIt)
            sum += *filterIt * filter[filterIt.getRelativeCol()][filterIt.getRelativeRow()];
        copy(x, y, c) = static_cast<int>(sum);
    }
    return copy;
}

