#ifndef MDP_SOLVER
#define MDP_SOLVER

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class MDP {
	public:
		int S;	/* num of states */
		int A;	/* num of actions */
		vector <double> V;
		vector < vector < vector <double> > > R;
		vector < vector < vector <double> > > T;
		vector <int> P; /* Policy */
		double Gamma;

		void load_MDP_data(char *);
		void display_MDP();
		void value_iterations(double);
	private:
		double compute_max_value(int);
};

void MDP::load_MDP_data(char* filename) {
	fstream fp;

	fp.open(filename, fstream::in);
	fp.is_open();

	fp>>S;
	fp>>A;

	V = vector<double>(S);
	R = vector < vector < vector<double> > >(S);
	T = vector < vector < vector<double> > >(S);

	for (int s1 = 0; s1 < S; s1++) {
		R[s1] = vector< vector <double> >(A);

		for (int a = 0; a < A; a++) {
			R[s1][a] = vector <double>(S);

			for (int s2 = 0; s2 < S; s2++) {
				fp>>R[s1][a][s2];
			}
		}
	}

	for (int s1 = 0; s1 < S; s1++) {
		T[s1] = vector< vector <double> >(A);

		for (int a = 0; a < A; a++) {
			T[s1][a] = vector<double>(S);

			for (int s2 = 0; s2 < S; s2++) {
				fp>>T[s1][a][s2];
			}
		}
	}

	fp>>Gamma;

	fp.close();

	/* Initialising V's and P's*/
	V = vector <double>(S,0.0);
	P = vector <int>(S);
}

void MDP::display_MDP() {

	// cout<<"Number of states "<<S<<"\n";
	// cout<<"Number of actions "<<A<<"\n";

	/*cout<<"Reward Matrix\n";
	for (int s1 = 0; s1 < S; s1++) {
		for (int a = 0; a < A; a++) {
			for (int s2 = 0; s2 < S; s2++) {
				cout<<"("<<s1<<" "<<a<<" "<<s2<<") "<<R[s1][a][s2]<<"  ";
			}
			cout<<"\n";
		}
		cout<<"\n\n";
	}

	cout<<"Transition Matrix\n";
	for (int s1 = 0; s1 < S; s1++) {
		for (int a = 0; a < A; a++) {
			for (int s2 = 0; s2 < S; s2++) {
				cout<<"("<<s1<<" "<<a<<" "<<s2<<") "<<T[s1][a][s2]<<"  ";
			}
			cout<<"\n";
		}
		cout<<"\n\n";
	}*/

	// cout<<"Value Functions\n";

	for(int s = 0; s < S; s++)
		printf("%lf %d\n",V[s],P[s]);

	// cout<<"Gamma "<<Gamma<<"\n";
}

double MDP::compute_max_value(int s) {
	double max_value = -9999999.0;

	for(int a = 0; a < A; a++) {
		double exp_value = 0.0;
		
		for (int sp = 0; sp < S; sp++){
			exp_value = exp_value + T[s][a][sp] * (R[s][a][sp] + Gamma * V[sp]);
		}

		if (exp_value > max_value) {
			max_value = exp_value;
			P[s] = a;
		}
	}

	V[s] = max_value;
	return max_value;
}


void MDP::value_iterations(double eph) {

	bool converged = false;
	double max_diff;
	int itr = 0;
	while (!converged) {
		max_diff = -1.0;

		for (int s = 0; s < S; s++) {
			double old_value = V[s];
			double new_value = compute_max_value(s);  /* V vector is updated with the new value inside the function */
			
			if (abs(new_value - old_value) > max_diff) {
				max_diff = abs(new_value - old_value);
			}
		}

		// cout<<"max diff "<<max_diff<<"\n";
		if (max_diff <= eph) {
			converged = true;
		}			

		itr++;
	}

	//cout<<"Total Iterations "<<itr<<"\n";

}

#endif
