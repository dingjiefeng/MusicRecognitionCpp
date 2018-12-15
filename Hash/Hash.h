#pragma once
#ifndef SHAZAM_HASH_H
#define SHAZAM_HASH_H
namespace shazam
{
	struct Hash;
}
struct shazam::Hash
{
	int f1;
	int f2;
	int dt;
	int offset;
	int song_id;
	Hash() = default;
	Hash(int _id ,int _offset):f1(0), f2(0), dt(0), offset(_offset), song_id(_id){}
	Hash(int f1, int f2, int dt, int offset, int songId)
		: f1(f1),
		  f2(f2),
		  dt(dt),
		  offset(offset),
		  song_id(songId)
	{
	}

	int getHashId() const
	{
		return (dt << 18) | (f1 << 9) | f2;
	}

	void setHashId(int hashId)
	{
		dt = hashId >> 18;
		f1 = (hashId & (0x3ffff)) >> 9;
		f2 = hashId & 0x1ff;
	}
};

#endif