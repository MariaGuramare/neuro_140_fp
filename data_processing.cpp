#include <iostream> 
#include <fstream>
#include <sstream>
#include <climits>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <random>
#include <list>
#include <tuple>
#include <string>
#include <math.h>
#include <string.h>
using namespace std;

// global variable & engines
float sample_percentage = 0.2;
random_device rd;  
mt19937 gen(rd()); 


// convex hull calculation 
double convex_hull() {
	//TO DO
	return 1;
}

// random dstance sampling
double sample_dist(vector<vector<float> > *vec) {
	//cout << "sample fct" << endl;
	double avg = 0;
	uniform_int_distribution<> dis(0, vec->size() - 1);
	int sample_size = sample_percentage * (vec->size());
	for (int i = 0; i < sample_size; i++) {
		int elt_1 = dis(gen);
		int elt_2 = dis(gen);
		//cout << "elt 1 " << elt_1 << ", elt 2 " << elt_2 << endl;
		vector<float> pt_1 = vec->at(elt_1);
		vector<float> pt_2 = vec->at(elt_2);
		double distance = pow((pt_2.at(0) - pt_1.at(0)), 2) + pow((pt_2.at(1) - pt_1.at(1)), 2) + pow((pt_2.at(2) - pt_1.at(2)), 2);
		avg += sqrt(distance);
	}
	//cout << "returned smp fct" << endl;
	return (avg/100);
}


// usage : ./data_processing infile infile_names num_prts outfile_stats
int main(int argc, char* argv[]) {

	// open in & out files
	ifstream datafile(argv[1]);
	ifstream names(argv[2]);
	int num_prots = stoi(argv[3]);
	ofstream data, coords;
	data.open(argv[4], fstream::app);
	string line, prot_name;

	// read line by line
	char eof[] = "EOF";
	while (getline(datafile, line)) {
		// new molecule
		char new_prot[] = "new prot";
		if (strcmp(line.c_str(), new_prot) == 0) {

			// open outfile to write coordinates
			getline(names, prot_name);
			cout << prot_name << endl;
			coords.open(prot_name);
			
			vector<vector<float> > prot;
			char end_of_prot[] = "end prot";
			// get 3D coordinates for each amino acid
			getline(datafile, line);
			while (strcmp(end_of_prot, (line.c_str())) != 0) {
				vector<float> new_point;
				for (int i = 0; i < 20; i++) {
					if (i > 0 && i < 4) {
						getline(datafile, line, '>');
						getline(datafile, line, '<');
						cout << "line " << i << " : " << line << endl;
						new_point.push_back(stof(line));
						coords << line << " ";
						getline(datafile, line, '>');
					}
					else {getline(datafile, line);}
				}
				coords << endl;
				prot.push_back(new_point);
				getline(datafile, line);
			}
			// have all coordinates --> calculate
			//double cv = convex_hull(prot);
			string cv = "NULL";
			cout << "1." << endl;
			double sd = sample_dist(&prot);
			data << sd << " " << cv << endl;
			coords.close();
		}
	}
}











