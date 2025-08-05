#ifndef SURFACE_SEARCHER_H
#define SURFACE_SEARCHER_H

#include "SurfaceReader.h"
#include "nanoflann.hpp"
#include <vector>

struct SurfacePointCloud {
    const std::vector<SurfaceElement>& surface;

    inline size_t kdtree_get_point_count() const {
        return surface.size();
    }

    inline double kdtree_get_pt(const size_t idx, const size_t dim) const {
        const auto& e = surface[idx];
        if (dim == 0) return e.tau;
        if (dim == 1) return e.x;
        return e.y;
    }

    template <class BBOX>
    bool kdtree_get_bbox(BBOX&) const {
        return false;
    }
};

class SurfaceSearcher {
public:
    explicit SurfaceSearcher(const std::vector<SurfaceElement>& elements);

    const SurfaceElement* findClosest(double tau, double x, double y) const;

private:
    const std::vector<SurfaceElement>& surface_;
    SurfacePointCloud cloud_;

    using KDTree = nanoflann::KDTreeSingleIndexAdaptor<
        nanoflann::L2_Simple_Adaptor<double, SurfacePointCloud>,
        SurfacePointCloud,3 >;

    KDTree index_;
};

#endif // SURFACE_SEARCHER_H

