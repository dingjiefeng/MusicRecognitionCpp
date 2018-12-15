#include <stdlib.h>
#include <iostream>
#include "../DB/CMySqlWrapper.h"
#include "../General/MyTime.h"
#include "../Hash/Hash.h"
#include "../ShazamAlgorithm/CMusicSearcher.h"
#include <boost/filesystem/path_traits.hpp>
#include <boost/filesystem/path.hpp>
using namespace std;

/**
 * 简单测试DB的增删改查操作：
 * 1. 新增一整行数据
 */

//inline void insertLine()
//{
//	CMySqlWrapper sql;
//	sql.connect();
//	sql.switchDB("shazam");
//	shazam::CMyTimeWrapper t;
//	t.tic();
//	for (long i = 0; i < 600000; ++i)
//		sql.insertIntoSongs("郁闷");
//	t.tocMs();
//}

/**
 * 简单测试从表里面读取数据
 */
//inline void selectDemo()
//{
//	int hashid(269338);
//	CMySqlWrapper sql;
//	sql.connect();
//	sql.switchDB("shazam");
//	shazam::CMyTimeWrapper t;
//	t.tic();
//	vector<shazam::Hash> &&hashes = sql.selectHashFromSongHash(hashid);
//	t.tocMs();
//	cout << hashes.size() << endl;
//	for(auto hash : hashes)
//	{
//		cout << hash.song_id << " " << hash.offset << endl;
//	}
//}

//
//int main()
//{
//
////	selectDemo();
////	shazam::Hash hash1,hash2;
////	hash1.setHashId(1);
////	hash2.setHashId(2);
////	vector<shazam::Hash> vec;
////	vec.push_back(hash1);
////	vec.push_back(hash2);
////	sort(vec.begin(), vec.end(), [](shazam::Hash &h1, shazam::Hash &h2) { return h1.getHashId() < h2.getHashId(); });
////	cout << vec[0].getHashId() << endl;
//	CMusicSearcher searcher;
//	boost::filesystem::path p("D:\\matlab\\Shazam\\Test\\I'm Alive_30dB.wav");
//	string pathCompleted(p.string());
//	cout << "the music to be recognized is: " << p.filename() << endl;
//	auto &&res  = searcher.search(pathCompleted);
//	cout << endl;
//	for (auto r : res)
//		cout << "the id of song: " << r.song_id << " the name of song: " << r.song_name << " score: " << r.score << endl;
//	
//	system("pause");
//	return 0;
//}