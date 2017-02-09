#include "stdafx.h"
#include "CharacterManager.h"
#include "Character.h"


CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
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

void CharacterManager::SetMaxCharacterID(int id)
{
	_max_character_id = id;
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