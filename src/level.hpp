#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "qtree.hpp"

enum VisionType {
    FULL_VISION,
    KNOWN_VISION,
    LOCAL_VISION
};

class Level {
    public:
        Level() {
            visionType = KNOWN_VISION;
        }
        Qtree<char> data;
        Qtree<bool> vision;
        Qtree<bool> latestVision;
        std::string status;
        VisionType visionType;
};

#endif
