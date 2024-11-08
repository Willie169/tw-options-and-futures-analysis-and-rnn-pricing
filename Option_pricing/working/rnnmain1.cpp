#include "rnnmain.hpp"

int main() {
    cout << "Training Model: 15 21 10 100 0.01 5" << endl;
	int a = trainModel(15, 21, 10, 100, 0.01, 5, "trainedModel_15_21_10_100_0.01_5");
    tuple<vector<vector<matrix>>, vector<double>> b = load(21, 23, "trainedModel_15_21_10_100_0.01_5");
	return 0;
}
