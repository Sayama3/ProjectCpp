#include "ImageIterator.hpp"

//Will default to 1, especially when we don't need it, for end typically ?

pixel ImageIterator::operator*() const {
    return *(*this);
}

pixel &ImageIterator::operator*() {
    return indexed(col, row, channel);
}

ImageIterator ImageIterator::operator++() {
    //if (((col + row) % 1000) == 0)
    //    std::cerr << "++ing" << col << "," << row << std::endl;
    channel++;
    if (channel >= indexed.GetChannels()) {
        channel = 0;
        col++;
        if (col >= indexed.GetWidth()) {
            col = 0;
            row++;
        }
    }
    //std::cerr << "+=ed to " << col << "," << row << std::endl;
    return *this;
}

ImageIterator ImageIterator::operator++(int _) {
    auto cp(*this);
    ++(*this);
    return cp;
}

bool ImageIterator::operator!=(ImageIterator other) const {
    return other.row != this->row || other.col != this->col;
}

#include "ImageIterator.hpp"
