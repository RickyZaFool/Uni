#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <TMinuit.h>

using namespace std;

vector<double> data;

void fcn(int &npar, double *, double &f, double *par, int) {
    double alpha = par[0];
    double beta  = par[1];

    double norm = 0;
    for (double x : data)
        norm += 1 + alpha * x + beta * x * x;

    double nll = 0;
    for (double x : data) {
        double fx = 1 + alpha * x + beta * x * x;
        if (fx <= 0) {
            f = 1e10; // Avoid log of non-positive value
            return;
        }
        nll -= log(fx / norm);
    }

    f = nll;
}


int main() {
    ifstream file("Es8Data.dat");
    double x;
    while (file >> x) data.push_back(x);

    TMinuit *gMinuit = new TMinuit(2);
    gMinuit->SetFCN(fcn);

    gMinuit->DefineParameter(0, "alpha", 0.0, 0.01, -10, 10);
    gMinuit->DefineParameter(1, "beta",  0.0, 0.01, -10, 10);

    gMinuit->Migrad();

    double alpha, beta, err_alpha, err_beta;
    gMinuit->GetParameter(0, alpha, err_alpha);
    gMinuit->GetParameter(1, beta,  err_beta);

    double cov[4];
    gMinuit->mnemat(cov, 2);

    double corr = cov[1] / sqrt(cov[0] * cov[3]);

    double gamma = 3 * alpha - 2 * beta;
    double sigma_gamma = sqrt(9 * cov[0] + 4 * cov[3] - 12 * cov[1]);

    cout << "alpha = " << alpha << " ± " << err_alpha << endl;
    cout << "beta  = " << beta  << " ± " << err_beta  << endl;
    cout << "corr(alpha, beta) = " << corr << endl;
    cout << "gamma = " << gamma << " ± " << sigma_gamma << endl;

    return 0;
}