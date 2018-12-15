//
// Created by djf on 2017/10/23 0023.
//

#ifndef SHAZAM_MYTIME_H
#define SHAZAM_MYTIME_H
#include <chrono>
#include <iostream>

namespace shazam
{
	class CMyTimeWrapper;
}

using namespace std::chrono;
class CMyTime
{
public:
	CMyTime() :cur_t(system_clock::now()), pre_t(system_clock::now()) {}
	void mark()
	{
		pre_t = system_clock::now();
	}
	double getDuration()
	{
		cur_t = system_clock::now();
		auto duration = duration_cast<microseconds>(cur_t - pre_t);
		return static_cast<double>(duration.count())*microseconds::period::num;
	}
private:
	system_clock::time_point cur_t;
	system_clock::time_point pre_t;
};

class shazam::CMyTimeWrapper
{
public:
	CMyTimeWrapper()
	{
		t = new CMyTime();
	};

	virtual ~CMyTimeWrapper()
	{
		delete t;
	}
	void tic() const
	{
		t->mark();
	}
	void tocMs() const
	{
		std::cout << "cost time: " << getDuration() / 1000 << " ms" << std::endl;
	}
	void tocUs() const
	{
		std::cout << "cost time: " << getDuration() << " us" << std::endl;
	}
	void tocS() const
	{
		std::cout << "cost time: " << getDuration()/1000000 << " s" << std::endl;
	}
private:
	double getDuration() const
	{
		return t->getDuration();
	}
private:
	CMyTime* t;
};


#endif //TESTDELETE_MYTIME_H
