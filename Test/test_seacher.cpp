#include "../ShazamAlgorithm/CMusicSearcher.h"

int main()
{
	CMusicSearcher searcher;
	string pathCompleted("D:\\matlab\\Shazam\\Test\\I'm Alive_30dB.wav");
	vector<song> &&res = searcher.search(pathCompleted);
	for (auto r : res)
		cout << "the id of song: " << r.song_id << " the name of song: " << r.song_name << " score: " << r.score << endl;
	return 0;
}
