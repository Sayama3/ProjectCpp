#include "test.hpp"

Image sampleImg() {
    Image img(3, 3, 3, ModelType::RGB, 0);
    img(0, 0, 0) = 1 - 1;
    img(0, 0, 1) = 2 - 1;
    img(0, 0, 2) = 3 - 1;
    img(1, 0, 0) = 11 - 1;
    img(1, 0, 1) = 12 - 1;
    img(1, 0, 2) = 13 - 1;
    img(2, 0, 0) = 21 - 1;
    img(2, 0, 1) = 22 - 1;
    img(2, 0, 2) = 23 - 1;
    img(0, 1, 0) = 31 - 1;
    img(0, 1, 1) = 32 - 1;
    img(0, 1, 2) = 33 - 1;
    img(1, 1, 0) = 41 - 1;
    img(1, 1, 1) = 42 - 1;
    img(1, 1, 2) = 43 - 1;
    img(2, 1, 0) = 51 - 1;
    img(2, 1, 1) = 52 - 1;
    img(2, 1, 2) = 53 - 1;
    img(0, 2, 0) = 61 - 1;
    img(0, 2, 1) = 62 - 1;
    img(0, 2, 2) = 63 - 1;
    img(1, 2, 0) = 71 - 1;
    img(1, 2, 1) = 72 - 1;
    img(1, 2, 2) = 73 - 1;
    img(2, 2, 0) = 81 - 1;
    img(2, 2, 1) = 82 - 1;
    img(2, 2, 2) = 83 - 1;
    return img;
}

bool test_SimpleIterator() {
    Image img = sampleImg();
    ImageIterator it(0, 0, 0, img);
    ImageIterator end(0, 3, 0, img);
    uint8_t last = 0;
    for (; it != end; ++it) {
        //std::cerr << *it << std::endl;
        if (*it < last)
            return false;
        last = *it;
    }
    return true;
}

bool test_image() {
    int cnt = 0;
    int w = 255;
    int h = 321;
    int c = 4;
    Image image(w, h, c, ModelType::ARGB, 125);
    for (ImageIterator it(image); it != end(image); ++it) {
        if (*it != 125)
            return false;
        cnt++;
    }
    std::cout << cnt << "/" << (w * h * c) << std::endl;
    return cnt == w * h * c;
}

bool test_filterIterator() {
    //Test1 filterValues
    {
        Image image = sampleImg();
        for (ImageIterator it(image); it != end(image); ++it) {
            uint8_t last = 0;
            //if (it.getRelativeChannel() == 0) {
            uint8_t current = *it;
            std::cout << static_cast<int>(current) << ">>>>>>>";
            auto [filterIt, endIterator] = it.filterIterators(1);
            for (; filterIt != endIterator;) {
                if (true || filterIt.getRelativeChannel() == 0) {
                    std::cout << static_cast<int>(*filterIt) << ", ";
                    if (*filterIt < last || current % 10 != (*filterIt) % 10)
                        return false;
                }
                ++filterIt;
            }
            std::cout << std::endl;
            //}
        }
    }
    std::cerr << "First part of test passed" << std::endl;
    //Test2 filterSizes
    {
        Image image = Image(256, 256, 3, ModelType::HSL, 0);
        int filterSize = 1;
        int square = std::pow(((filterSize * 2) + 1), 2);
        for (ImageIterator it(image); it != end(image); ++it) {
            auto [filterIt, endIterator] = it.filterIterators(filterSize);
            int count = 0;
            for (; filterIt != endIterator; ++filterIt) {
                count++;
            }
            int margin = filterSize + 1;
            if (it.getRelativeRow() > margin && it.getRelativeRow() < (image.GetHeight() - margin) &&
                it.getRelativeCol() > margin &&
                it.getRelativeCol() < (image.GetWidth() - margin)) {
                if (count != square)
                    return false;
            } else {
                if (count > square)
                    return false;
            }
        }
    }
    std::cerr << "Second part of test passed" << std::endl;
    return true;
}

int test_All() {
    if (!test_image())
        return -100;
    if (!test_SimpleIterator())
        return -101;
    if (!test_filterIterator())
        return -102;
    if (!test_genericFilter())
        return -103;
    return 0;
}

bool test_genericFilter() {
    Image img = sampleImg();
    int N = img.GetWidth() * img.GetHeight();
    Image blurred = medianBlur<5>(img);
    ImageIterator it(img);
    ImageIterator en = end(img);
    float av[] = {0, 0, 0};
    for (; it != en; ++it) {
        av[it.getRelativeChannel()] += ((*it) * 1.f) / N;
    }
    for (ImageIterator bl(blurred); bl != end(blurred); ++bl)
        if (*bl != av[bl.getRelativeChannel()])
            return false;
    return true;
}
