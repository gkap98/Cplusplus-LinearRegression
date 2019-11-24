//
//  LinearRegressionModel.h
//  LiniarRegressionModel
//
//  Created by Gavin Kaepernick on 11/4/19.
//  Copyright © 2019 Gavin Kaepernick. All rights reserved.
//

#ifndef LinearRegressionModel_h
#define LinearRegressionModel_h

#include <vector>
using namespace std;

class LinearRegressionModel {
	
public:
	LinearRegressionModel(vector <vector<double>>& features, vector<double>& labels, double learningRate);
	double predict(vector<double>& inputFeatures);
	vector<double> yPrimeMinusY(vector<double> yPrime, vector<double> labels);
	vector<double> calculatingWeights(vector<vector<double>>& features, vector<double>& yPrimeMinusY, double learningRate);
	vector<double> yPrimes(vector<vector<double>>& features, vector<double>& labels);
	
	
private:
	vector <double> oldWeights;
	vector <double> newWeights;
	
};

#endif /* LinearRegressionModel_h */
