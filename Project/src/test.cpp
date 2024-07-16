#include "test.hpp"
#include "ImageIterator.hpp"

bool test_SimpleIterator() {
    Image img(3, 3, 3, ModelType::RGB, 0);
    img(1, 0, 0) = 1;
    img(1, 0, 1) = 1;
    img(1, 0, 2) = 1;
    img(2, 0, 0) = 2;
    img(2, 0, 1) = 2;
    img(2, 0, 2) = 2;
    img(0, 1, 0) = 3;
    img(0, 1, 1) = 3;
    img(0, 1, 2) = 3;
    img(1, 1, 0) = 4;
    img(1, 1, 1) = 4;
    img(1, 1, 2) = 4;
    img(2, 1, 0) = 5;
    img(2, 1, 1) = 5;
    img(2, 1, 2) = 5;
    img(0, 2, 0) = 6;
    img(0, 2, 1) = 6;
    img(0, 2, 2) = 6;
    img(1, 2, 0) = 7;
    img(1, 2, 1) = 7;
    img(1, 2, 2) = 7;
    img(2, 2, 0) = 8;
    img(2, 2, 1) = 8;
    img(2, 2, 2) = 8;
    ImageIterator it(0, 0,0, img);
    ImageIterator end(0, 3,0, img);
    uint8_t last = 0;
    for (; it != end; it++) {
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
    int c = 1;
    Image image(w, h, c, ModelType::ARGB, 125);
    for (ImageIterator it(image); it != end(image); it++) {
        if (*it != 125)
            return false;
        cnt++;
    }
    std::cout << cnt << "/" << (w * h * c) << std::endl;
    return cnt == w * h * c;
}

int test_All() {
    if (!test_image())
        return -100;
    if (!test_SimpleIterator())
        return -101;
    return 0;
}