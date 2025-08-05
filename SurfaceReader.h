#ifndef SURFACEREADER_H
#define SURFACEREADER_H

#include <string>
#include <vector>

struct SurfaceElement {
    double tau;
    double x, y;
    double eta;

    double dsigma_t, dsigma_x, dsigma_y;
    double dsigma_eta;

    double vx, vy;
    double v_eta;

    double pi00, pi01, pi02, pi03;
    double pi11, pi12, pi13;
    double pi22, pi23;
    double pi33;

    double bulkPi;

    double Tdec, Edec, Pdec, muBdec;
};

class SurfaceReader {
public:
    explicit SurfaceReader(const std::string& filename);
    bool readSurface();  

    size_t size() const;
    const std::vector<SurfaceElement>& elements() const;

private:
    std::string filename_;
    std::vector<SurfaceElement> elements_;
};

#endif // SURFACEREADER_H

