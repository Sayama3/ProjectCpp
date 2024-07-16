#ifndef PROJECTCPP_IMAGEITERATOR_HPP
#define PROJECTCPP_IMAGEITERATOR_HPP

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "Image.hpp"

typedef uint8_t pixel;

class ImageIterator : std::iterator<std::forward_iterator_tag, pixel> {
private:
    int row;
    int col;
    int startCol;
    uint32_t width;
    int channel;
    Image &indexed;
public:

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    int getChannel() const {
        return channel;
    }

    explicit inline ImageIterator(int x, int y, int channel, uint32_t width,
                                  Image &indexed) : row(y), col(x), channel(channel),
                                                    width(width),
                                                    indexed(indexed), startCol(col) {
        //std::cerr << " creating v_it" << x << "," << y << std::endl;
    }

    explicit inline ImageIterator(int x, int y, int channel, Image &indexed) : ImageIterator(x, y, channel,indexed.GetWidth(),indexed) {

    }

    explicit inline ImageIterator(int x, int y, Image &indexed) : ImageIterator(x, y, 0, indexed) {

    }

    explicit inline ImageIterator(Image &indexed) : ImageIterator(0, 0, indexed) {
    }

    //Will default to 1, especially when we don't need it, for end typically ?
    pixel operator*() const;

    pixel &operator*();

    ImageIterator operator++();

    ImageIterator operator++(int _);

    bool operator!=(ImageIterator other) const;

    std::tuple<ImageIterator, ImageIterator> filterIterators(int filterExtent);
    //Because why not, equivalent to filterIterators(0) actually
    std::tuple<ImageIterator, ImageIterator> pixelValues(){
        return {ImageIterator(col, row, 0,1,  indexed), ImageIterator(col, row+1, 0, indexed)};
    }
};

inline ImageIterator end(Image image) {
    return ImageIterator(0, image.GetHeight(), 0, 0, image);
}


#endif //PROJECTCPP_IMAGEITERATOR_HPP
