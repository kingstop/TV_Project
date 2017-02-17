#include "stdafx.h"
#include "CharacterManager.h"
#include "Character.h"



CharacterManager::CharacterManager()
{

	_save_time = 5 * _TIME_MINUTE_ * _TIME_SECOND_ * _TIME_SECOND_MSEL_;
	
	char a = 'a';
	for (char a = 'a'; a < ('a' + 26); a++)
	{
		_char_configs.push_back(a);
	}
	_day_title = "aaa";
	_day_create_count = 0;
	_max_character_id = 0;
	_last_save_time = 0;

}


CharacterManager::~CharacterManager()
{
}

void  CharacterManager::RefreshDayNumber()
{
	std::vector<int> vc_number;
	for (size_t i = 0; i <= 9; i++)
	{
		vc_number.push_back(i);
	}

	for (size_t i = 0; i < 6; i++)
	{
		std::random_shuffle(vc_number.begin(), vc_number.end());
		for (size_t j = 0; j < 10; j++)
		{
			_day_number[i][j] = vc_number[j];
		}
	}
	_day_create_count = 0;
}
std::string CharacterManager::generateStr(int& key, const char* argu)
{
	//int number_entry;
	int number_temp = 1;
	char current_server_char = gMovieManager.GetServerID();
	std::string str_name = current_server_char + _day_title;
	int numbers[6];
	for (size_t i = 0; i < 6; i++)
	{
		int cur_number = (key / number_temp) % 10;
		numbers[i] = _day_number[i][cur_number];
		number_temp *= 10;
	}
	char sz_name[256];
	sprintf(sz_name, "%s%d%d%d%d%d%d%s", str_name.c_str(), numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5], argu);

	return sz_name;
}

void CharacterManager::Load(DBQuery* p)
{
	DBQuery& query = *p;
	query.reset();
	query << "select * from `movie_day_play`;";
	SDBResult sResult = query.store();
	int current_day_passed = gMovieManager.GetDayPassed(g_server_time);
	int rows_length = sResult.num_rows();
	for (int i = 0; i < rows_length; i++)
	{
		DBRow& row = sResult[i];
		s64 movie_id = row["movie_id"];
		int play_count = row["play_count"];
		int day_passed = row["passed_day"];
		int temp_day = current_day_passed - day_passed;
		if (temp_day >= 0 && temp_day <=8 )
		{
			std::map<s64, std::map<s64, int>>::iterator it = _watch_record.find(day_passed);
			if (it == _watch_record.end())
			{
				std::map<s64, int> temp_map;
				_watch_record[day_passed] = temp_map;
			}
			std::map<s64, int>::iterator it_play = _watch_record[day_passed].find(movie_id);
			if (it_play == _watch_record[day_passed].end())
			{
				_watch_record[day_passed][movie_id] = 0;
			}
			_watch_record[day_passed][movie_id] = _watch_record[day_passed][movie_id] + 1;
		}
	}

	query.reset();
	sResult.clear();
	query << "select * from `server_global`;";
	rows_length = sResult.num_rows();
	if (rows_length > 0)
	{
		DBRow& row = sResult[0];
		_day_create_count = row["day_create_heroes_count"];
		std::string str_number = row["day_number"].c_str();
		std::vector<std::string> outVC;
		std::vector<std::string> outVC1;
		std::vector<std::string> outVC2;
		SplitStringA(str_number, ";", outVC);
		int length = outVC.size();
		for (size_t i = 0; i < length; i++)
		{
			std::string numbers_str = outVC[i];
			SplitStringA(numbers_str, ",", outVC1);
			int length_1 = outVC1.size();
			for (size_t j = 0; j < length_1; j++)
			{
				_day_number[i][j] = atoi(outVC1[j].c_str());
			}
		}
		_last_save_time = row["UNIX_TIMESTAMP(`save_time`)"];
	}

	RefreshTitle();
	if (same_day(_last_save_time, g_server_time) == false)
	{
		RefreshDayNumber();
	}
	time_t server_time = g_server_time;
	tm* p1 = localtime(&server_time);
	int next_min = (60 - p1->tm_sec) * _TIME_SECOND_MSEL_;
	gEventMgr.addEvent(this, &CharacterManager::EventPerMin, EVENT_PER_MIN, next_min, -1, 0);

	gEventMgr.addEvent(this, &CharacterManager::Save, EVENT_SAVE_DAY_PLAY, _save_time, -1, 0);
}

