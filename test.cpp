#include <iostream>
#include <vector>

using namespace std;

void calculate_vector_im(vector<vector<double> > B, vector<double> w_old, 
			 vector<double>& w_new, vector<double> d, int row, int col) {
        vector<double> wd;
        wd.resize(row);
        double factor;
        for(int i = 0; i < row; i++) {
                wd[i] = w_old[i]+d[i];
		cout << "wd[" << i << "] " << wd[i] << endl;
        }
        for(int j = 0; j < row-1; j++) {
                factor = B[j+1][j]/B[j][j];
                for(int k = j; k < j+3; k++) {
                        B[j+1][k] = B[j+1][k]-B[j][k]*factor;
                }
                wd[j+1] = wd[j+1]-wd[j]*factor;
        }

	cout << "To upper triangle:" << endl;
	cout << "B is: " << endl;
	for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                        cout << "upper B[" << i << "][" << j << "] " << B[i][j] << endl;
                }
        }
	
	cout << "wd is: " << endl;
	for(int i = 0; i < row; i++)
		cout << "upper wd[" << i << "] " << wd[i] << endl;


        for(int j = 0; j < row; j++) {
		factor = B[j][j];
                for(int k = j; k < j+2; k++) {
                        B[j][k]=B[j][k]/factor;
                }
                wd[j] = wd[j]/factor;
        }
	cout << "Diagnol to unit: " << endl;
	cout << "B is: " << endl;
	for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                        cout << "To unit B[" << i << "][" << j << "] " << B[i][j] << endl;
                }
        }

	cout << "wd is" << endl;
	for(int i = 0; i < row; i++)
                cout << "To unit wd[" << i << "] " << wd[i] << endl;

        for(int i = row-1; i > 0; i--) {
                factor = B[i-1][i];
                B[i-1][i] = 0;
                wd[i-1] = wd[i-1]-wd[i]*factor;
        }
        for(int i = 0; i < row; i++) {
                w_new[i] = wd[i];
        }

	cout << "We want B = I, and finally B is: " << endl;
	for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                        cout << "Finally B[" << i << "][" << j << "] " << B[i][j] << endl;
                }
        }
	cout << "Finally wd(w_new) is:" << endl;
	for(int i = 0; i < row; i++)
                cout << "Finally wd[" << i << "] " << wd[i] << endl;

}


int main()
{
	int row = 3;
	int col = 3;
	double lambda = 0.2;
	vector<vector<double> > B;
	B.resize(row);
        for(int i = 0; i < col; i++) {
                B[i].resize(col,0.0);
        }
        for(int i = 0; i < row; i++) {
                B[i][i] = 1+2*lambda;
        }
        for(int i = 0; i < row-1; i++) {
                B[i][i+1] = -lambda;
                B[i+1][i] = -lambda;
        }

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			cout << "B[" << i << "][" << j << "] " << B[i][j] << endl; 
		}
	}


	vector<double> w_old;
	w_old.resize(row);
	w_old[0] = 0.1;
	w_old[1] = 0.2;
	w_old[2] = 0.3;
	
	vector<double> d;
	d.resize(row);
	d[0] = 0.01;
	d[1] = 0;
	d[2] = 0.03;

	vector<double> w_new;
	w_new.resize(row);

	calculate_vector_im(B, w_old, w_new, d, row, col);

	return 0;
}



