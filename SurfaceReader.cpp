#include "SurfaceReader.h"
#include <fstream>
#include <iostream>

SurfaceReader::SurfaceReader(const std::string& filename)
    : filename_(filename) {}

bool SurfaceReader::readSurface() {
    std::ifstream fin(filename_, std::ios::binary);
    if (!fin) {
        std::cerr << "Error: Cannot open file " << filename_ << std::endl;
        return false;
    }

    elements_.clear();

    
    SurfaceElement elem;
    while (fin.read(reinterpret_cast<char*>(&elem), sizeof(SurfaceElement))) {
        elements_.push_back(elem);
    }

    if (elements_.empty()) {
        std::cerr << "No surface elements read from file." << std::endl;
        return false;
    }

    std::cout << "Read " << elements_.size() << "surface elements from " << filename_ << std::endl;
    return true;
}

size_t SurfaceReader::size() const {
    return elements_.size();
}

const std::vector<SurfaceElement>& SurfaceReader::elements() const {
    return elements_;
}

