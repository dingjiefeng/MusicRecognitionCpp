#include <iostream>
#include <vector>
#include <Eigen/fft>
#include "../Hash/FFTWrapper.h"
#include "../General/MyTime.h"
using namespace std;
using namespace Eigen;

/**
 * 1. 尽量使用Eigenvalue::matrix作为默认容器，方便接口对接
 */


void example_org_fft();
void example_self_fft();

//int main()
//{
//	shazam::CMyTimeWrapper t;
//	t.tic();
//	example_self_fft();
//	t.tocMs();
//	system("pause");
//	return 0;
//}


void example_org_fft()
{
	MatrixXcd m(1,4096);
	MatrixXcd cf(1,4096);
	for (int j = 0; j < m.rows(); ++j)
	{
		for (int i = 0; i < m.cols(); ++i)
			m(0, i) = static_cast<double>(i + 1);
	}
	
	FFT<double> fft;
	
	cf.row(0) = fft.fwd(m.row(0));
	MatrixXd f = cf.cwiseAbs();
	std::cout << "复数结果" << cf << std::endl;
	std::cout << "结果" << f << std::endl;
}

void example_self_fft()
{
	shazam::CFFtWrapper fft;
	MatrixXd datas(2, 4096);
	for (int i = 0; i < datas.cols(); ++i)
		datas(0, i) = i + 1;
	for (int i = 0; i < datas.cols(); ++i)
		datas(1, i) = i + 1;
	Matrix<MatrixXd, Dynamic, Dynamic> &&res = fft(datas);
	cout << res(0,0) << endl;
	cout << "=============================================" << endl;
	cout << res.rows() << " " << res.cols() << endl;
}



