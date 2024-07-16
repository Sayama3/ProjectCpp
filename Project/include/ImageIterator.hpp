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
    int channel;
    Image &indexed;
public:
    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    explicit inline ImageIterator(int x, int y, int channel, Image &indexed) : channel(channel), row(y),
                                                                               indexed(indexed), col(x) {
        //std::cerr << " creating v_it" << x << "," << y << std::endl;
    }

    explicit inline ImageIterator(int x, int y, Image &indexed) : ImageIterator(x, y, 0, indexed) {

    }

    explicit inline ImageIterator(Image &indexed) : ImageIterator(0, 0, 0, indexed) {
    }

    //Will default to 1, especially when we don't need it, for end typically ?
    pixel operator*() const;

    pixel &operator*();

    ImageIterator operator++();

    ImageIterator operator++(int _);

    bool operator!=(ImageIterator other) const;
};

inline ImageIterator end(Image image) {
    return ImageIterator(0, image.GetHeight(), 0, image);
}

#endif //PROJECTCPP_IMAGEITERATOR_HPP
