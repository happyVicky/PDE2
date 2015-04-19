#include <iostream>
#include <vector>

using namespace std;

void calculate_vector_exp(vector<vector<double> > A, vector<double> w_old, 
			 vector<double>& w_new, vector<double> d, int row, int col) {
                
        double element = 0;
        double w_element;
        for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                        element = element+A[i][j]*w_old[j];
                }
                w_element = element+d[i];
                w_new[i]=(w_element);
                element = 0;
        }

}


int main()
{
	int row = 5;
	int col = 5;
	double lambda = 0.3;
	vector<vector<double> > A;
	A.resize(row);
        for(int i = 0; i < col; i++) {
                A[i].resize(col,0.0);
        }
        for(int i = 0; i < row; i++) {
                A[i][i] = 1-2*lambda;
        }
        for(int i = 0; i < row-1; i++) {
                A[i][i+1] = lambda;
                A[i+1][i] = lambda;
        }

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			cout << "A[" << i << "][" << j << "] " << A[i][j] << endl; 
		}
	}


	vector<double> w_old;
	w_old.resize(row);
	w_old[0] = 0.1;
	w_old[1] = 0.2;
	w_old[2] = 0.3;
	w_old[3] = 0.35;
	w_old[4] = 0.39;
	
	vector<double> d;
	d.resize(row);
	d[0] = 0.01;
	d[1] = 0;
	d[2] = 0;
	d[3] = 0;
	d[4] = 0.09;

	vector<double> w_new;
	w_new.resize(row);

	cout << "before cal: " << endl;
	        for(int i = 0; i < row; i++) {
                cout << w_new[i] << endl;
        }


	calculate_vector_exp(A, w_old, w_new, d, row, col);

	cout << "after cal: " << endl;
	for(int i = 0; i < row; i++) {
		cout << w_new[i] << endl;
	}

	return 0;
}



