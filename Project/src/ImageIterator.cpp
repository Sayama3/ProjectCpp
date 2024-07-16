#include "ImageIterator.hpp"

//Will default to 1, especially when we don't need it, for end typically ?

pixel ImageIterator::operator*() const {
    return *(*this);
}

pixel &ImageIterator::operator*() {
    return indexed(getCol(), getRow(), getChannel());
}

ImageIterator ImageIterator::operator++() {
    channel++;
    if (channel >= endChannel) {
        channel = 0;
        relativeCol++;
        if (relativeCol >= width) {
            relativeCol = 0;
            relativeRow++;
        }
    }
    return *this;
}

ImageIterator ImageIterator::operator++(int _) {
    auto cp(*this);
    ++(*this);
    return cp;
}

bool ImageIterator::operator!=(ImageIterator other) const {
    return other.getRow() != this->getRow() || other.getCol()!= this->getCol() ||
           other.getChannel() != this->getChannel();
}

std::tuple<ImageIterator, ImageIterator> ImageIterator::filterIterators(int filterExtent) {
    int startX = std::max(0, relativeCol - filterExtent);
    int startY = std::max(0, relativeRow - filterExtent);
    int endX = std::min(static_cast<uint32_t>(relativeCol + filterExtent + 1), indexed.GetWidth());
    int endY = std::min(static_cast<uint32_t>(relativeRow + filterExtent + 1), indexed.GetHeight());
    auto begin = ImageIterator(startX, startY, channel,
                               endX - startX,channel+1, indexed);
    //We don't need maxWidth nor channel, only used for comparison of a non moving iterator
    auto end = ImageIterator(startX, endY, channel, indexed);
    return {begin, end};
}

#include "ImageIterator.hpp"
