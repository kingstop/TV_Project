#pragma once
#include <iostream>
#include <map>
#include <vector>

typedef std::map<s64, message::MsgWatchRecordInfo> MAPWATCHRECORDS;
class Character : public EventableObject
{

public:
	Character();
	virtual ~Character();
public:
	void Create(u64 id);
	void Create(message::MsgCharacterDataDB2GSACK* msg);
	void AddMovieToFavourite(s64 movie_id, Session* p);
	void AddSession(Session* s);
	void RemoveSession(Session* s);
	void SendClienInit(Session* s);
	void PlayVideo(s64 movie_id, s64 video_id);
	void StopVideo(s64 movie_id, s64 video_id, int  progress);
	void StartSave();
	void StartDestroyClock();
	void StopDestroyClock();
	const message::MsgMovieTheme* GetFavourite();
	const message::MsgMovieTheme* GetRecentlyPlay();
	const std::list<s64>* GetFavouriteList();
	const MAPWATCHRECORDS* getRecentlyWatch();

	void Save();
	u64 GetID();
protected:
	void Destroy();
protected:
	MAPWATCHRECORDS _watch_records;
	message::MsgMovieTheme _collection_theme;
	message::MsgMovieTheme _recently_theme;
	std::list<s64> _collection_movie;
	int _vip_level;
	u64 _id;
	std::string _name;
	bool _destroy;
	std::list<Session*> _sessions;
};

