#include "predefine.h"
#include <cmath>


const double fmc_to_GeV_m1 = 5.076;


void load_charm(const std::string& filename, std::vector<particle>& plist, int& Nparticles) {

    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Error: Cannot open charm.dat file: " << filename << std::endl;
        return;
    }

    std::string line;

    for (int i = 0; i < 3; ++i) std::getline(fin, line);

    Nparticles = -1;
    std::getline(fin, line);
    {
        std::istringstream iss(line);
        std::string dummy;
        iss >> dummy >> Nparticles;
    }

    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        int idx, pid;
        double px, py, pz, E, mass;
        double x, y, eta, tau;
        double Tf, vx, vy, vz;
        double p0x, p0y, p0z;
        double weight;

        iss >> idx >> pid >> px >> py >> pz >> E >> mass
            >> x >> y >> eta >> tau >> Tf >> vx >> vy >> vz
            >> p0x >> p0y >> p0z >> weight;

//        if (std::abs(pid) != abspid) continue;

        particle p;

        p.pid = pid;
	p.p.a[1] = px;
	p.p.a[2] = py;
	p.p.a[3] = pz;
	p.p.a[0] = E;
        p.mass = mass;
	p.x.a[1] = x ; // in fm;
	p.x.a[2] = y ; // in fm;
	p.x.a[3] = eta;
	p.x.a[0] = tau ;// in fm/c;
        p.Tf = Tf;
        p.vcell = {vx, vy, vz};
        p.p0.a[1] = p0x;
	p.p0.a[2] = p0y;
	p.p0.a[3] = p0z;
	p.weight = weight;

        plist.push_back(p);
    }

    std::cout << "Read " << plist.size() << " charm particles from " << filename
              << " (expected: " << Nparticles << ")\n";
}

    
///////////////////////
void output_oscar_augmented(const std::vector<particle>& plist,
                            const std::vector<SurfaceElement>& elements,
                            const SurfaceSearcher& searcher,
                            const std::string& fname) {
    std::ofstream f(fname);
    if (!f) {
        std::cerr << "Error: Cannot open output file: " << fname << std::endl;
        return;
    }

    int Nparticles = 0;
    for (const auto& p : plist)
        if (std::abs(p.pid) == 4) Nparticles++;

    f << "OSC1997A\n";
    f << "final_id_p_x\n";
    f << "    lbt  1.0alpha   208    82   208    82   aacm  0.1380E+04        1\n";
    f << "        1  " << std::setw(10)
      << Nparticles << "    0.001    0.001    1    1       1\n";

    int i = 0;
    for (const auto& p : plist) {
        if (std::abs(p.pid) == 4) {
        const SurfaceElement* e = searcher.findClosest(p.x.x0(), p.x.x1(), p.x.x2());

	f << std::setw(10) << std::setfill(' ') << i << "  "      // particle index, i10,2x
              << std::setw(10) << std::setfill(' ') << p.pid << "  "; // particle id, i10,2x
            f << ff(p.p.x()) << "  "
              << ff(p.p.y()) << "  "
              << ff(p.p.z()) << "  "
              << ff(p.p.t()) << "  "
              << ff(p.mass) << "  "
	      << ff(p.x.x1() ) << "  "
              << ff(p.x.x2() ) << "  "
              << ff(p.x.x3() ) << "  " // p.x.x3() is eta_s
              << ff(p.x.x0() ) << "  " // p.x.x0() is tau

           //   << ff(p.x.x1() / fmc_to_GeV_m1) << "  "
           //   << ff(p.x.x2() / fmc_to_GeV_m1) << "  "
          //    << ff(p.x.x3() / fmc_to_GeV_m1) << "  " // p.x.x3() is eta_s
          //    << ff(p.x.x0() / fmc_to_GeV_m1) << "  " // p.x.x0() is tau
              << ff(p.Tf) << "  "
	      << ff(p.vcell[0] ) << "  "
              << ff(p.vcell[1] ) << "  "
	      << ff(p.vcell[2] ) << "  "
            //  << ff(p.vcell[0] * sqrt(1 - tanh(p.x.x3()) * tanh(p.x.x3()) ) ) << "  "
           //   << ff(p.vcell[1] * sqrt(1 - tanh(p.x.x3()) * tanh(p.x.x3()) ) ) << "  "
	   //   << ff(vz) << "  "   //vz = tanh(p.x.x3())
	    //  << ff(tanh(p.x.x3()) ) << "  "
              << ff(p.p0.x()) << "  "
              << ff(p.p0.y()) << "  "
              << ff(p.p0.z()) << "  "
	     // << ff(p.tau0) << "  "
	      << ff(e ? e->dsigma_t : 0.0) << "  " 
	      << ff(e ? e->dsigma_x : 0.0) << "  " 
	      << ff(e ? e->dsigma_y : 0.0) << "  "
	      << ff(p.weight) << "\n";
    }
        i++;
    }

    std::cout << "Wrote augmented charm output to " << fname << "\n";
}
