#pragma once
#include <iostream>
#include <map>
#include <vector>
class Character : public EventableObject
{
public:
	Character();
	virtual ~Character();
public:
	void Create(u64 id);
	void Create(message::MsgCharacterDataDB2GSACK* msg);	
	void AddSession(Session* s);
	void RemoveSession(Session* s);
	void SendClienInit(Session* s);
	void StartSave();
	void StartDestroyClock();
	void StopDestroyClock();
	void Save();
	u64 GetID();
protected:
	void Destroy();
protected:
	std::map<int, message::MsgWatchRecordInfo> _watch_records;
	message::MsgMovieTheme _collection_theme;
	std::list<int> _collection_movie;
	int _vip_level;
	u64 _id;
	bool _destroy;
	std::list<Session*> _sessions;
};

