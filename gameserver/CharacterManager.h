#pragma once
class Character;
class CharacterManager
{
public:
	CharacterManager();
	virtual ~CharacterManager();
public:
	void CreateCharacter(message::MsgCharacterDataDB2GSACK* msg);	
	Character* CreateCharacter();
	Character* GetCharacter(u64 id);
	void Destroy(Character* p);
	void LoadCharacter(u64 id, Session* s);	
	void SetMaxCharacterID(int id);
protected:
	u64 generateID();
protected:
	std::map<u64, Character*> _characters;
	
	std::map<u64, std::list<Session*>> _wait_load_sessions;	
	u64 _max_character_id;
};

