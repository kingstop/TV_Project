#ifndef __player_session_h__
#define __player_session_h__
class DreamHero;
class Session :PUBLIC_BASE_OBJECT(Session), public EventableObject
{
	REGISTER_POOL_INFO(Session, 100, 0)
public:
	enum
	{
		_session_online_,
		_session_offline_,
	};
	void prasePBDefault(google::protobuf::Message* p);	
	static void registerPBCall();
public:
public:
	void parseMsgCharacterIDDB2GSACK(message::MsgCharacterIDDB2GSACK* msg);
	void parseCreateCharacter();
	//void praseDBQueryHeroInfo(message::MsgHeroDataDB2GS* HeroDataMsg);
	
	//DreamHero* get_dream_hero();
public:
	Session(tran_id_type t, account_type a, u16 gate);
	~Session();
	void close();
	void setReconnet();
	void setWaitReconnet();
	u16  getGateId() const {return m_gate ;}
	tran_id_type getTranId() const {return m_tranid ;}
	account_type getAccount() const {return m_account ;}
	void sendPBMessage(google::protobuf::Message* p);
	void parsePBMessage(google::protobuf::Message* p);


public:
	Character* GetCharacter();
	int getState();
	void set_channel(int channel) { _channel = channel; }
	int get_channel();
protected:
	void Save();
protected:
	tran_id_type m_tranid;
	account_type m_account;
	u16 m_gate;
	u8  m_state;
	Character* _character;
	u64 _channel_character_id;
	u64 _default_character_id;
	std::string _channel_key_word;
	//DreamHero* _dream_hero;
	int _channel;
private:
};
#endif

