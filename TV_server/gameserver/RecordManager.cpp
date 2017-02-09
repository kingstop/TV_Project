#include "stdafx.h"
#include "RecordManager.h"


RecordManager::RecordManager()
{
}

RecordManager::~RecordManager()
{
}

const char* RecordManager::getCurTime()
{
	build_unix_time_to_string(g_server_time, _cur_time);
	return _cur_time.c_str();
}



void RecordManager::update()
{
	int max_count = 10;
	std::string sql_record;
	for (size_t i = RecordTypeLogin; i < RecordTypeMax; i++)
	{		
		RECORDS::iterator it = _record[i].begin();

		for (int j = 0; it != _record[i].end(); ++ it, j ++)
		{
			if (j >= max_count)
			{
				message::MsgRecordSqlGS2DB msg;
				msg.set_sql(sql_record.c_str());
				gGSDBClient.sendPBMessage(&msg, 0);				
				sql_record.clear();
				j = 0;
			}

			if (j == 0)
			{
				sql_record += _sql_head[i];
			}
			else
			{
				sql_record += ",";
			}
			sql_record += (*it);
		}

		if (sql_record.empty() == false)
		{
			message::MsgRecordSqlGS2DB msg;
			msg.set_sql(sql_record.c_str());
			gGSDBClient.sendPBMessage(&msg, 0);
			sql_record.clear();
		}
		_record[i].clear();
	}
}