#pragma once
#include "mysql_connection.h"
#include <windows.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "ServerSet.h"
#include <vector>
#include "../Hash/Hash.h"

using namespace sql;
using namespace std;

class CMySqlWrapper
{
public:

	CMySqlWrapper()
		: serverInfo("tcp://127.0.0.1:3306", "root", "123456"),
		driver(nullptr),
		con(nullptr),
		stmt(nullptr),
		prep_stmt(nullptr),
		res(nullptr)
	{
	}
	~CMySqlWrapper();

	bool CMySqlWrapper::isConnected() const
	{
		if (con->isValid() && !con->isClosed())
			return true;
		return false;
	}

	bool CMySqlWrapper::connect()
	{
		try
		{
			driver = get_driver_instance();
			con = driver->connect(serverInfo.host.c_str(), serverInfo.user.c_str(), serverInfo.pwd.c_str());
			stmt = con->createStatement();
		}
		catch (SQLException e)
		{
			exceptionHandle(e);
		}
		return con->isValid();
	}

	static void CMySqlWrapper::exceptionHandle(SQLException& e)
	{
		if (e.getErrorCode() != 0) {
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}
	}
	void CMySqlWrapper::switchDB(const string& db_name)
	{
		try
		{
			con->setSchema(db_name.c_str());
			stmt = con->createStatement();
		}
		catch (SQLException e)
		{
			exceptionHandle(e);
		}
	}
	int CMySqlWrapper::insertIntoSongs(const string& name)
	{
		int num(-1);
		try
		{
			string cmd("INSERT INTO songs (name) VALUES(\"" + string_To_UTF8(name) + "\")");
			stmt->executeUpdate(cmd.c_str());
			res = stmt->executeQuery("SELECT LAST_INSERT_ID();");//("SELECT id FROM songs WHERE id = @@IDENTITY");
			if (res->next())
				num = res->getInt(1);
		}
		catch (SQLException e)
		{
			exceptionHandle(e);
		}
		return num;
	}
	/*
	void CMySqlWrapper::insertIntoSonghash(int hash, int songid, int offset)
	{
		try
		{
			prepareInsertToSonghash();
			prep_stmt->setInt(1, hash);
			prep_stmt->setInt(2, songid);
			prep_stmt->setInt(3, offset);
			prep_stmt->executeUpdate();
			prep_stmt->clearParameters();
		}
		catch (SQLException e)
		{
			exceptionHandle(e);
		}
	}*/
	void CMySqlWrapper::insertBatchIntoSonghash(vector<shazam::Hash> &hashes)
	{
		try
		{ 
			//"INSERT INTO song_hash (hash, id, offset) VALUES( ?, ?, ?)"
			for (auto hash : hashes)
			{
				string cmd("INSERT INTO song_hash (hash, id, offset) VALUES(" + to_string(hash.getHashId()) + "," + to_string(hash.song_id) + "," + to_string(hash.offset) + ")");
				stmt->executeUpdate(cmd.c_str());

			}
		}
		catch (SQLException e)
		{
			exceptionHandle(e);
		}
	}

	string getNameFromSongs(int song_id)
	{
		string name;
		try
		{
			string cmd("SELECT * FROM songs WHERE id = " + to_string(song_id) + ";");
			res = stmt->executeQuery(cmd.c_str());
			if(res->next())
				name = res->getString("name");
			return UTF8_To_string(name);
		} catch (SQLException e)
		{
			exceptionHandle(e);
			return name;
		}
	}
	vector<shazam::Hash> selectHashFromSongHash(int hashid)
	{
		vector<shazam::Hash> hashes;
		try
		{
			string cmd("SELECT * FROM song_hash WHERE hash = " + to_string(hashid) + ";");
			res = stmt->executeQuery(cmd.c_str());
//			prepareSelectFromSongHash();
//			prep_stmt->setInt(1, hashid);
//			res = prep_stmt->executeQuery();
			while(res->next())
			{
				shazam::Hash hash(res->getInt(2), res->getInt(3));
				hashes.push_back(hash);
			}
			return hashes;
		}
		catch (SQLException e)
		{
			exceptionHandle(e);
			return hashes;// make complier happy
		}
	}
private:
	void prepareSelectFromSongHash()
	{
		try
		{
			prep_stmt = con->prepareStatement("SELECT * FROM song_hash WHERE hash = ?;");
		}
		catch (SQLException e)
		{
			exceptionHandle(e);
		}
	}
	inline void CMySqlWrapper::prepareInsertToSongs()
	{
		try
		{
			prep_stmt = con->prepareStatement("INSERT INTO songs (name) VALUES(?)");
		}
		catch (SQLException exception)
		{
			exceptionHandle(exception);
		}
	}
	inline void CMySqlWrapper::prepareInsertToSonghash()
	{
		try
		{
			prep_stmt = con->prepareStatement("INSERT INTO song_hash (hash, id, offset) VALUES( ?, ?, ?)");
		}
		catch (SQLException exception)
		{
			exceptionHandle(exception);
		}
	}
	static string string_To_UTF8(const std::string & str)
	{
		int nwLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

		wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
		ZeroMemory(pwBuf, nwLen * 2 + 2);

		MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char * pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);

		WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr(pBuf);

		delete[]pwBuf;
		delete[]pBuf;

		pwBuf = nullptr;
		pBuf = nullptr;

		return retStr;
	}

	static string UTF8_To_string(const std::string & str)
	{
		int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

		wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
		memset(pwBuf, 0, nwLen * 2 + 2);

		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char * pBuf = new char[nLen + 1];
		memset(pBuf, 0, nLen + 1);

		WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr = pBuf;

		delete[]pBuf;
		delete[]pwBuf;

		pBuf = NULL;
		pwBuf = NULL;

		return retStr;
	}
private:
	ServerSet serverInfo;
	Driver *driver;
	Connection *con;
	Statement* stmt;
	PreparedStatement* prep_stmt;
	ResultSet* res;
};


