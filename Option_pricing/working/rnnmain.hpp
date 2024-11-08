#ifndef RNNMAIN_H
#define RNNMAIN_H

#include "RNN.hpp"
#include "matrix.hpp"
#include <fstream>
#include <sstream>
#include <tuple>
using namespace std;

vector<matrix> neg_vec_matrix(vector<matrix> vm)
{
	for (int i = 0; i < vm.size(); i++)
		vm[i] = vm[i].negative();

	return vm;
}

vector<matrix> normalized_seq(vector<matrix> seq)
{
	for (int i = 0; i < seq.size(); i++)
	{
		vector<double> temp = seq[i].vals;

		double minVal = *min_element(temp.begin(), temp.end());
		double maxVal = *max_element(temp.begin(), temp.end());

		if (maxVal == minVal)
			maxVal += 1e-9;

		for (int j = 0; j < temp.size(); j++)
			temp[j] = (temp[j] - minVal) / (maxVal - minVal);

		seq[i].vals = temp;
	}

	return seq;
}

int trainModel(int starty, int endy, int _seq_length, int _hidden_size, double _learning_rate, int _epoch, string _filename)
{
	vector<matrix> vm;
	string line, cell;

	vector<string> files;
	for (int i = starty; i < endy; i++)
	{
		files.push_back("completeData/20" + to_string(i) + "completeData.csv");
	}

	for (size_t i = 0; i < files.size(); i++)
	{
		ifstream data(files[i]);
		if (!data.is_open())
			return 1;
		getline(data, line);
		while (getline(data, line))
		{
			istringstream iss(line);
			vector<double> sv;
			while (getline(iss, cell, ','))
			{
				sv.push_back(stod(cell));
			}
			matrix mat(1, 6706);
			mat.vals = sv;
			mat = mat.transpose();
			vm.push_back(mat);
		}
		data.close();
	}

	vm = normalized_seq(vm);

    vector<vector<matrix>> sequences;
    int seq_length = _seq_length;

    for(int i = 0; i < vm.size() - seq_length; i += seq_length){
        vector<matrix> temp;

        for(int j = i; j < i + seq_length; j++)
            temp.push_back(vm[j]);

        sequences.push_back(temp);
    }

    cout<<sequences.size()<<" sequences"<<endl;

    int hidden_size = _hidden_size;
    int signal_size = 6706;
    double learning_rate = _learning_rate;
    matrix h0 = random_matrix(-1 * sqrt(1.0 / double(hidden_size)), sqrt(1.0 / double(hidden_size)), hidden_size, 1);

    rnn tra(hidden_size, signal_size, seq_length, learning_rate);

    int epoch = _epoch;
    vector<vector<matrix>> inputs(sequences.begin(), sequences.end() - 1);
    vector<vector<matrix>> outputs(sequences.begin() + 1, sequences.end());
    tra.train(inputs, outputs, epoch);

    tra.save_weights(_filename);

	return 0;
}

tuple<vector<vector<matrix>>, vector<double>> load(int starty, int endy, string _filename) {
    rnn my_rnn(0,0,0,0);
    my_rnn.load_weights(_filename);
    vector<vector<matrix>> predictions;
    vector<double> msev;
/*Haven't been tested yet because we don't have time. Uncomment to use.
    vector<matrix> vm;
	string line, cell;

	vector<string> files;
	for (int i = starty; i < endy; i++)
	{
		files.push_back("completeData/20" + to_string(i) + "completeData.csv");
	}

	for (size_t i = 0; i < files.size(); i++)
	{
		ifstream data(files[i]);
		if (!data.is_open())
			return make_tuple(predictions, msev);
		getline(data, line);
		while (getline(data, line))
		{
			istringstream iss(line);
			vector<double> sv;
			while (getline(iss, cell, ','))
			{
				sv.push_back(stod(cell));
			}
			matrix mat(1, 6706);
			mat.vals = sv;
			mat = mat.transpose();
			vm.push_back(mat);
		}
		data.close();
	}

	vm = normalized_seq(vm);

    vector<vector<matrix>> sequences;
    int seq_length = my_rnn.seq_length;

    for(int i = 0; i < vm.size() - seq_length; i += seq_length){
        vector<matrix> temp;

        for(int j = i; j < i + seq_length; j++)
            temp.push_back(vm[j]);

        sequences.push_back(temp);
    }

    cout<<sequences.size()<<" sequences"<<endl;

    vector<vector<matrix>> input_data(sequences.begin(), sequences.end() - 1);
    vector<vector<matrix>> targets(sequences.begin() + 1, sequences.end());

    matrix h0 = random_matrix(-1 * sqrt(1.0 / double(my_rnn.hidden_size)), sqrt(1.0 / double(my_rnn.hidden_size)), my_rnn.hidden_size, 1);

    for (int i = 0; i < input_data.size(); ++i) {
        vector<matrix> input_masks = mask_seq(input_data[i], my_rnn.signal_size);
        vector<matrix> hidden_masks = convert_input_masks_to_hidden_masks(input_masks, my_rnn.hidden_size);
        predictions = my_rnn.forward(input_data[i], h0, input_masks, hidden_masks);

        double mse = mse_seq(predictions[2], targets[i]);
        msev.push_back(mse);
        cout << "MSE for sequence " << i << ": " << mse << endl;
    }
*/
    return make_tuple(predictions, msev);
}

#endif
