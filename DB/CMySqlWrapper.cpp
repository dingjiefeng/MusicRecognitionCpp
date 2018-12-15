#include "CMySqlWrapper.h"

CMySqlWrapper::~CMySqlWrapper()
{
	if (res && !res->isClosed())  res->close();
	delete res;
	res = nullptr;

	if (prep_stmt)
	{
		prep_stmt->close();
		delete prep_stmt;
		prep_stmt = nullptr;
	}

	if (stmt)
	{
		stmt->close();
		delete stmt;
		stmt = nullptr;
	}

	if (con)
	{
		if (con->isValid() && !con->isClosed())
			con->close();
		delete con;
		con = nullptr;
	}
}