void CharacterManager::RefreshTitle()
{
	time_t server_open_time = gMovieManager.GetServerOpenTime();
	tm* p_open_time = localtime(&server_open_time);
	_day_title = "aaa";
	if (g_server_time > server_open_time)
	{
		s64 day_spawn = p_open_time->tm_hour * 60 * 60 + p_open_time->tm_min * 60 + p_open_time->tm_sec;
		s64 time_spwan = g_server_time - (server_open_time - day_spawn);
		s64 number = time_spwan / (60 * 60 * 24);
		int number_char_1 = number % 26;
		int number_char_2 = (number / 26) % 26;
		int number_char_3 = (number / (26 * 26)) % 26;
		_day_title.clear();
		_day_title.push_back(_char_configs[number_char_1]);
		_day_title.push_back(_char_configs[number_char_2]);
		_day_title.push_back(_char_configs[number_char_3]);
		_day_title.push_back('\0');
		//_day_create_heroes_count = 0;
	}
}
Character* CharacterManager::GetCharacter(u64 id)
{
	Character* character = NULL;
	std::map<u64, Character*>::iterator it = _characters.find(id);
	if (it != _characters.end())
	{
		character = it->second;
	}
	return character;
}

u64 CharacterManager::generateID()
{
	_max_character_id++;
	return _max_character_id;
}

Character* CharacterManager::CreateCharacter()
{
	Character* character = new Character();
	character->Create(generateID());
	_characters[character->GetID()] = character;
	return character;	
}
std::string CharacterManager::generateName()
{
	std::string name;
	_day_create_count++;
	name = generateStr(_day_create_count, "");
	return name;
}

void CharacterManager::CreateCharacter(message::MsgCharacterDataDB2GSACK* msg)
{
	Character* character = GetCharacter(msg->character_id());
	if (character == NULL)
	{
		character = new Character();
		character->Create(msg);
	}
	std::map<u64, std::list<Session*>>::iterator it = _wait_load_sessions.find(msg->character_id());
	if (it != _wait_load_sessions.end())
	{
		std::list<Session*>::iterator it_session = it->second.begin();
		for (; it_session != it->second.end(); ++ it_session)
		{
			Session* session = (*it_session);
			character->AddSession(session);
		}
	}	
}

void CharacterManager::Save()
{
	message::MsgSaveDataGS2DB msg;
	int current_day_passed;
	char sz_temp[1024];
	std::string sql = "delete from `movie_day_play`;";
	std::map<s64, std::map<s64, int>>::iterator it = _watch_record.begin();
	for (int i = 0; it != _watch_record.end(); ++ it, i ++)
	{
		int passed_day = it->first;
		std::map<s64, int>::iterator it_play = it->second.begin();
		for (; it_play != it->second.end(); it_play++)
		{
			if (i == 0)
			{
				sql += "insert into `movie_day_play`(`passed_day`, `movie_id`, `play_count`) values";
			}
			else
			{
				sql += ",";
			}
			s64 movie_id = it_play->first;
			int play_count = it_play->second;
			sprintf(sz_temp, "(%d,%I64d,%d)", passed_day, movie_id, play_count);
			sql += sz_temp;
			if (i > 30)
			{
				i = 0;
				msg.set_sql(sql.c_str());
				gGSDBClient.sendPBMessage(&msg, 0);
				sql.clear();
			}
		}
	}
	if (sql.empty() == false)
	{
		msg.set_sql(sql.c_str());
		gGSDBClient.sendPBMessage(&msg, 0);
		sql.clear();
	}
	std::string number_str;
	std::string number_temp;
//	char sz_temp[64];
	for (size_t i = 0; i < 6; i++)
	{
		if (number_str.empty() == false)
		{
			number_str += ";";
		}
		for (size_t j = 0; j < 10; j++)
		{
			if (number_temp.empty() == false)
			{
				number_temp += ',';

			}
			sprintf(sz_temp, "%d", _day_number[i][j]);
			number_temp += sz_temp;
		}
		number_str += number_temp;
		number_temp.clear();
	}

	sql.clear();
	_last_save_time = g_server_time;
	std::string last_time_temp;
	build_unix_time_to_string(_last_save_time, last_time_temp);
	sprintf(sz_temp, "replace into `server_global`(`sid`, `server_id`, `day_create_count`, `day_number`, `save_time`) values(%d, %d, %d, '%s', '%s')",
		1, gMovieManager.GetServerID(), _day_create_count, number_str.c_str(), last_time_temp.c_str());
	msg.set_sql(sz_temp);
	gGSDBClient.sendPBMessage(&msg, 0);
}

