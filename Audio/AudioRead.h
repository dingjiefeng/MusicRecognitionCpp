#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
/**
 * class for reading *.pcm
 * !!!attention : only for single channel
 */
class CAudioRead
{
public:
	CAudioRead():data(nullptr),length(0)
	{
	}
	~CAudioRead()
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}
	}
	void load(std::string &path);
	int size() const { return length; }
	short get(int pos);
private:
	short *data;
	int length;
};

inline void CAudioRead::load(std::string& path)
{
	fstream fin;
	fin.open(path.c_str(), ios::in | ios::binary);
	if(fin)
	{
		fin.seekg(0, fin.end);
		int len(fin.tellg());
		fin.seekg(0, fin.beg);
		char *temp = new char[len];
		fin.read(temp, len);
		if (!fin) cerr << "failed" << endl;
		data = new short[len / 2];
		for (int i = 0; i < len / 2; ++i)
			data[i] = *(reinterpret_cast<short*>(temp + i * 2));
		length = len;
		delete[] temp;
	}
}

inline short CAudioRead::get(int pos)
{
	if (pos < 0 || pos >= length || data==nullptr)
		cerr << "failed at" << __FILE__ << " #" << __LINE__ << endl;
	return data[pos];
}
