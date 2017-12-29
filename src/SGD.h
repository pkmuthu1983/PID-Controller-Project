#ifndef SGD_H
#define SGD_H

using namespace std;

class SGD {
	int cur_ts;
	int train_length;
	int state;
	unsigned int numparams;
	double delta_k;
	double cost_till_i;
	vector<double> costs_incr;
	vector<double> cur_params;
	vector<double> tmp_params;
	vector<double> delta;
public:
	double k_p;
	double k_d;
	double k_i;
	bool use_new_values;

	SGD(vector<double>, int, vector<double>);
	void reset_sgd(vector<double>);
	void update(double);
	void update_params();
	void copy_params();
};


#endif

