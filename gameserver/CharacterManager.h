#pragma once
class Character;
class CharacterManager : public EventableObject
{
public:
	CharacterManager();
	virtual ~CharacterManager();
public:
	void DayUpdate();
	void Load(DBQuery* p);
public:
	void CreateCharacter(message::MsgCharacterDataDB2GSACK* msg);	
	Character* CreateCharacter();
	Character* GetCharacter(u64 id);
	std::string generateStr(int& key, const char* argu);
	void RefreshTitle();
	void PlayVideo(s64 movie_id);
	void Destroy(Character* p);
	void LoadCharacter(u64 id, Session* s);	
	void Save();
	void SetMaxCharacterID(int id);
	const std::vector<s64>* getRankMovies();
	std::string generateName();
protected:
	u64 generateID();
	void RefreshDayNumber();
	void EventPerDay();
	void EventPerMin();
protected:
	std::map<u64, Character*> _characters;
	std::map<s64, std::map<s64, int>> _watch_record;
	std::map<u64, std::list<Session*>> _wait_load_sessions;	
	std::vector<s64> _day_rank_movies;
	u64 _max_character_id;
	int _save_time;
	u8 _day_number[6][10];
	int _day_create_count;
	std::vector<char> _char_configs;
	std::string _day_title;
	u64 _last_save_time;
};

