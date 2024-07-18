#include "ImageTreatments.hpp"

Image genericFilter(const Image &img, std::vector<std::vector<float>> filter,bool normalizeFilterByEffactive) {
    int N = filter.size();
    if (N%2==0 || !std::all_of(filter.begin(), filter.end(),
                     [N](auto &v) { return v.size() == N; }))
        throw "Filter must be square and odd sized";
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
        int norm=0;
        for (; filterIt != endIterator; ++filterIt, ++norm)
            sum += (*filterIt) * filter[filterIt.getRelativeCol()][filterIt.getRelativeRow()];
        copy(x, y, c) = static_cast<int>(sum)/(normalizeFilterByEffactive && norm > 0 ? norm : 1.f);
    }
    return copy;
}

