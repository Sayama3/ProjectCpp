#ifndef PROJECTCPP_IMAGEITERATOR_HPP
#define PROJECTCPP_IMAGEITERATOR_HPP

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "Image.hpp"

typedef uint8_t const pixel;

class ImageIterator : std::iterator<std::forward_iterator_tag, pixel> {
private:
    int startRow;
    int relativeRow;
    int startCol;
    int relativeCol;
    uint32_t width;
    int startChannel;
    int channel;
    int endChannel;
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

    explicit inline ImageIterator(int x, int y, int channel, uint32_t width, int endChannel,
                                  const Image &indexed) : relativeRow(0), startRow(y), relativeCol(0), startCol(x), channel(0), startChannel(channel),
                                                          width(width),
                                                          indexed(indexed),
                                                          endChannel(endChannel) {
        //std::cerr << " creating v_it" << x << "," << y << std::endl;
    }

    explicit inline ImageIterator(int x, int y, int channel, uint32_t width,
                                  const Image &indexed) : ImageIterator(x, y, channel, indexed.GetWidth(),
                                                                        indexed.GetChannels(), indexed) {
    }

    explicit inline ImageIterator(int x, int y, int channel, const Image &indexed) : ImageIterator(x, y, channel,
                                                                                                   indexed.GetWidth(),
                                                                                                   indexed) {

    }

    explicit inline ImageIterator(int x, int y, const Image &indexed) : ImageIterator(x, y, 0, indexed) {

    }

    explicit inline ImageIterator(const Image &indexed) : ImageIterator(0, 0, indexed) {
    }

    //Will default to 1, especially when we don't need it, for end typically ?
    pixel operator*() const;

    pixel &operator*();

    ImageIterator operator++();

    ImageIterator operator++(int _);

    bool operator!=(ImageIterator other) const;

    std::tuple<ImageIterator, ImageIterator> filterIterators(int filterExtent);

    //Because why not, equivalent to filterIterators(0) actually
    std::tuple<ImageIterator, ImageIterator> pixelValues() {
        return {ImageIterator(relativeCol, relativeRow, 0, 1, indexed), ImageIterator(relativeCol, relativeRow + 1, 0, indexed)};
    }
};

inline ImageIterator end(const Image& image) {
    return ImageIterator(0, image.GetHeight(), 0, image);
}


#endif //PROJECTCPP_IMAGEITERATOR_HPP
