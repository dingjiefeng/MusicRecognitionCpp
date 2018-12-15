#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include <iostream>
#include <string>
#include "../DB/CMySqlWrapper.h"
#include "../General/MyTime.h"

/**
 * \TODO ： 作为文件部分的测试功能，利用boost所带fileSystem库，遍历当前目录并做一些简单筛选
 */
namespace bf = boost::filesystem;
using namespace std;


//int iterDirectory(const string &p)
//{
//	CMySqlWrapper sql;
//	sql.connect();
//	sql.switchDB("shazam");
//	shazam::CMyTimeWrapper t;
//	t.tic();
//	ofstream out("filelist.txt");
//	bf::path path(p);
//	if(bf::exists(p) && bf::is_directory(p))
//	{
//		//directory
//		int fileNum(0);
//		bf::recursive_directory_iterator end_iter;
//		for(bf::recursive_directory_iterator file_iter(p);
//			file_iter != end_iter;
//			++file_iter)
//		{
//			if(!bf::is_directory(*file_iter))
//			{
//				++fileNum;
//				out << file_iter->path().string().substr(p.size()) << endl;
//				sql.insertSong(file_iter->path().string().substr(p.size()), " waw");
//			}
//
//		}
//		out.close();
//		t.tocMs();
//		return fileNum;
//	}
//	cout << "文件目录不存在" << endl;
//	return -1;
//}

//int main()
//{
//	std::cout << iterDirectory("D:\\matlab\\Shazam\\音乐库\\MusicDatabase\\MusicDatabase\\") << std::endl;
//	system("pause");
//	return 0;
//}