#include "maximilian.h"
#include "../General/MyTime.h"
#include "../Audio/AudioRead.h"
#include <memory>

/**
 * \TODO : 测试读取wav\pcm文件的功能，并验证数据是否与matlab读出的数据相符
 * \brief :
 * 1. 测试下来发现读取同一个wav文件，速度是matlab audioread 函数的十倍，也有可能是因为matlab做了归一化的原因
 * 2. 由于matlab做了归一化，所以我比较的是相邻数据之间的比值，经过测试发现比值是相同的，也就没有做其他测试，默认相同
 * 
 */

void readWav()
{
	maxiSample wavFile;
	shazam::CMyTimeWrapper t;
	t.tic();
	wavFile.load("D:\\matlab\\Shazam\\音乐库\\MusicDatabase\\MusicDatabase\\周杰伦 - 三年二班.wav");
	t.tocMs();
	int st = 7000;
	for (int i = st; i < st + 1000; ++i)
		cout << wavFile.temp[i] << endl;
}

void readPcm()
{
	CAudioRead r;
	string path("C:\\Users\\djf\\Desktop\\ch3.pcm");
	r.load(path);
	for (int i = 0; i < 10; ++i)
		cout << r.get(i) << endl;
	shared_ptr<int> pi;
}


int main()
{
	readPcm();
	system("pause");

	return 0;
}