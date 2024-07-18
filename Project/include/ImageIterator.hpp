#ifndef PROJECTCPP_IMAGEITERATOR_HPP
#define PROJECTCPP_IMAGEITERATOR_HPP

#include "Image.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

typedef uint8_t pixel;

class ImageIterator {
	typedef std::forward_iterator_tag iterator_category;
	typedef pixel value_type;
	typedef pixel difference_type;
	typedef pixel *pointer;
	typedef pixel &reference;

private:
	int startRow;
	int relativeRow;
	int startCol;
	int relativeCol;
	uint32_t width;
	int startChannel;
	int channel;
	int amountOfChannel;
	const Image &indexed;

public:
	int getRelativeRow() const {
		return relativeRow;
	}
	int getRow() const {
		return relativeRow + startRow;
	}

	int getRelativeCol() const {
		return relativeCol;
	}
	int getCol() const {
		return relativeCol + startCol;
	}

	int getRelativeChannel() const {
		return channel;
	}
	int getChannel() const {
		return channel + startChannel;
	}

	explicit inline ImageIterator(int x, int y, int channel, uint32_t width, int amountOfChannel,
								  const Image &indexed) : relativeRow(0), startRow(y), relativeCol(0), startCol(x), channel(0), startChannel(channel),
														  width(width),
														  indexed(indexed),
														  amountOfChannel(amountOfChannel) {
		//std::cerr << " creating v_it" << x << "," << y << std::endl;
	}

	explicit inline ImageIterator(int x, int y, int channel, uint32_t width,
								  const Image &indexed) : ImageIterator(x, y, channel, indexed.GetWidth(),
																		indexed.GetChannels() - channel, indexed) {
	}

	explicit inline ImageIterator(int x, int y, int channel, const Image &indexed) : ImageIterator(x, y, channel,
																								   indexed.GetWidth(),
																								   indexed) {
	}

	explicit inline ImageIterator(int x, int y, const Image &indexed) : ImageIterator(x, y, 0, indexed) {
	}

	explicit inline ImageIterator(const Image &indexed) : ImageIterator(0, 0, indexed) {
	}
	inline ImageIterator(const ImageIterator &image) : ImageIterator(image.getRelativeCol(), image.getRelativeRow(), image.getRelativeChannel(), image.indexed) {
		this->startCol = image.startCol;
		this->startRow = image.startRow;
		this->startChannel = image.startChannel;
		this->width = image.width;
		this->amountOfChannel = image.amountOfChannel;
	}
	inline pixel &atOther(Image &otherImage) const {
		return otherImage(getCol(), getRow(), getChannel());
	}
	inline void copyCurrentValue(Image &otherImage) const {
		this->atOther(otherImage) = **this;
	}
	//Will default to 1, especially when we don't need it, for end typically ?
	pixel operator*() const;

	pixel &operator*();

	ImageIterator operator++();

	bool operator!=(ImageIterator other) const;

	std::tuple<ImageIterator, ImageIterator> filterIterators(int filterExtent);

	//Because why not, equivalent to filterIterators(0) actually
	std::tuple<ImageIterator, ImageIterator> pixelValues() {
		return {ImageIterator(relativeCol, relativeRow, 0, 1, indexed), ImageIterator(relativeCol, relativeRow + 1, 0, indexed)};
	}
};

inline ImageIterator end(const Image &image) {
	return ImageIterator(0, image.GetHeight(), 0, image);
}


#endif//PROJECTCPP_IMAGEITERATOR_HPP
