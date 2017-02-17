#include "stdafx.h"
#include "MovieManager.h"


MovieManager::MovieManager()
{
	message::MsgMovieThemeExternal* external = _rank_theme.mutable_theme_external();
	external->set_id(RankID);
	external->set_describe("");
	external->set_name("");
	external->set_type(message::MovieType_Rank);
}


MovieManager::~MovieManager()
{
}

void MovieManager::Load(DBQuery* p)
{
	if (p)
	{
		DBQuery& query = *p;
		query.reset();
		query << "select * from `videos_info`;";
		SDBResult sResult = query.store();
		int rows_length = sResult.num_rows();
		for (int i = 0; i < rows_length; i++)
		{
			message::MsgVideo video_entry;
			DBRow& row = sResult[i];
			video_entry.set_video_id(row["video_id"]);
			video_entry.set_name(row["name"].c_str());
			video_entry.set_path(row["path"].c_str());
			video_entry.set_rank(row["rank"]);
			video_entry.set_describe(row["describe"].c_str());
			_videos[video_entry.video_id()] = video_entry;
		}

		query.reset();
		sResult.clear();
		query << "select * from `movies_info`";
		sResult = query.store();
		rows_length = sResult.num_rows();
		for (int i = 0; i < rows_length; i++)
		{					
			DBRow& row = sResult[i];
			message::MsgMovieExternal movie_external_entry;
			movie_external_entry.set_movie_id(row["movie_id"]);
			movie_external_entry.set_describe(row["describe"].c_str());
			movie_external_entry.set_poster_path(row["poster_path"].c_str());
			movie_external_entry.set_path(row["path"].c_str());
			int movie_type = row["video_type"];
			movie_external_entry.set_type((message::VideoType)movie_type);
			movie_external_entry.set_name(row["name"].c_str());
			_movies[movie_external_entry.movie_id()] = movie_external_entry;
		}

		query.reset();
		sResult.clear();
		query << "select * from `themes_info`";
		sResult = query.store();
		rows_length = sResult.num_rows();
		for (int i = 0; i < rows_length; i++)
		{
			DBRow& row = sResult[i];
			message::MsgMovieThemeExternal theme_external;
			theme_external.set_id(row["theme_id"]);
			theme_external.set_name(row["name"].c_str());
			theme_external.set_describe(row["describe"].c_str());
		
			int type = row["type"];
			theme_external.set_type((message::MovieType)type);
			_themes[theme_external.id()] = theme_external;
		}

		query.reset();
		sResult.clear();
		query << "select * from `movies_collection`";
		sResult = query.store();
		rows_length = sResult.num_rows();
		for (int i = 0; i < rows_length; i++)
		{
			DBRow& row = sResult[i];
			int movie_id = row["movie_id"];
			int video_id = row["video_id"];
			std::map<s64, std::list<s64>>::iterator it = _movie_videos.find(movie_id);
			if (it == _movie_videos.end())
			{
				std::list<s64> list_entry;
				_movie_videos[movie_id] = list_entry;
			}
			_movie_videos[movie_id].push_back(video_id);
		}

		query.reset();
		sResult.clear();
		query << "select * from `themes_collection`";
		sResult = query.store();
		rows_length = sResult.num_rows();
		for (int i = 0; i < rows_length; i++)
		{
			DBRow& row = sResult[i];
			int movie_id = row["movie_id"];
			int theme_id = row["theme_id"];
			int ratting = row["ratting"];
			std::map<s64, std::list<std::pair<s64, s64>>>::iterator it = _theme_movie_ids.find(theme_id);
			if (it == _theme_movie_ids.end())
			{
				std::list<std::pair<s64, s64>> list_entry;
				_theme_movie_ids[theme_id] = list_entry;
			}
			std::pair<s64, s64> entry;
			entry.first = theme_id;
			entry.second = ratting;
			_theme_movie_ids[theme_id].push_back(entry);
		}

		query.reset();
		sResult.clear();
		query << "select * from `main_panel_layout`";
		sResult = query.store();
		rows_length = sResult.num_rows();
		for (int i = 0; i < rows_length; i++)
		{
			DBRow& row = sResult[i];
			int grid_id = row["grid_id"];
			s64 theme_id = row["theme_id"];
			_grid_theme[grid_id] = theme_id;
		}

		query.reset();
		sResult.clear();
		query << "select * from `movies_info`";
		sResult = query.store();
		rows_length = sResult.num_rows();
		if (rows_length > 0)
		{
			DBRow& row = sResult[0];
			gMovieManager.SetConfigPicPath(row["config_pic_path"].c_str());
			gMovieManager.SetConfigVideoPath(row["config_video_path"].c_str());
			gMovieManager.SetConfigResourcePath(row["config_resource_path"].c_str());
		}
	}
}


