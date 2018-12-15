#pragma once

#include <string>
using namespace std;
/**
* \brief 需要注意的是，MySql需要的是以null结尾的字符串，所以，std::string需要调用c_str()转化一下
*/
struct ServerSet
{
	string host;
	string user;
	string pwd;

	ServerSet(const string& host = "tcp://127.0.0.1:3306", const string& user = "root", const std::string& pwd = "123456")
		: host(host),
		user(user),
		pwd(pwd)
	{
	}
};
