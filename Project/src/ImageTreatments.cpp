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
        float sum = 0;
        //N is odd, N/2 will floor
        auto [filterIt, endIterator] = it.filterIterators(N / 2);
        int norm=0;
        for (; filterIt != endIterator; ++filterIt, ++norm)
            sum += (*filterIt) * filter[filterIt.getRelativeCol()][filterIt.getRelativeRow()];
        it.atOther(copy) = static_cast<int>(sum)/(normalizeFilterByEffactive && norm > 0 ? norm : 1.f);
    }
    return copy;
}
template<int N>
Image median(const Image &img) {
	Image median(img.GetHeight(),img.GetWidth(),img.GetChannels(),img.GetImageType(),0);
	for (ImageIterator it(img); it != end(img); ++it) {
		auto [filterIt, endIterator] = it.filterIterators(N / 2);
		std::sort(filterIt,endIterator,[](auto &a,auto &b){return *a<*b;});
		it.atOther(median)=std::min_element(filterIt,endIterator,[](auto &a,auto &b){return *a<*b;});
	}
}
template<int N>
Image erode(const Image &img) {
	Image eroded(img.GetHeight(),img.GetWidth(),img.GetChannels(),img.GetImageType(),0);
	for (ImageIterator it(img); it != end(img); ++it) {
		auto [filterIt, endIterator] = it.filterIterators(N / 2);
		it.atOther(eroded)=std::min_element(filterIt,endIterator,[](auto &a,auto &b){return *a<*b;});
	}
}
template<int N>
Image dilate(const Image &img) {
	Image dilated(img.GetHeight(),img.GetWidth(),img.GetChannels(),img.GetImageType(),0);
	for (ImageIterator it(img); it != end(img); ++it) {
		auto [filterIt, endIterator] = it.filterIterators(N / 2);
		it.atOther(dilated)=std::max_element(filterIt,endIterator,[](auto &a,auto &b){return *a<*b;});
	}
}