const char * MovieManager::GetConfigPicPath()
{
	return _config_pic_path.c_str();
}
const char * MovieManager::GetConfigVideoPath()
{
	return _config_video_path.c_str();
}
const char * MovieManager::GetConfigResourcePath()
{
	return _config_resource_path.c_str();
}


void MovieManager::SetConfigPicPath(const char * path)
{
	_config_pic_path = path;



}
void MovieManager::SetConfigVideoPath(const char * path)
{
	_config_video_path = path;
}
void MovieManager::SetConfigResourcePath(const char * path)
{
	_config_resource_path = path
}

const std::map<s64, message::MsgVideo>* MovieManager::getVideos()
{
	return &_videos;
}
const message::MsgVideo* MovieManager::getVideo(s64 id)
{
	message::MsgVideo* video = NULL;
	std::map<s64, message::MsgVideo>::iterator it = _videos.find(id);
	if (it != _videos.end())
	{
		video = &(it->second);
	}
	return video;
}


int MovieManager::GetServerType()
{
	return _server_type;
}
void MovieManager::SetServerType(int type)
{
	_server_type = type;
}

const std::map<s64, message::MsgMovieExternal>* MovieManager::getMovies()
{
	return &_movies;
}
const message::MsgMovieExternal* MovieManager::getMovie(s64 id)
{
	message::MsgMovieExternal* entry = NULL;
	std::map<s64, message::MsgMovieExternal>::iterator it = _movies.find(id);
	if (it != _movies.end())
	{
		entry = &(it->second);
	}
	return entry;
}

const message::MsgMovieTheme* MovieManager::getRankMovieTheme()
{
	return &_rank_theme;
}
const std::map<s64, message::MsgMovieThemeExternal>* MovieManager::getThemes()
{
	return &_themes;
}
const message::MsgMovieThemeExternal* MovieManager::getTheme(s64 id)
{
	message::MsgMovieThemeExternal* entry = NULL;
	std::map<s64, message::MsgMovieThemeExternal>::iterator it = _themes.find(id);
	if (it != _themes.end())
	{
		entry = &(it->second);
	}
	return entry;
}
const std::map<s64, std::list<s64>>* MovieManager::getMovieVideos()
{
	return &_movie_videos;
}
const std::list<s64>* MovieManager::getMovieVideos(s64 id)
{
	std::list<s64>* entry = NULL;
	std::map<s64, std::list<s64>>::iterator it = _movie_videos.find(id);
	if (it != _movie_videos.end())
	{
		entry = &(it->second);
	}
	return entry;

}
const std::map<s64, std::list<std::pair<s64, s64>>>* MovieManager::getThemeMovies()
{
	return &_theme_movie_ids;
}
const std::list<std::pair<s64, s64>>* MovieManager::getThemeMovies(s64 id)
{
	std::list<std::pair<s64, s64>>* entry_list = NULL;
	std::map<s64, std::list<std::pair<s64, s64>>>::iterator it = _theme_movie_ids.find(id);
	if (it != _theme_movie_ids.end())
	{
		entry_list = &(it->second);
	}
	return entry_list;
}

const std::map<s64, s64>* MovieManager::getGridTheme()
{
	return &_grid_theme;
}

void MovieManager::SetServerOpenTime(u64 time)
{
	_server_open_time = time;

	
}
void MovieManager::SetServerDayUpdateTime(u64 time)
{
	_server_day_update_time = time;
	time_t temp_time = _server_open_time;
	struct tm *ptr;
	ptr = localtime(&temp_time);
	ptr->tm_hour = _server_day_update_time;
	ptr->tm_min = 1;
	ptr->tm_sec = 1;
	time_t temp_time_1 = mktime(ptr);
	if (temp_time_1 > temp_time)
	{
		_server_first_update_time = temp_time_1;
	}
	else
	{
		_server_first_update_time = temp_time_1 + (24 * 60 * 60);
	}
}
u64 MovieManager::GetServerOpenTime()
{
	return _server_open_time;
}
u64 MovieManager::GetServerDayUpdateTime()
{
	return _server_day_update_time;
}

void MovieManager::SetServerID(char id)
{
	_server_id = id;
}
char MovieManager::GetServerID()
{
	return _server_id;
}



u64 MovieManager::GetDayPassed(u64 time)
{
	u64 day_passed = 0;
	if (time > _server_first_update_time)
	{
		day_passed = ((time - _server_first_update_time) / (24 * 60 * 60)) + 1;
	}
	return day_passed;
}