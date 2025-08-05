#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "SurfaceReader.h"
#include "SurfaceSearcher.h"
#include "predefine.h"



int main() {
    
    SurfaceReader surf("surface.dat");
    if (!surf.readSurface()) return 1;
    const auto& elements = surf.elements();

    //***********this part is not necessary; 
    //it convert binary data "surface.dat" into ASCII text data "text_surface.dat"
    std::ofstream fout("text_surface.dat");
    if (!fout) {
        std::cerr << "Error: Cannot open output file." << std::endl;
        return 1;
    }
    fout << "# tau x y dsigma_t dsigma_x dsigma_y\n";
    for (size_t i = 0; i < surf.size(); ++i) {
        const auto& ele = surf.elements()[i];
        fout << ele.tau << " " << ele.x  << " " << ele.y << " "
           //  << e.eta      << " "
             << ele.dsigma_t << " " << ele.dsigma_x << " " << ele.dsigma_y << " "
	     "\n";
    }
    fout.close();
    std::cout << "Converted binary data to ASCII text and Wrote to text_surface.dat\n";
    //this part can be commented out
    //***********


    
    SurfaceSearcher searcher(elements);

    
    std::vector<particle> plist;
    int expected_N = 0;
    load_charm("charm.dat", plist, expected_N);

    output_oscar_augmented(plist, elements, searcher, "charm_with_dsigma_txy.dat");

    return 0;
}
