#include "stdafx.h"
#include "MovieManager.h"


MovieManager::MovieManager()
{
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
			std::map<int, std::list<int>>::iterator it = _movie_videos.find(movie_id);
			if (it == _movie_videos.end())
			{
				std::list<int> list_entry;
				_movie_videos[movie_id] = list_entry;
			}
			_movie_videos[movie_id].push_back(video_id);
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
			int theme_id = row["theme_id"];
			int ratting = row["ratting"];
			std::map<int, std::list<std::pair<int, int>>>::iterator it = _theme_movie_ids.find(theme_id);
			if (it == _theme_movie_ids.end())
			{
				std::list<std::pair<int, int>> list_entry;
				_theme_movie_ids[theme_id] = list_entry;
			}
			std::pair<int, int> entry;
			entry.first = theme_id;
			entry.second = ratting;
			_theme_movie_ids[theme_id].push_back(entry);
		}
	}
}


const std::map<int, message::MsgVideo>* MovieManager::getVideos()
{
	return &_videos;
}
const message::MsgVideo* MovieManager::getVideo(int id)
{
	message::MsgVideo* video = NULL;
	std::map<int, message::MsgVideo>::iterator it = _videos.find(id);
	if (it != _videos.end())
	{
		video = &(it->second);
	}
	return video;
}


const std::map<int, message::MsgMovieExternal>* MovieManager::getMovies()
{
	return &_movies;
}
const message::MsgMovieExternal* MovieManager::getMovie(int id)
{
	message::MsgMovieExternal* entry = NULL;
	std::map<int, message::MsgMovieExternal>::iterator it = _movies.find(id);
	if (it != _movies.end())
	{
		entry = &(it->second);
	}
	return entry;
}
const std::map<int, message::MsgMovieThemeExternal>* MovieManager::getThemes()
{
	return &_themes;
}
const message::MsgMovieThemeExternal* MovieManager::getTheme(int id)
{
	message::MsgMovieThemeExternal* entry = NULL;
	std::map<int, message::MsgMovieThemeExternal>::iterator it = _themes.find(id);
	if (it != _themes.end())
	{
		entry = &(it->second);
	}
	return entry;
}
const std::map<int, std::list<int>>* MovieManager::getMovieVideos()
{
	return &_movie_videos;
}
const std::list<int>* MovieManager::getMovieVideos(int id)
{
	std::list<int>* entry = NULL;
	std::map<int, std::list<int>>::iterator it = _movie_videos.find(id);
	if (it != _movie_videos.end())
	{
		entry = &(it->second);
	}
	return entry;

}
const std::map<int, std::list<std::pair<int, int>>>* MovieManager::getThemeMovies()
{
	return &_theme_movie_ids;
}
const std::list<std::pair<int, int>>* MovieManager::getThemeMovies(int id)
{
	std::list<std::pair<int, int>>* entry_list = NULL;
	std::map<int, std::list<std::pair<int, int>>>::iterator it = _theme_movie_ids.find(id);
	if (it != _theme_movie_ids.end())
	{
		entry_list = &(it->second);
	}
	return entry_list;
}