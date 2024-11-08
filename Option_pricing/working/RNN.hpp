#ifndef RNN_H
#define RNN_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <math.h>
#include "matrix.hpp"
using namespace std;

double random_double(const double &min, const double &max)
{
	return ((double)rand() / RAND_MAX) * (max - min) + min;
}

double mse_seq(vector<matrix> output, vector<matrix> target)
{
	int n = output.size();
	double result = 0.0;

	for (int i = 0; i < n; i++)
	{
		matrix err = output[i].minus(target[i]);

		for (int j = 0; j < err.vals.size(); j++)
			result += pow(err.vals[j], 2);
	}

	result /= n * output[0].vals.size();

	return result;
}

matrix random_matrix(const double &l, const double &r, const int &row, const int &col)
{
	matrix temp(row, col);
	for (int i = 0; i < row * col; i++)
	{
		temp.vals[i] = random_double(l, r);
	}

	return temp;
}

matrix tanh_function(matrix v)
{
	for (int i = 0; i < v.vals.size(); i++)
		v.vals[i] = tanh(v.vals[i]);

	return v;
}

matrix clip(matrix a, const double &mn, const double &mx)
{
	for (int i = 0; i < a.vals.size(); i++)
		a.vals[i] = clamp(a.vals[i], mn, mx);

	return a;
}

vector<matrix> mask_seq(vector<matrix> input_seq, int signal_size)
{
	int n = input_seq.size();
	vector<matrix> res = input_seq;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < signal_size; ++j)
		{
			res[i].vals[j] = 1.0;
		}
	}

	return res;
}

vector<matrix> convert_input_masks_to_hidden_masks(const vector<matrix> &input_masks, const int &hidden_size)
{
	int n = input_masks.size();
	vector<matrix> hidden_masks(n);

	for (int i = 0; i < n; ++i)
	{
		int rows = hidden_size;
		int cols = 1;
		matrix mask(rows, cols);

		double mask_value = all_of(input_masks[i].vals.begin(), input_masks[i].vals.end(),
										[](double v) { return v == 1.0; })
								? 1.0
								: 0.0;

		for (int j = 0; j < rows * cols; ++j)
		{
			mask.vals[j] = mask_value;
		}

		hidden_masks[i] = mask;
	}

	return hidden_masks;
}

class rnn
{
  public:
	int hidden_size;
	int signal_size;
	int seq_length;
	double learning_rate;
	matrix U;
	matrix V;
	matrix W;
	matrix b;
	matrix c;
	string message;

	rnn(const int &h_s, const int &s_s, const int &s_l, const double &l_r)
	{
		hidden_size = h_s;
		signal_size = s_s;
		seq_length = s_l;
		learning_rate = l_r;

		U = random_matrix(-1 * sqrt(1.0 / double(signal_size)), sqrt(1.0 / double(signal_size)), hidden_size, signal_size);
		V = random_matrix(-1 * sqrt(1.0 / double(hidden_size)), sqrt(1.0 / double(hidden_size)), signal_size, hidden_size);
		W = random_matrix(-1 * sqrt(1.0 / double(hidden_size)), sqrt(1.0 / double(hidden_size)), hidden_size, hidden_size);
		matrix b_(hidden_size, 1);
		matrix c_(signal_size, 1);
		b = b_;
		c = c_;
	}

	vector<vector<matrix>> forward(vector<matrix> inputs, matrix h_0, vector<matrix> input_masks, vector<matrix> hidden_masks)
	{
		int sz = inputs.size();
		vector<matrix> X(sz), H(sz), O(sz);

		for (int i = 0; i < sz; i++)
		{
			X[i] = inputs[i];

			matrix h;

			if (i)
				h = H[i - 1];
			else
				h = h_0;

			H[i] = tanh_function(U.dot(X[i]).add(W.dot(h)).add(b));
			H[i] = H[i].multiply_element(hidden_masks[i]);

			O[i] = V.dot(H[i]).add(c);
			O[i] = O[i].multiply_element(input_masks[i]);
		}

		return {X, H, O};
	}

	void backward(vector<matrix> X, vector<matrix> H, vector<matrix> O, vector<matrix> targets, matrix h_0, vector<matrix> input_masks, vector<matrix> hidden_masks)
	{
		matrix dU(hidden_size, signal_size);
		matrix dW(hidden_size, hidden_size);
		matrix dV(signal_size, hidden_size);
		matrix db(hidden_size, 1);
		matrix dc(signal_size, 1);
		matrix dhnext(hidden_size, 1);

		for (int i = seq_length - 1; i >= 0; i--)
		{
			matrix dy = O[i].minus(targets[i]).multiply_scalar(2.0 / double(signal_size));
			dy = dy.multiply_element(input_masks[i]);

			dV = dV.add(dy.dot(H[i].transpose()));
			dc = dc.add(dy);

			matrix dh = V.transpose().dot(dy).add(dhnext);
			dh = dh.multiply_element(hidden_masks[i]);

			matrix dhrec = H[i].multiply_element(H[i]).negative().element_add(1.0).multiply_element(dh);
			db = db.add(dhrec);

			dU = dU.add(dhrec.dot(X[i].transpose()));
			if (i)
				dW = dW.add(dhrec.dot(H[i - 1].transpose()));
			else
				dW = dW.add(dhrec.dot(h_0.transpose()));

			dhnext = W.transpose().dot(dhrec);
		}

		dU = clip(dU, -5.0, 5.0);
		dW = clip(dW, -5.0, 5.0);
		dV = clip(dV, -5.0, 5.0);
		db = clip(db, -5.0, 5.0);
		dc = clip(dc, -5.0, 5.0);

		U = U.minus(dU.multiply_scalar(learning_rate));
		W = W.minus(dW.multiply_scalar(learning_rate));
		V = V.minus(dV.multiply_scalar(learning_rate));
		b = b.minus(db.multiply_scalar(learning_rate));
		c = c.minus(dc.multiply_scalar(learning_rate));
	}

