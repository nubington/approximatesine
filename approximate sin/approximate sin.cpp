
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <math.h>
#include <time.h>

using namespace std;

double factorial(int n);

double wrapAngle(double angle);

bool parseDouble(string string, double& result);

double sin(double theta, double& error);

const double PI = atan(1.0)*4;

int main()
{
	double theta, error;
	int degree = 169;
	string input;

	while (true)
	{
		cout << "sin(x),  x = ";
		cin >> theta;

		// start time
		time_t start = clock();

		double _sin = sin(theta, error);

		// time elapsed
		double timeElapsed = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);

		cout << endl << setprecision(numeric_limits<double>::digits10) << _sin << ", |error| <= " << abs(error)
			<< ", " << timeElapsed * 1000.0 << " ms" << endl << endl;
	}
}

double factorial(int n)
{
	// if n is 0, return 1
	if (!n)
		return 1;

	double result = 1;

	for (int i = 2; i <= n; i++)
		result *= i;

	return result;
}

double wrapAngle(double angle)
{
	double twoPi = 2.0 * PI;

    return angle - twoPi * floor( angle / twoPi );
}

double sin(double theta, double& error)
{
	theta = wrapAngle(theta);

	double sin = 0;
	int n;

	for (n = 0; (2*n + 1) <= 169; n++)
	{
		sin += (pow(-1.0, n) * pow(theta, 2*n + 1)) / factorial(2*n + 1);
	}

	error = (pow(-1.0, n + 1) * pow(theta, 2*(n + 1) + 1)) / factorial(2*(n + 1) + 1);

	return sin;
}

bool parseDouble(string string, double& result)
{
	bool dot = false;
	double number = 0, power = 1;

	char numLength = string.length();
	char decimalPlace = numLength;
	char neg = (string[0] == '-');

	for (int i = neg; i < numLength; i++)
	{
		if (string[i] == '.')
		{
			decimalPlace = i;
			if (!dot)
				dot = true;
			else
				return false;
		}
	}

	int decimalAmount = 0;

	if (decimalPlace >= neg)
		decimalAmount = numLength - (decimalPlace + 1);

	for (int i = 0; i < decimalAmount; i++)
		power /= 10;

	for (int i = numLength - 1; i >= neg; i--)
	{
		if (string[i] == '.')
			continue;

		char num = string[i] - 48;

		if (num < 0 || num > 9)
			return false;

		number += num * power;

		power *= 10;
	}

	if (neg)
		result = -number;
	else
		result = number;

	return true;
}