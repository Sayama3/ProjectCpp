#ifndef PROJECTCPP_IMAGEITERATOR_HPP
#define PROJECTCPP_IMAGEITERATOR_HPP

#include "Image.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

typedef uint8_t pixel;

class ImageIterator {
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = pixel;
	using difference_type = std::ptrdiff_t;
	using pointer = const pixel *;
	using reference = const pixel &;

private:
	int startRow;
	int relativeRow;
	int startCol;
	int relativeCol;
	uint32_t width;
	int startChannel;
	int channel;
	int amountOfChannel;
	Image const *indexed;

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
								  Image const *indexed) : relativeRow(0), startRow(y), relativeCol(0), startCol(x), channel(0), startChannel(channel),
														  width(width),
														  indexed(indexed),
														  amountOfChannel(amountOfChannel) {
		//std::cerr << " creating v_it" << x << "," << y << std::endl;
	}

	explicit inline ImageIterator(int x, int y, int channel, uint32_t width,
								  Image const *indexed) : ImageIterator(x, y, channel, indexed->GetWidth(),
																		indexed->GetChannels() - channel, indexed) {
	}

	explicit inline ImageIterator(int x, int y, int channel, Image const *indexed) : ImageIterator(x, y, channel,
																								   indexed->GetWidth(),
																								   indexed) {
	}

	explicit inline ImageIterator(int x, int y, Image const *indexed) : ImageIterator(x, y, 0, indexed) {
	}

	explicit inline ImageIterator(Image const *indexed) : ImageIterator(0, 0, indexed) {
	}
	explicit inline ImageIterator(const Image &indexed) : ImageIterator(&indexed) {
	}
	inline ImageIterator(const ImageIterator &iterator) : ImageIterator(iterator.getRelativeCol(), iterator.getRelativeRow(), iterator.getRelativeChannel(), iterator.indexed) {
		this->startCol = iterator.startCol;
		this->startRow = iterator.startRow;
		this->startChannel = iterator.startChannel;
		this->width = iterator.width;
		this->amountOfChannel = iterator.amountOfChannel;
	}
	inline pixel &atOther(Image &otherImage) const {
		return otherImage(getCol(), getRow(), getChannel());
	}
	inline void copyCurrentValue(Image &otherImage) const {
		this->atOther(otherImage) = **this;
	}
	const pixel &operator*() const;

	ImageIterator operator++();

	bool operator!=(const ImageIterator& other) const;
	inline bool operator==(const ImageIterator& other) const {
		return !(*this != other);
	}
	ImageIterator &operator=(const ImageIterator &other) {
		if (this != &other) {
			this->startCol = other.startCol;
			this->startRow = other.startRow;
			this->startChannel = other.startChannel;
			this->width = other.width;
			this->amountOfChannel = other.amountOfChannel;
			this->indexed = other.indexed;
			this->relativeCol = other.relativeCol;
			this->relativeRow = other.relativeRow;
			this->channel = other.channel;
			return *this;
		}
	}

	std::tuple<ImageIterator, ImageIterator> filterIterators(int filterExtent) const;

	//Because why not, equivalent to filterIterators(0) actually
	std::tuple<ImageIterator, ImageIterator> pixelValues() const {
		return {ImageIterator(relativeCol, relativeRow, 0, 1, indexed), ImageIterator(relativeCol, relativeRow + 1, 0, indexed)};
	}
};

inline ImageIterator end(Image const *image) {
	return ImageIterator(0, image->GetHeight(), 0, image);
}
inline ImageIterator end(const Image &image) {
	return end(&image);
}


#endif//PROJECTCPP_IMAGEITERATOR_HPP
