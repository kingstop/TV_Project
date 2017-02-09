#include "stdafx.h"
#include "session.h"
#include "Character.h"
//#include "DreamHero.h"
//#include "player.h"
//#include "message/girls.pb.h"
//#include "FRWorld.h"

/************************************************************************/

/*                          注册消息实例                                */  

/*  message::MsgDB2GSQueryCharResult 注册回调    prasePBTest             */

/************************************************************************/
typedef void(Session::*pn_msg_cb)(google::protobuf::Message*);
static std::map<std::string, pn_msg_cb > static_session_cb_funs;
static void registerCBFun(std::string str, pn_msg_cb fun)
{
    static_session_cb_funs.insert(std::make_pair(str, fun));
}

void Session::prasePBDefault(google::protobuf::Message* p)
{
     Mylog::log_server(LOG_INFO, "Parse message name [%s]", p->GetTypeName().c_str());
}

//这里负责注册消息
void Session::registerPBCall()
{


	//parseCmdReqClearDailyRankList

	//

}


int Session::getState()
{
	return m_state;
}



void Session::parsePBMessage(google::protobuf::Message* p)
{
    std::map<std::string, pn_msg_cb >::iterator it = static_session_cb_funs.find(p->GetTypeName());
    if (it != static_session_cb_funs.end())
    {
        pn_msg_cb fun = boost::ref( it->second);
        if ( NULL != fun )
        {
            (this->*fun)(p);
            return ;
        }
    }
    prasePBDefault(p);
}

//////////////////////////////////////////////////////////////////////////

Session::Session(tran_id_type t, account_type a, u16 gate)
    :m_tranid(t), m_account(a), m_gate(gate),m_state(_session_online_), _character(NULL)
{
	message::MsgReqCharacterIDGS2DB msg;
	msg.set_account(m_account);
	gGSDBClient.sendPBMessage(&msg, m_tranid);	
	//DreamHero* hero = gDreamHeroManager.GetHero(m_account);
	//if (hero)
	//{
	//	hero->StopDestroyClock();
	//}
	
	//if (hero != NULL)
	//{
		//_dream_hero = hero;
	//	_dream_hero->set_session(this);
	//	_dream_hero->SendClientInit();
		
	//}
	//else
	//{
	//	message::MsgReqHeroDataGS2DB msg;
	//	msg.set_account(m_account);
	//	gGSDBClient.sendPBMessage(&msg, m_tranid);
	//}

}

Session::~Session()
{
	if (_character)
	{
		_character->RemoveSession(this);
		_character = NULL;

	}
	//if (_dream_hero != NULL)
	//{
	//	_dream_hero->StartDestroyTime();
	//	_dream_hero->set_session(NULL);
	//}	
	//_dream_hero = NULL;
}

Character* Session::GetCharacter()
{

	return _character;
}

int Session::get_channel()
{
	return _channel;
}

void Session::close()
{
	//if (_dream_hero != NULL)
	//{
	//	_dream_hero->StartDestroyTime();
	//}
	
}

void Session::setReconnet()
{
    m_state = _session_online_;
	//if (_dream_hero)
	//{
	//	_dream_hero->set_online(true);
	//}
}



void Session::setWaitReconnet()
{
    m_state = _session_offline_;
	//if (_dream_hero)
	//{
	//	_dream_hero->set_online(false);
	//}	
}

void Session::sendPBMessage(google::protobuf::Message* p)
{
    if (m_state == _session_online_)
    {
	    gGSGateManager.sendMessage(p, m_tranid, m_gate);
    }
	else
    {

    }
}

void Session::parseMsgCharacterIDDB2GSACK(message::MsgCharacterIDDB2GSACK* msg)
{
	u64 character_id = 0;		
	_channel_character_id = msg->channel_character_id();
	_default_character_id = msg->default_charatcer_id();
	if (_channel_character_id != 0)
	{
		character_id = _channel_character_id;
	}
	else if (_default_character_id != 0)
	{
		character_id = _default_character_id;
	}
	Character* character = gCharacterManager.GetCharacter(character_id);
	if (character != NULL)
	{
		_character = character;
		_character->SendClienInit(this);
		_character->AddSession(this);
	}
	else
	{
		if (character_id != 0)
		{
			gCharacterManager.LoadCharacter(character_id, this);
		}		
	}	
}

void Session::Save()
{
	char sz_sql[512];
	sprintf(sz_sql, "replace into `account_character_relationship`(`account`, `channel`, `character_id`, `key_word`) values(%lu, %d, %lu, '%s')",
		m_account, _channel ,_default_character_id, _channel_key_word.c_str());
	message::MsgSaveDataGS2DB msg;
	msg.set_sql(sz_sql);
	gGSDBClient.sendPBMessage(&msg, m_tranid);		
}

void Session::parseCreateCharacter()
{
	_character = gCharacterManager.CreateCharacter();
	_default_character_id = _character->GetID();
	_channel_character_id = 0;
	_character->SendClienInit(this);
	_character->AddSession(this);
}






