#pragma once
class MovieManager
{
public:
	MovieManager();
	virtual ~MovieManager();
public:
	void Load(DBQuery* p);
	const std::map<s64, message::MsgVideo>* getVideos();
	const message::MsgVideo* getVideo(s64 id);
	const std::map<s64, message::MsgMovieExternal>* getMovies();
	const message::MsgMovieExternal* getMovie(s64 id);
	const std::map<s64, message::MsgMovieThemeExternal>* getThemes();
	const message::MsgMovieThemeExternal* getTheme(s64 id);
	const std::map<s64, std::list<s64>>* getMovieVideos();
	const std::list<s64>* getMovieVideos(s64 id);
	const std::map<s64, std::list<std::pair<s64, s64>>>* getThemeMovies();
	const std::list<std::pair<s64, s64>>* getThemeMovies(s64 id);
	const std::map<s64, s64>* getGridTheme();
protected:
	std::map<s64, message::MsgVideo> _videos;
	std::map<s64, message::MsgMovieExternal> _movies;
	std::map<s64, message::MsgMovieThemeExternal> _themes;
	std::map<s64, std::list<s64>> _movie_videos;
	std::map<s64, std::list<std::pair<s64, s64>>> _theme_movie_ids;
	std::map<s64, s64> _grid_theme;
	
};

