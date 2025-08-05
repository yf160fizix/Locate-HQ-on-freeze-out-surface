#ifndef PREDEFINE_H
#define PREDEFINE_H

#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "lorentz.h"
#include "SurfaceReader.h"
#include "SurfaceSearcher.h"

extern const double fmc_to_GeV_m1;

struct particle{
	// mass, x, p, t, all in units of [GeV^a]
	int pid, col, acol;
	bool charged;
	double mass, weight, tau0, Q0, Q00, tf_lab;
	bool is_virtual;

	double T0, mfp0, Tf; // production temperature, local mfp
	coordinate x0; // production location
	coordinate x; // current location
	fourvec p0; // production momentum, after each radiation
	fourvec p; // current momentum
        fourvec mother_p;

	std::vector<std::vector<particle> > radlist;
	std::vector<double> vcell;

};


// Fortran style float format
class ff {
public:
    ff(double x): value(x) {}
    const double value;
	friend std::ostream & operator<< (std::ostream & stream, const ff & x) {
		// So that the log does not scream
		if (x.value == 0.) {
		    stream << "0.000000E+00";
		    return stream;
		}
		int exponent = floor(log10(std::abs(x.value)));
		double base = x.value / pow(10, exponent);
		// Transform here
		base /= 10;
		exponent += 1;
		if (base >= 0){
			std::stringstream buff;
			buff << std::setw(8) << std::setprecision(6);
			buff << std::fixed << base;
			stream << std::setw(8) << buff.str();
		}
		else{
			std::stringstream buff;
			buff << std::setw(8) << std::setprecision(6);
			buff << std::fixed << base;
			//Checking if we have a leading minus sign
			std::string newbase = "-" + buff.str().substr(2, buff.str().size()-1);
			stream << std::setw(8) << newbase;
		}

		if (exponent >= 0) stream << "E+" << std::setw(2) << std::setfill('0') << exponent;
		else stream << "E-" << std::setw(2) << std::setfill('0') << std::abs(exponent);
		return stream;
	}
};

void load_charm(const std::string& filename,
                std::vector<particle>& plist,
		int& Nparticles);

void output_oscar(const std::vector<particle> plist,
                  int abspid, std::string fname);

void output_oscar_augmented(const std::vector<particle>& plist,
                            const std::vector<SurfaceElement>& elements,
                            const SurfaceSearcher& searcher,
                            const std::string& fname);
#endif