	void train(vector<vector<matrix>> input_data, vector<vector<matrix>> targets, int epochs)
	{
		matrix h0 = random_matrix(-1 * sqrt(1.0 / double(hidden_size)), sqrt(1.0 / double(hidden_size)), hidden_size, 1);
		int n = input_data.size();

		for (int t = 0; t < epochs; ++t)
		{
			double error = 0.0;

			for (int i = 0; i < n; ++i)
			{
				vector<matrix> inputs = input_data[i];

				vector<matrix> input_masks = mask_seq(inputs, signal_size);

				vector<matrix> hidden_masks = convert_input_masks_to_hidden_masks(input_masks, hidden_size);

				vector<vector<matrix>> XHO = forward(inputs, h0, input_masks, hidden_masks);

				vector<matrix> target = targets[i];

				error += mse_seq(XHO[2], target);

				backward(XHO[0], XHO[1], XHO[2], target, h0, input_masks, hidden_masks);
			}

			error /= double(n);

            ostringstream oss;
			oss << "epoch " << t + 1 << "/" << epochs << "-----------------"
				 << "mse : " << error << endl;
            cout << oss.str();
            message = message + oss.str();
		}
	}

	void save_weights(const string& filename) {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        // Write U
        file.write(reinterpret_cast<const char*>(&U.rows), sizeof(int));
        file.write(reinterpret_cast<const char*>(&U.cols), sizeof(int));
        file.write(reinterpret_cast<const char*>(U.vals.data()), U.vals.size() * sizeof(double));

        // Write V
        file.write(reinterpret_cast<const char*>(&V.rows), sizeof(int));
        file.write(reinterpret_cast<const char*>(&V.cols), sizeof(int));
        file.write(reinterpret_cast<const char*>(V.vals.data()), V.vals.size() * sizeof(double));

        // Write W
        file.write(reinterpret_cast<const char*>(&W.rows), sizeof(int));
        file.write(reinterpret_cast<const char*>(&W.cols), sizeof(int));
        file.write(reinterpret_cast<const char*>(W.vals.data()), W.vals.size() * sizeof(double));

        // Write b
        file.write(reinterpret_cast<const char*>(&b.rows), sizeof(int));
        file.write(reinterpret_cast<const char*>(&b.cols), sizeof(int));
        file.write(reinterpret_cast<const char*>(b.vals.data()), b.vals.size() * sizeof(double));

        // Write c
        file.write(reinterpret_cast<const char*>(&c.rows), sizeof(int));
        file.write(reinterpret_cast<const char*>(&c.cols), sizeof(int));
        file.write(reinterpret_cast<const char*>(c.vals.data()), c.vals.size() * sizeof(double));

        // Write message
        const char* msg_data = message.c_str();
        uint32_t msg_size = static_cast<uint32_t>(message.size());
        file.write(reinterpret_cast<const char*>(&msg_size), sizeof(uint32_t));
        file.write(msg_data, msg_size);

        file.close();
        cout << "Weights saved to " << filename << endl;
    }

    void load_weights(const string& filename) {
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        // Read U
        int rows, cols;
        file.read(reinterpret_cast<char*>(&rows), sizeof(int));
        file.read(reinterpret_cast<char*>(&cols), sizeof(int));
        U = matrix(rows, cols);
        file.read(reinterpret_cast<char*>(U.vals.data()), U.vals.size() * sizeof(double));

        // Read V
        file.read(reinterpret_cast<char*>(&rows), sizeof(int));
        file.read(reinterpret_cast<char*>(&cols), sizeof(int));
        V = matrix(rows, cols);
        file.read(reinterpret_cast<char*>(V.vals.data()), V.vals.size() * sizeof(double));

        // Read W
        file.read(reinterpret_cast<char*>(&rows), sizeof(int));
        file.read(reinterpret_cast<char*>(&cols), sizeof(int));
        W = matrix(rows, cols);
        file.read(reinterpret_cast<char*>(W.vals.data()), W.vals.size() * sizeof(double));

        // Read b
        file.read(reinterpret_cast<char*>(&rows), sizeof(int));
        file.read(reinterpret_cast<char*>(&cols), sizeof(int));
        b = matrix(rows, cols);
        file.read(reinterpret_cast<char*>(b.vals.data()), b.vals.size() * sizeof(double));

        // Read c
        file.read(reinterpret_cast<char*>(&rows), sizeof(int));
        file.read(reinterpret_cast<char*>(&cols), sizeof(int));
        c = matrix(rows, cols);
        file.read(reinterpret_cast<char*>(c.vals.data()), c.vals.size() * sizeof(double));

        // Read the custom message
        uint32_t msg_size;
        file.read(reinterpret_cast<char*>(&msg_size), sizeof(uint32_t));
        message.resize(msg_size);
        file.read(&message[0], msg_size);

        file.close();
        cout << "Weights loaded from " << filename << endl;
        cout << "Message: " << endl << message << endl;
    }
};

#endif
