#include <iostream>
#include "../ShazamAlgorithm/CHashEncoder.h"
#include "../General/MyTime.h"
#include "../DB/CMySqlWrapper.h"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include <thread>

namespace bf = boost::filesystem;
void task(CMySqlWrapper & sql, vector<Hash> &hashes)
{
	sql.insertBatchIntoSonghash(hashes);
}
int iterDirectory(const string &p)
{
	CHashEncoder h;
	CMySqlWrapper sql;
	sql.connect();
	sql.switchDB("shazam");
	ofstream out("filelist.txt");
	bf::path path(p);
	if (bf::exists(p) && bf::is_directory(p))
	{
		//directory
		int fileNum(0);
		bf::recursive_directory_iterator end_iter;
		for (bf::recursive_directory_iterator file_iter(p);
			file_iter != end_iter;
			++file_iter)
		{
			if (!bf::is_directory(*file_iter))
			{
				++fileNum;
				cout << endl;
				cout << "fileNum :" << fileNum << " ";
				string songPath(file_iter->path().string());
				string songName(songPath.substr(p.size()));
				int songId = sql.insertIntoSongs(songName);
				vector<Hash> &&hashes = h.generateFingerprint(songPath, songId);
				cout << endl;
				cout << "the number of hashes is: " << hashes.size() << endl;
				sql.insertBatchIntoSonghash(hashes);
			}

		}
		out.close();
		return fileNum;
	}
	cout << "文件目录不存在" << endl;
	return -1;
}
//int main(int argc, char* argv[])
//{
//	shazam::CMyTimeWrapper t;
//	cout << "start to generate hashes of songs: " << endl;
//	t.tic();
//	cout << "the number of songs is : " <<iterDirectory("D:\\matlab\\Shazam\\音乐库\\MusicDatabase\\small\\") << endl;
//	t.tocMs();
//
//	system("pause");
//	return 0;
//}
