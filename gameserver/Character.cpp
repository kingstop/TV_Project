#include "stdafx.h"
#include "Character.h"
#include "session.h"
#define _SAVE_CHARACTER_TIME_ 6 * _TIME_MINUTE_ * _TIME_SECOND_MSEL_
#define _DESTROY_CHARACTER_TIME_ 5 * _SAVE_CHARACTER_TIME_
Character::Character()
{
	message::MsgMovieThemeExternal entry_theme_external;
	entry_theme_external.set_id(0);
	entry_theme_external.set_describe("");
	entry_theme_external.set_name("");
	entry_theme_external.set_type(message::MovieType_MyFavourite);
	_collection_theme.mutable_theme_external()->CopyFrom(entry_theme_external);	

	message::MsgMovieThemeExternal* external = _recently_theme.mutable_theme_external();
	external->set_id(1);
	entry_theme_external.set_describe("");
	entry_theme_external.set_name("");
	entry_theme_external.set_type(message::MovieType_RecentlyPlay);

}

const message::MsgMovieTheme* Character::GetFavourite()
{
	return &_collection_theme;
}
const message::MsgMovieTheme* Character::GetRecentlyPlay()
{
	return &_recently_theme;
}

const std::list<s64>* Character::GetFavouriteList()
{
	return &_collection_movie;
}

const std::map<s64, message::MsgWatchRecordInfo>* Character::getRecentlyWatch()
{
	return &_watch_records;
}

Character::~Character()
{
}

u64 Character::GetID()
{
	return _id;
}
void Character::Create(u64 id)
{
	_id = id;
	_vip_level = 0;
}
void Character::RemoveSession(Session* s)
{
	std::list<Session*>::iterator it = _sessions.begin();
	for (; it != _sessions.end(); ++it)
	{
		if ((*it) == s)
		{
			_sessions.erase(it);
			break;
		}
	}
	if (_sessions.size() == 0)
	{
		StartDestroyClock();
	}
}

void Character::AddSession(Session* s)
{
	bool ret = false;
	std::list<Session*>::iterator it = _sessions.begin();
	for (; it != _sessions.end(); ++it)
	{
		if ((*it) == s)
		{
			ret = true;
			break;
		}
	}

	if (ret == false)
	{
		_sessions.push_back(s);
		if (_sessions.size() == 1)
		{
			StopDestroyClock();
		}
	}
}


void Character::StartSave()
{
	if (gEventMgr.hasEvent(this, EVENT_SAVE_CHARACTER_DATA_))
	{
		gEventMgr.removeEvents(this, EVENT_SAVE_CHARACTER_DATA_);
	}
	gEventMgr.addEvent(this, &Character::Save, EVENT_SAVE_CHARACTER_DATA_, _SAVE_CHARACTER_TIME_, -1, 0);
}

void Character::StartDestroyClock()
{
	if (gEventMgr.hasEvent(this, EVENT_DESTROY_CHARACTER_))
	{
		gEventMgr.removeEvents(this, EVENT_DESTROY_CHARACTER_);
	}
	gEventMgr.addEvent(this, &Character::Destroy, EVENT_DESTROY_CHARACTER_, _DESTROY_CHARACTER_TIME_, 1, 0);
	_destroy = true;
}

void Character::Destroy()
{
	gCharacterManager.Destroy(this);
}

void Character::StopDestroyClock()
{
	if (gEventMgr.hasEvent(this, EVENT_DESTROY_CHARACTER_))
	{
		gEventMgr.removeEvents(this, EVENT_DESTROY_CHARACTER_);
	}
	_destroy = false;
}

void Character::SendClienInit(Session* s)
{
	if (s != NULL)
	{
		message::MsgS2CClientInit msg;
		msg.set_config_pic_path("");
		msg.set_config_video_path("");
		msg.set_vip(_vip_level);
		msg.set_resource_path("");
		const std::map<s64, s64>* map = gMovieManager.getGridTheme();
		std::map<s64, s64>::const_iterator it_grid = map->begin();
		for (; it_grid != map->end(); ++it_grid)
		{
			msg.add_gird_theme()->set_number_1(it_grid->first);
			msg.add_gird_theme()->set_number_2(it_grid->second);
		}

		std::map<s64, message::MsgWatchRecordInfo>::iterator it = _watch_records.begin();
		for (; it != _watch_records.end(); ++it)
		{
			msg.add_watch_record()->CopyFrom(it->second);
		}
		
		s->sendPBMessage(&msg);
	}

}



void Character::Save()
{
	char sz_sql[40960];
	char temp_sql[512];
	std::string watch_str;
	std::map<s64, message::MsgWatchRecordInfo>::iterator it = _watch_records.begin();
	for (int i = 0; it != _watch_records.end(); ++ it, i ++)
	{
		if (i != 0)
		{
			watch_str += ";";
		}
		const message::MsgWatchRecordInfo& msg_entry = it->second;
		sprintf(temp_sql, "%d,%d,%d,%lu", msg_entry.movie_id(), msg_entry.video_id(), msg_entry.progress(), msg_entry.time());
		watch_str += temp_sql;
	}
	sprintf(sz_sql, "replace into `character`(`character_id`, `rate_of_progress`, `vip`) values(%lu, '%s', %d)", _id, watch_str.c_str(), _vip_level);
	message::MsgSaveDataGS2DB msg;
	msg.set_sql(sz_sql);
	gGSDBClient.sendPBMessage(&msg, 0);

	std::string sql_collection;
	sprintf(temp_sql, "delete from `character_movie_collection` where `character_id` =%lu", _id);
	sql_collection += temp_sql;
	std::list<s64>::iterator it_collection = _collection_movie.begin();
	for (int i = 0; it_collection != _collection_movie.end(); ++it_collection, i ++)
	{
		if (i != 0)
		{
			sql_collection += "insert into character_movie_collection(`character_id`,`movie_id`) values";
		}
		else
		{
			sql_collection += ",";
		}
		int id = (*it_collection);
		sprintf(temp_sql, "(%lu, %d)", _id, id);
		sql_collection += temp_sql;
	}
	
	msg.set_sql(sql_collection.c_str());
	gGSDBClient.sendPBMessage(&msg, 0);	
}

void Character::Create(message::MsgCharacterDataDB2GSACK* msg)
{
	_id = msg->character_id();
	_vip_level = msg->vip();
	int record_size = msg->records_size();
	for (size_t i = 0; i < record_size; i++)
	{
		message::MsgWatchRecordInfo entry_watch;
		entry_watch.CopyFrom(msg->records(i));
		_watch_records[entry_watch.movie_id()] = entry_watch;
	}
	int collection_movies_size = msg->collection_movies_ids_size();
	for (size_t i = 0; i < collection_movies_size; i++)
	{
		int movie_id = msg->collection_movies_ids(i);
		_collection_movie.push_back(movie_id);
		const message::MsgMovieExternal* movie_external = gMovieManager.getMovie(movie_id);
		_collection_theme.add_movies_externals()->CopyFrom(*movie_external);
	}		
	
}
