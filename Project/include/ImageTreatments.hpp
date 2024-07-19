#ifndef PROJECTCPP_IMAGETREATMENTS_HPP
#define PROJECTCPP_IMAGETREATMENTS_HPP

#include "Image.hpp"
#include "ImageIterator.hpp"
#include "cmath"
#include "numeric"
#include <algorithm>
namespace LocalTransformation {

	Image genericFilter(const Image &img, std::vector<std::vector<float>> filter, bool normalize = false);
	inline Image sobelFilter(const Image &img, bool horizontal = true) {
		std::vector<std::vector<float>> sobelFilterMatrix;
		if (horizontal)
			sobelFilterMatrix =
					{
							{-1, -2, -1},
							{0, 0, 0},
							{1, 2, 1}};
		else
			sobelFilterMatrix =
					{
							{-1, 0, 1},
							{-2, 0, 2},
							{-1, 0, 1}};
		return genericFilter(img, sobelFilterMatrix);
	}
	inline Image sobelH(const Image &img) { return sobelFilter(img, true); }
	inline Image sobelV(const Image &img) { return sobelFilter(img, false); }

	inline Image sobelNorm(const Image &img) {
		Image sob1 = sobelFilter(img, true);
		Image sob2 = sobelFilter(img, false);
		Image result = Image(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			it.atOther(result) = static_cast<uint8_t>(std::sqrt(std::pow(it.atOther(sob1), 2) + std::pow(it.atOther(sob2), 2)));
		}
		return result;
	}
	inline Image sharpening(const Image &img) {
		std::vector<std::vector<float>> sharpeningFilterMatrix =
				{
						{0, -1, 0},
						{-1, 5, -1},
						{0, -1, 0}};
		return genericFilter(img, sharpeningFilterMatrix);
	}
	inline Image gaussianBlur(const Image &img) {
		std::vector<std::vector<float>> gaussianFilterMatrix =
				{
						{1, 4, 6, 4, 1},
						{4, 16, 24, 16, 4},
						{6, 24, 36, 24, 6},
						{4, 16, 24, 16, 4},
						{1, 4, 6, 4, 1},
				};
		return genericFilter(img, gaussianFilterMatrix, true);
	}

	inline Image meanBlur(const Image &img, int N) {
		std::vector<std::vector<float>> filter(N, std::vector<float>(N, 1.f));
		return genericFilter(img, filter, true);
	}

	Image erode(const Image &img, int N) {
		Image eroded(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			auto [filterIt, endIterator] = it.filterIterators(N / 2);
			uint8_t min = *filterIt;
			for (; filterIt != endIterator; ++filterIt)
				min = std::max(min, *filterIt);
			it.atOther(eroded) = min;
		}
		return eroded;
	}

	Image dilate(const Image &img, int N) {
		Image dilated(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			auto [filterIt, endIterator] = it.filterIterators(N / 2);
			uint8_t max = *filterIt;
			for (; filterIt != endIterator; ++filterIt)
				max = std::max(max, *filterIt);
			it.atOther(dilated) = max;
		}
		return dilated;
	}

	Image median(const Image &img, int N) {
		Image median(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			auto [filterIt, endIterator] = it.filterIterators(N / 2);
			std::vector<uint8_t> values(filterIt, endIterator);
			std::sort(values.begin(), values.end());
			it.atOther(median) = values[values.size() / 2];
		}
		return median;
	}

	Image localConstrast(const Image &img, float factor, int N) {
		Image contrast(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			auto [filterIt, endIterator] = it.filterIterators(N / 2);
			int cnt = 0;
			int sum = 0;
			for (; filterIt != endIterator; ++filterIt, ++cnt)
				sum += *filterIt;
			it.atOther(contrast) += static_cast<uint8_t>(factor * ((*it) - sum / cnt));
		}
		return contrast;
	}

	Image adaptiveThreshold(const Image &img, int offset, int N) {
		Image contrast(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			auto [filterIt, endIterator] = it.filterIterators(N / 2);
			int cnt = 0;
			int sum = 0;
			for (; filterIt != endIterator; ++filterIt, ++cnt)
				sum += *filterIt;
			it.atOther(contrast) = *it > (sum / cnt) + offset ? 255 : 0;
		}
		return contrast;
	}

	Image morphologicGradient(const Image &img, int N) {
		Image gradient(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			auto [filterIt, endIterator] = it.filterIterators(N / 2);
			uint8_t max = *filterIt;
			uint8_t min = *filterIt;
			for (; filterIt != endIterator; ++filterIt) {
				max = std::max(max, *filterIt);
				min = std::min(min, *filterIt);
			}
			it.atOther(gradient) = max - min;
		}
		return gradient;
	}

	Image meanShift(const Image &img, int threshold, int N) {
		Image meanShifted(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (ImageIterator it(img); it != end(img); ++it) {
			auto [filterIt, endIterator] = it.filterIterators(N / 2);
			int cnt = 0;
			int sum = 0;
			for (; filterIt != endIterator; ++filterIt) {
				if (std::abs(*filterIt - *it) < threshold) {
					sum += *filterIt;
					cnt++;
				}
			}
			it.atOther(meanShifted) = sum / cnt;
		}
		return meanShifted;
	}

}// namespace LocalTransformation
#endif//PROJECTCPP_IMAGETREATMENTS_HPP
