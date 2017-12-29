#include <iostream>
#include <vector>
#include "SGD.h"

SGD::SGD(vector<double> init_values,
    int train_len, vector<double> del) {

	train_length = train_len;

	for (unsigned int i=0; i<=init_values.size(); i++){
		costs_incr.push_back(0);
	}
	cur_params.push_back(0);
	delta.push_back(0);
	tmp_params.push_back(0);
	for (unsigned int i=0; i<init_values.size(); i++){
		cur_params.push_back(init_values[i]);
		tmp_params.push_back(init_values[i]);
		delta.push_back(del[i]);
	}
	k_p = 0, k_d = 0, k_i=0;
	use_new_values = false;
	cost_till_i = 0;
	state = 0;
	numparams = init_values.size();
	copy_params();
	cur_ts = 0;
}

void SGD::update(double error_i) {
	cur_ts++;
	if (cur_ts >= train_length/2)
		cost_till_i += error_i * error_i;

	if ((cur_ts % train_length) == 0) {
		costs_incr[state] = cost_till_i;
		cost_till_i = 0;

#ifdef DEBUG_SGD
		cout << "SGD DEBUG  Train iter:" << cur_ts/train_length << ", state: " << state << ", COST: " << costs_incr[state] << ", kp: " << k_p << ", ki: " << k_i << ", kd" << k_d << endl;
#endif
		update_params();
		use_new_values = true;
	} else {
		use_new_values = false;
	}
}

void SGD::update_params() {
	unsigned int next_state = state + 1;
	bool increase = false;
	unsigned int i;

	if (next_state > numparams) {
		for (i=1; i<=numparams; i++) {
			increase = (costs_incr[i] > costs_incr[0]);
			// change_i = learn_rate * ((costs_incr[i] - costs_incr[0])/delta[i]);
			// change_i = ( (change_i > 0) ? min(change_i, abs(delta[i])):max(change_i, -abs(delta[i])) );

			if (delta[i] > 0 && increase) {
				delta[i] = -1 * delta[i];
			} else if (delta[i] < 0 && increase) {
				delta[i] = -1 * delta[i];
				delta[i] *= 0.9;
			} else {
				cur_params[i] = cur_params[i] + delta[i];
				delta[i] *= 1.1;
			}
			tmp_params[i] = cur_params[i];
		}

		state = 0;
		for (i=0; i<=numparams; i++){
			costs_incr[i] = 0;
		}

	} else {
		for (i=1; i<= numparams; i++){
			if (next_state == i)
				tmp_params[i] = cur_params[i] + delta[i];
			else
				tmp_params[i] = cur_params[i];

		}
		state = next_state;
	}
	copy_params();
}

void SGD::copy_params(){
	k_p = tmp_params[1];
	k_i = tmp_params[2];
	k_d = tmp_params[3];
}
