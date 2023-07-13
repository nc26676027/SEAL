#pragma	once

#include "plainfunc.h"
//#include "func.h"
#include "MinicompFunc.h"

void minimax_ReLU_plain(long comp_no, vector<int> deg, long alpha, vector<Tree> &tree, double scaled_val, long scalingfactor, vector<double>& x, vector<double>& res);

vector<double> add_(vector<double> &a, vector<double> &b);
vector<double> multiply_(vector<double> &a, vector<double> &b);

