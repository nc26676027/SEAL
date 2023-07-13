#pragma	once
#include "plaincomp.h"
#include "MinicompFunc.h"
#include "func.h"
#include "PolyUpdate.h"
#include "program.h"
#include "Bootstrapper.h"
#include <omp.h>
#include <NTL/RR.h>
#include <fstream>
#include <vector>
#include <chrono>


using namespace std;
using namespace minicomp;

typedef vector<double> Cleartext;



class Tensor
{
private:
	int k_;		// k: gap
	int h_;		// w: height
	int w_;		// w: width
	int c_;		// c: number of channels
	int t_;		// t: \lfloor c/k^2 \rfloor
	int p_;		// p: 2^log2(nt/k^2hwt)
	int logn_;
	vector<double> vec_;

public:
	Tensor();
	Tensor(int logn, int k, int h, int w, int c, int t, int p, vector<double> data);
	int k() const;
    int h() const;
    int w() const;
	int c() const;
	int t() const;
	int p() const;
    int logn() const;
    long n() const;
    vector<double> vec() const;
	void set_vec(vector<double> vec);
	void print_parms();
};

void multiplexed_parallel_convolution_print(const Tensor &cnn_in, Tensor &cnn_out, int co, int st, int fh, int fw, const vector<double> &data, vector<double> running_var, vector<double> constant_weight, double epsilon, vector<Cleartext> pool, ofstream &output, size_t stage, bool end = false);
void multiplexed_parallel_batch_norm_plain_print(const Tensor &cnn_in, Tensor &cnn_out, vector<double> bias, vector<double> running_mean, vector<double> running_var, vector<double> weight, double epsilon, double B, ofstream &output, size_t stage, bool end = false);
void approx_ReLU_plain_print(const Tensor &cnn_in, Tensor &cnn_out, long comp_no, vector<int> deg, long alpha, vector<Tree> &tree, double scaled_val, long scalingfactor, double B, ofstream &output, size_t stage);
void multiplexed_parallel_downsampling_plain_print(const Tensor &cnn_in, Tensor &cnn_out, ofstream &output);
void tensor_add_plain_print(const Tensor &cnn1, const Tensor &cnn2, Tensor &destination, ofstream &output);
void averagepooling_plain_scale_print(const Tensor &cnn_in, Tensor &cnn_out, double B, ofstream &output);
void fully_connected_plain_print(const Tensor &cnn_in, Tensor &cnn_out, vector<double> matrix, vector<double> bias, int q, int r, ofstream &output);

void multiplexed_parallel_convolution_plain(const Tensor &cnn_in, Tensor &cnn_out, int co, int st, int fh, int fw, const vector<double> &data, vector<double> running_var, vector<double> constant_weight, double epsilon, vector<Cleartext> pool, bool end = false);
void multiplexed_parallel_batch_norm_plain(const Tensor &cnn_in, Tensor &cnn_out, vector<double> bias, vector<double> running_mean, vector<double> running_var, vector<double> weight, double epsilon, double B, bool end = false);
void ReLU_plain(const Tensor &cnn_in, Tensor &cnn_out, long comp_no, vector<int> deg, long alpha, vector<Tree> &tree, double scaled_val, long scalingfactor, double scale = 1.0);
void multiplexed_parallel_downsampling_plain(const Tensor &cnn_in, Tensor &cnn_out);
void cnn_add_plain(const Tensor &cnn1, const Tensor &cnn2, Tensor &destination);
void averagepooling_plain_scale(const Tensor &cnn_in, Tensor &cnn_out, double B, ofstream &output);
void matrix_multiplication_plain(const Tensor &cnn_in, Tensor &cnn_out, vector<double> matrix, vector<double> bias, int q, int r);


void memory_save_rotate(const Cleartext &in, Cleartext &out, int steps, long n);

Cleartext rotate_vector_plain(Cleartext &in, int steps);
Cleartext add_vec(Cleartext &a, Cleartext &b);
Cleartext sub_vec(Cleartext &a, Cleartext &b);
Cleartext multiply_vec(Cleartext &a, Cleartext &b);


