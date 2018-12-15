#pragma once
#ifndef SHAZAM_FFT_H
#define SHAZAM_FFT_H
#include "../3rd_party/Eigen/fft"

namespace shazam
{
	class CFFtWrapper;
}

using namespace Eigen;

/**
 * \brief 封装了Eigen::FFT,
 * 1. 作为一个函数对象用于产生歌曲的快速傅里叶变换
 * 可产生多通道的变换信息 
 * 2. 如果是MatrixXcf的输入格式，默认同一行的数据术语同一个通道
 */
class shazam::CFFtWrapper
{
public:
	typedef Matrix<float, Dynamic, Dynamic> unitf;
	explicit CFFtWrapper(int nfft = -1)
		: Nfft(nfft)
	{
	}
	~CFFtWrapper()
	{
	}
	int nfft() const
	{
		return Nfft;
	}

	void set_nfft(int nfft)
	{
		Nfft = nfft;
	}

	int window_size() const
	{
		return WINDOW_SIZE;
	}

	Matrix<MatrixXd, Dynamic, Dynamic> operator()(MatrixXd& datas);
	//FFT<float> fft;		//FFT processor
private:
	FFT<double> fftd;		//FFT processor
	int Nfft;			//N-point FFT
	static const int WINDOW_SIZE = 4096;
};
/**
 * \TODO : 多通道float信号生成对应的FFT结果
 * \brief : 二维矩阵生成三维矩阵，分别是通道、帧数、帧信号三个维度
 * 这里有一个**大**坑： 按行计算fft的时候，是直接计算的，按列计算的时候，是把列的每一行当作一个数组来计算的
 */
inline Matrix<MatrixXd, Dynamic, Dynamic> shazam::CFFtWrapper::operator()(MatrixXd& datas)
{
	int frameNum = datas.cols() / WINDOW_SIZE + ((datas.cols() % WINDOW_SIZE) > 0 ? 1 : 0);
	Matrix<MatrixXd, Dynamic, Dynamic> res(datas.rows(), frameNum);
	for (int i = 0; i < datas.rows(); ++i)
	{
		for (int j = 0; j < frameNum; ++j)
		{
			//计算每一通道每一帧的频域信息
			MatrixXcd frameAmp(1, WINDOW_SIZE);
			for (int k = 0; k < WINDOW_SIZE; ++k)
			{
				if (j*WINDOW_SIZE + k < datas.cols())
					frameAmp(0, k) = datas(i, j*WINDOW_SIZE + k);
				else
					frameAmp(0, k) = 0;
			}
			MatrixXcd tmp(1, WINDOW_SIZE);
			tmp.row(0) = fftd.fwd(frameAmp.row(0), Nfft);
			res(i, j) = tmp.cwiseAbs();
		}
	}
	return res;
}


#endif
