//
//  main.cpp
//  LinearRegression -Real-
//
//  Created by Gavin Kaepernick on 11/6/19.
//  Copyright © 2019 Gavin Kaepernick. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "LinearRegressionModel.h"
using namespace std;

//-- ******************************
//-- MAIN
//-- ******************************

int main(int argc, const char * argv[]) {
	cout << "------------------------------" << endl;
	cout << "Liniar Regression Models" << endl;
	cout << "------------------------------" << endl;
	
	
	//-- Test 1
	{
		vector<vector<double>> features = { {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0} };
		vector<double> labels = { 3.0, 2.0, 1.0 };

		LinearRegressionModel model(features, labels, .1);

		vector<double> unknownInput = { 0.0, 4.0 };

		double predictedValue = model.predict(unknownInput); //should be about 2.0

		cout << "The predicted value is " << predictedValue << endl;
	}
	//-- Test 2
	{
//			vector<vector<double>> features = { { 1.0, 2.0 }, { 3.0, 3.0 },{ 4.0, 4.0 }};
//			vector<double> labels = { 3.0, 1.0, 0.0 };
//
//			LinearRegressionModel model(features, labels, .1); //2.9
//
//			vector<double> unknownInput = { 1.0, 1.0 };
//
//			double predictedValue = model.predict(unknownInput);
//
//			cout << "The predicted value is " << predictedValue << endl;
		}
	//-- Test 3
	{
//		vector<vector<double>> features = { { 6.2 },{ 2.8 },{ 8.3 },{ 1.5 },{ 2.0 },{ 3.7 },{ 4.4 },{ 9.4 },{ 6.9 } };
//		vector<double> labels = { 19.0, 9.0, 40.0, 7.0, 20.0, 17.0, 27.0, 44.0, 30.0};
//
//		LinearRegressionModel model(features, labels, .01); //-13.1 with a learning rate of .01
//
//		vector<double> unknownInput = { -4.0 };
//
//		double predictedValue = model.predict(unknownInput);
//
//		cout << "The predicted value is " << predictedValue << endl;
	}
	return 0;
}

//-- ******************************
//-- FUNCTIONS
//-- ******************************
LinearRegressionModel::LinearRegressionModel(vector<vector<double>>& features, vector<double>& labels, double learningRate) {
	
	vector<double> yPrimeMinusYVector(labels.size(), 0.0);
	
	//-- ***************************
	//-- INITIALIZERS
	//-- ***************************
	//-- Inserting x0 with a value of 1 into the features
	for (int i = 0; i < features.size(); i++) {
		features[i].insert(features[i].begin(), 1.0);
	}
	//-- Initiallizing yPrime with 0.0
	vector <double> yPrime (labels.size(), 0.0);
	
	//-- Inserting 0's for the starting weights
	oldWeights = vector<double> (features[0].size(), 0);
	newWeights = vector<double> (features[0].size(), 0);
	
	//-- ***************************
	//-- CALCULATION STEPS
	//-- ***************************
	bool calculating = true;
	int iterations = 1;
	while (calculating == true) {
		
		//-- STEP 1 - Calculating Y Prime - Y
		yPrimeMinusYVector = yPrimeMinusY(yPrime, labels);
		
		//-- STEP 2 - Calculate weights from summing Y Prime - Y * features
		calculatingWeights(features, yPrimeMinusYVector, learningRate);
		
		//-- STEP 3 - setting new Y Prime
		yPrime = yPrimes(features, newWeights);
		
		//-- STEP 4 - Print the iteration with the weights at that current moment in time
		cout << "Iteration: " << iterations << endl;
		cout << "---------------" << endl;
		for (int i = 0; i < newWeights.size(); i++) {
			cout << "W" << i << ": " << newWeights[i] << endl;
		}
		cout << endl;
		//-- STEP 5 - Check to see if the difference is less than .0001
		for (int i = 0; i < newWeights.size(); i++) {
			if (abs(newWeights[i] - oldWeights[i]) > .0001) {
				break;
			}
			else {
				calculating = false;
			}
		}
		//-- STEP 6 (conditional) - increment and prepare for next iteration
		iterations++;
		oldWeights = newWeights;
	}
}


double LinearRegressionModel::predict(vector<double>& inputFeatures) {
	double retVal = 0;
	inputFeatures.insert(inputFeatures.begin(), 1.0);
	
	for (int i = 0; i < newWeights.size(); i++) {
		retVal += (newWeights[i] * inputFeatures[i]);
	}
	return retVal;
}

vector<double> LinearRegressionModel::yPrimes(vector<vector<double>>& features, vector<double>& weights) {
	vector<double> yPrimes (features.size(), 0.0);
	for (int i = 0; i < features.size(); i++) {
		for (int k = 0; k < weights.size(); k++) {
			yPrimes[i] += weights[k] * features[i][k];
		}
	}
	return yPrimes;
}
vector<double> LinearRegressionModel::yPrimeMinusY(vector<double> yPrime, vector<double> labels) {
	
	//-- Initiallizing and calculating Y Prime - Y
	vector <double> yPrimeMinusY(labels.size(), 0.0);
	for (int i = 0; i < labels.size(); i++) {
		yPrimeMinusY[i] = yPrime[i] - labels[i];
	}
	return yPrimeMinusY;
}
vector<double> LinearRegressionModel::calculatingWeights(vector<vector<double>>& features, vector<double>& yPrimeMinusY, double learningRate) {
	//-- Multiplying
	for (int i = 0; i < newWeights.size(); i++) {
		double sum = 0;
		for (int k = 0; k < features[i].size(); k++) {
			sum += (features[k][i] * yPrimeMinusY[k]);
		}
		newWeights[i] = (oldWeights[i] - (learningRate * (sum / features.size())));
	}
	return newWeights;
}
