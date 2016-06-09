#include "Road.h"
#include "Intersection.h"
#include "Lane.h"

Road::Road(Intersection &source, Intersection &target): source(source), target(target) {
    update();
}

void Road::update() {
    sourceSideId = source.getRectangle().getSectorId(target.getRectangle().getCenter());
    targetSideId = target.getRectangle().getSectorId(source.getRectangle().getCenter());
    sourceSide = source.getRectangle().getSide(sourceSideId).getSubsegment(0, 0.5);
    targetSide = target.getRectangle().getSide(targetSideId).getSubsegment(0.5, 1);
    int lanesNumber = std::max(2, (int) (std::min(sourceSide.getLength(),
                                      targetSide.getLength()) / Settings::getInstance().getGridSize()));
    std::vector<Segment<double>> sourceSplits = sourceSide.getSplittedSubsegments(lanesNumber, true);
    std::vector<Segment<double>> targetSplits = targetSide.getSplittedSubsegments(lanesNumber, false);
    lanes.resize(lanesNumber);
    for (int i = 0; i < lanesNumber; i++) {
        lanes[i] = new Lane(sourceSplits[i], targetSplits[i], *this);
    }
    for (int i = 0; i < lanesNumber; i++) {
        Lane *leftAdjacentLane = NULL;
        if (i != 0) {
            leftAdjacentLane = lanes[i - 1];
        }
        Lane *rightAdjacentLane = NULL;
        if (i != lanesNumber - 1) {
            leftAdjacentLane = lanes[i + 1];
        }
        lanes[i]->setAdjacents(leftAdjacentLane, rightAdjacentLane, lanes.back(), lanes[0]);
    }
}