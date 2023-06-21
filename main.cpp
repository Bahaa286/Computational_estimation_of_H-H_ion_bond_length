#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

double h = 0.0001; // Interval between points for differentiation
ofstream plot1("plot1.csv"); // File for the data of the first function plot
ofstream plot2("plot2.csv"); // File for the data of the second function plot

// Potential function when A=B. Minimizable
double numerator(double x){
    return (1 - 2*x*x/3)*exp(-x) + (1+x)*exp(-2*x);
}

double denominator(double x){
    return 1 + (1 + x + x*x/3)*exp(-x);
}

double potentialFunction(double x){
    return -1 + (2/x)*(numerator(x)/denominator(x));
}

// Potential function when A=-B. Not minimizable
double numeratorB(double x){
    return -(1 - 2*x*x/3)*exp(-x) + (1+x)*exp(-2*x);
}

double denominatorB(double x){
    return 1 - (1 + x + x*x/3)*exp(-x);
}

double potentialFunctionB(double x){
    return -1 + (2/x)*(numeratorB(x)/denominatorB(x));
}

// Five point numerical differentiation formula
double fivePointDiff(double (*f)(double), double x0, double h){
    return (-25*f(x0) + 48*f(x0+h) - 36*f(x0+2*h) + 16*f(x0+3*h) -
    3*f(x0+4*h))/(12*h);
}

// The derivative of the first potential function
double derivative(double x) {
    return fivePointDiff(potentialFunction, x, h);
}

// Solve f(x)=0 using the bisection method
double solveMidPoint(double (*f)(double), double start, double end, double tol){
    double midPoint = (start+end)/2;
    double midPointOld;
    double value = f(midPoint);
    double negative=0.0, positive=0.0;
    int i=0;

    if(f(start) < 0){
        negative = start;
        positive = end;
    }else{
        positive = start;
        negative = end;
    }

    do{
        if(value < 0){
            negative = midPoint;
        }else if(value > 0){
            positive = midPoint;
        }else{
            break;
        }

        midPointOld = midPoint;
        midPoint = (positive+negative)/2;
        value =  f(midPoint);
        i++;
    }
    while (abs(midPoint-midPointOld)>tol);
    cout << i-1 << " iterations of bisection for accuracy to " << tol << endl;
    return midPoint;

}

// solve f(x)=0 using the Newton-Raphson method
double solveNewtonRaphson(double (*f)(double), double point0, double tol){
    double point = point0;
    int i = 0;
    do {
        point0 = point;
        point = point0-f(point0)/fivePointDiff(f, point0, h);
        i++;
    }
    while (abs(point-point0)>tol);
    cout << i-1 << " iterations of Newton-Raphson for accuracy to " << tol << endl;
    return point;
}

int main(){

    //cout << "Enter h: " << endl;
    //cin >> h;
    auto start1 = high_resolution_clock::now();
    double xMid = solveMidPoint(derivative, 2, 3, 0.0001);
    auto stop1 = high_resolution_clock::now();
    auto midPointDuration = duration_cast<microseconds>(stop1 - start1);

    auto start2 = high_resolution_clock::now();
    double xNewton = solveNewtonRaphson(derivative, 2, 0.0001);
    auto stop2 = high_resolution_clock::now();
    auto newtonDuration = duration_cast<microseconds>(stop2 - start2);

    cout << "x of minimal energy using the mid-point method: " << xMid << endl << "Calculated in: " << midPointDuration.count() << " microseconds" << endl;
    cout << "x of minimal energy using the Newton-Raphson method: " << xNewton << endl << "Calculated in: " << newtonDuration.count() << " microseconds" << endl;;
    cout << "Ground state energy = " << potentialFunction(xNewton) << endl;

    // Write the first function's plot data
    plot1 << "x,E" << endl;
    for (double x=0.5; x<=16; x = x+0.1) {
        plot1 << x << "," << potentialFunction(x) << endl;
    }
    plot1.close();

    // Write the second function's plot data
    plot2 << "x,E" << endl;
    for (double x=0.5; x<=16; x = x+0.1) {
        plot2 << x << "," << potentialFunctionB(x) << endl;
    }
    plot2.close();

    return 0;
}
