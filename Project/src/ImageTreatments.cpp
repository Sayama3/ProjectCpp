#include "ImageTreatments.hpp"

Image LocalTransformation::genericFilter(const Image &img, std::vector<std::vector<float>> filter,bool normalize) {
    int N = filter.size();
    if (N%2==0 || !std::all_of(filter.begin(), filter.end(),
                     [N](auto &v) { return v.size() == N; }))
        throw "Filter must be square and odd sized";
    ImageIterator it(img);
    ImageIterator en = end(img);
    Image copy(img);
    for (; it != en; ++it) {
        float sum = 0;
        //N is odd, N/2 will floor
        auto [filterIt, endIterator] = it.filterIterators(N / 2);
        int norm=0;
        for (; filterIt != endIterator; ++filterIt){
			int v = static_cast<int>(filter[filterIt.getRelativeCol()][filterIt.getRelativeRow()]);
			norm += v;
            sum += (*filterIt) * v;
		}
        it.atOther(copy) = static_cast<int>(sum)/(normalize && norm > 0 ? norm : 1.f);
    }
    return copy;
}
