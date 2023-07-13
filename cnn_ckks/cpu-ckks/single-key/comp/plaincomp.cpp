#include "plaincomp.h"

void minimax_ReLU_plain(long comp_no, vector<int> deg, long alpha, vector<Tree> &tree, double scaled_val, long scalingfactor, vector<double>& plain_in, vector<double>& res)
{
	// variables
	vector<vector<double>> decomp_coeff(comp_no, vector<double>(0));
	vector<double> scale_val(comp_no, 0.0);
	vector<double> temp(plain_in.size(), 0.0);
	vector<double> half(plain_in.size(), 0.0);
	vector<double> x(plain_in.size(), 0.0);

	// ifstream and scale
	string str;
	string addr = "../result";
	str = addr + "/d" + to_string(alpha) + ".txt";
	ifstream in(str);

	// scaled value setting	
	scale_val[0] = 1.0;	
	for(int i=1; i<comp_no; i++) scale_val[i] = 2.0;
	scale_val[comp_no-1] = scaled_val;

	// print degrees and coefficients of the component polynomials of minimax composite polynomial
	// for(int i=0; i<comp_no; i++) cout << deg[i] << " ";
	// cout << endl;
	for (int i = 0; i < comp_no; i++) {
		for(int j=0; j<coeff_number(deg[i], tree[i]); j++) {
			double temp;
			in >> temp;
			decomp_coeff[i].emplace_back(temp);
			// cout << decomp_coeff[i][j] << " ";
		}
		// cout << endl;
	}

	// scale coefficients properly so that unnecessary level consumptions do not occur
	for(int i=0; i<comp_no-1; i++) for(int j=0; j<coeff_number(deg[i], tree[i]); j++) decomp_coeff[i][j] /= scale_val[i+1];
	for(int j=0; j<coeff_number(deg[comp_no-1], tree[comp_no-1]); j++) decomp_coeff[comp_no-1][j] *= 0.5;		// scale 

	// generation of half ciphertext
	// long n = cipher_in.poly_modulus_degree()/2;
	long n = plain_in.size();
	vector<double> m_half(n);
	for(int i=0; i<n; i++) m_half[i] = 0.5;
	x = plain_in;

	// evaluating pk ... p1(x) / 2
	for (int i = 0; i < comp_no; ++i) {
		// cout << "*******************************************" << endl;
		// cout << "               No: " << i << endl;
		// eval_polynomial_integrate(encryptor, evaluator, decryptor, encoder, public_key, secret_key, relin_keys, cipher_x, cipher_x, deg[i], decomp_coeff[i], tree[i]); 
		eval_polynomial_integrate(x, x, deg[i], decomp_coeff[i], tree[i]); 
		// decrypt_and_print_part(cipher_x, decryptor, encoder, n, 0, 5);
	}

	// x(1+sgn(x))/2 from sgn(x)/2
	// encoder.encode(m_half, cipher_x.scale(), plain_half);
	// encryptor.encrypt(plain_half, cipher_half);	
	// evaluator.add_reduced_error(cipher_x, cipher_half, cipher_temp);
	half = m_half;
	temp = add_(x, half);
	// evaluator.multiply_reduced_error(cipher_temp, cipher_in, relin_keys, cipher_res);
	res = multiply_(temp, plain_in);
	// evaluator.rescale_to_next_inplace(cipher_res);
}



vector<double> add_(vector<double> &a, vector<double> &b) {
	if(a.size() != b.size()) throw std::invalid_argument("add - len(a) != len(b)");
	vector<double> out(a.size(), 0.0);
	for (int i = 0; i < a.size(); i++) {
		out[i] = a[i] + b[i];
	}
	return out;
}


vector<double> multiply_(vector<double> &a, vector<double> &b) {
	if(a.size() != b.size()) throw std::invalid_argument("mul - len(a) != len(b)");
	vector<double> out(a.size(), 0.0);
	for (int i = 0; i < a.size(); i++) {
		out[i] = a[i] * b[i];
	}
	return out;
}
