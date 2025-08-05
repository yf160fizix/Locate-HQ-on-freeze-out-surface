#include "SurfaceSearcher.h"

SurfaceSearcher::SurfaceSearcher(const std::vector<SurfaceElement>& elements)
    : surface_(elements), cloud_{elements},
      index_(3, cloud_, nanoflann::KDTreeSingleIndexAdaptorParams(10)) {
    index_.buildIndex();
}

const SurfaceElement* SurfaceSearcher::findClosest(double tau, double x, double y) const {
    double query_pt[3] = { tau, x, y };
    size_t ret_index;
    double out_dist_sqr;

    nanoflann::KNNResultSet<double> resultSet(1);
    resultSet.init(&ret_index, &out_dist_sqr);
    index_.findNeighbors(resultSet, query_pt);

    return &surface_[ret_index];
}

