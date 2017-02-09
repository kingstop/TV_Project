#pragma once
class MovieManager
{
public:
	MovieManager();
	virtual ~MovieManager();
public:
	void Load(DBQuery* p);
	const std::map<int, message::MsgVideo>* getVideos();
	const message::MsgVideo* getVideo(int id);
	const std::map<int, message::MsgMovieExternal>* getMovies();
	const message::MsgMovieExternal* getMovie(int id);
	const std::map<int, message::MsgMovieThemeExternal>* getThemes();
	const message::MsgMovieThemeExternal* getTheme(int id);
	const std::map<int, std::list<int>>* getMovieVideos();
	const std::list<int>* getMovieVideos(int id);
	const std::map<int, std::list<std::pair<int, int>>>* getThemeMovies();
	const std::list<std::pair<int, int>>* getThemeMovies(int id);
	const std::map<int, int>* getGridTheme();
protected:
	std::map<int, message::MsgVideo> _videos;
	std::map<int, message::MsgMovieExternal> _movies;	
	std::map<int, message::MsgMovieThemeExternal> _themes;
	std::map<int, std::list<int>> _movie_videos;
	std::map<int, std::list<std::pair<int, int>>> _theme_movie_ids;
	std::map<int, int> _grid_theme;
	
};

