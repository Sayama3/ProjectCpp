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
        if ((col-startCol) >= width) {
            col = startCol;
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

std::tuple<ImageIterator, ImageIterator> ImageIterator::filterIterators(int filterExtent) {
    if(channel!=0)
        std::cerr<<"Initializing a filter iterator not at the beggining of a channel, probably an error\n";
    int startX = std::max(0, col - filterExtent);
    int startY = std::max(0, row - filterExtent);
    int endX = std::min(static_cast<uint32_t>(col + filterExtent + 1), indexed.GetWidth());
    int endY = std::min(static_cast<uint32_t>(row + filterExtent + 1), indexed.GetHeight());
    auto begin = ImageIterator(startX, startY, channel,
                               endX - startX, indexed);
    auto end = ImageIterator(startX, endY, channel, indexed);
    return {begin, end};
}

#include "ImageIterator.hpp"
