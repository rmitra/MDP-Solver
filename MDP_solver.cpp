#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string.h>

#include "MDP_solver.h"

using namespace std;
	
int main(int argc, char* argv[]) {
	MDP m;
	
	m.load_MDP_data(argv[1]);
	//m.display_MDP();
	
	double eph = 0.000001;

	m.value_iterations(eph);
	m.display_MDP();
	return 0;
}	
	