void CharacterManager::SetMaxCharacterID(int id)
{
	_max_character_id = id;
}

void CharacterManager::Destroy(Character* p)
{
	std::map<u64, Character*>::iterator it = _characters.find(p->GetID());
	if (it != _characters.end())
	{
		_characters.erase(it);
	}
	delete p;
}


bool sort(const std::pair<s64, int>& entry_1, const std::pair<s64, int>& entry_2)
{
	if (entry_1.second > entry_2.second)
	{
		return true;
	}
	return false;
}

void CharacterManager::EventPerDay()
{
	RefreshDayNumber();
	Save();
}

void CharacterManager::EventPerMin()
{
	time_t server_time = g_server_time;
	tm* p1 = localtime(&server_time);
	if (p1->tm_hour == 0)
	{
		if (p1->tm_min == 0)
		{
			EventPerDay();
		}
	}
	if (gEventMgr.hasEvent(this, EVENT_PER_MIN) == true)
	{
		gEventMgr.removeEvents(this, EVENT_PER_MIN);
	}
	int next_min = (60 - p1->tm_sec) * _TIME_SECOND_MSEL_;
	gEventMgr.addEvent(this, &CharacterManager::EventPerMin, EVENT_PER_MIN, next_min, -1, 0);
}
void CharacterManager::DayUpdate()
{
	
	int current_day_passed = gMovieManager.GetDayPassed(g_server_time);
	std::map<s64, std::map<s64, int>>::iterator it = _watch_record.begin();
	std::map<s64, int> day_played_temp;
	std::vector<std::pair<s64, int>> movie_played;
	while (it != _watch_record.end())
	{
		int temp = current_day_passed - it->first;
		if (temp >= 7)
		{
			it = _watch_record.erase(it);
		}
		else
		{
			std::map<s64, int>::iterator it_movie_day_played = it->second.begin();
			for (; it_movie_day_played != it->second.end(); ++ it_movie_day_played)
			{
				s64 movie_id = it_movie_day_played->first;
				int played_count = it_movie_day_played->second;
				std::map<s64, int>::iterator it_found = day_played_temp.find(movie_id);
				if (it_found == day_played_temp.end())
				{
					day_played_temp[movie_id] = played_count;
				}
				else
				{
					it_found->second += played_count;
				}
			}
			++it;
		}
	}
	std::map<s64, int>::iterator it_movie_played_temp = day_played_temp.begin();
	for (; it_movie_played_temp != day_played_temp.end(); ++ it_movie_played_temp)
	{
		std::pair<s64, int> entry_pair;
		entry_pair.first = it_movie_played_temp->first;
		entry_pair.second = it_movie_played_temp->second;
		movie_played.push_back(entry_pair);
	}
	std::sort(movie_played.begin(), movie_played.end(), sort);
	std::vector<std::pair<s64, int>>::iterator it_vec_movies = movie_played.begin();
	_day_rank_movies.clear();
	for (; it_vec_movies != movie_played.end(); ++ it_vec_movies)
	{
		s64 movie_id = (*it_vec_movies).first;
		_day_rank_movies.push_back(movie_id);
	}


}

void CharacterManager::PlayVideo(s64 movie_id)
{
	int day_passed = gMovieManager.GetDayPassed(g_server_time);
	std::map<s64, std::map<s64, int>>::iterator it  = _watch_record.find(day_passed);
	if (it == _watch_record.end())
	{
		std::map<s64, int> entry_map;
		_watch_record[day_passed] = entry_map;
	}
	std::map<s64, int>::iterator it_day_count = _watch_record[day_passed].find(movie_id);
	if (it_day_count == _watch_record[day_passed].end())
	{
		_watch_record[day_passed][movie_id] = 0;
	}
	_watch_record[day_passed][movie_id] = _watch_record[day_passed][movie_id] + 1;

}

const std::vector<s64>* CharacterManager::getRankMovies()
{
	return &_day_rank_movies;
}

void CharacterManager::LoadCharacter(u64 id, Session* s)
{
	std::map<u64, std::list<Session*>>::iterator it = _wait_load_sessions.find(id);
	if (it != _wait_load_sessions.end())
	{
		_wait_load_sessions[id].push_back(s);
	}
	else
	{
		std::list<Session*> list_temp;
		list_temp.push_back(s);
		_wait_load_sessions[id] = list_temp;
		message::MsgReqCharacterDataGS2DB msg;
		msg.set_character_id(id);
		gGSDBClient.sendPBMessage(&msg);
	}
}