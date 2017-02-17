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
	registerCBFun(PROTOCO_NAME(message::MsgC2SReqMovieThemes), &Session::parseMsgC2SReqMovieThemes);
	registerCBFun(PROTOCO_NAME(message::MsgC2SReqThemeInfo), &Session::parseMsgC2SReqThemeInfo);
	registerCBFun(PROTOCO_NAME(message::MsgC2SReqMovieInfo), &Session::parseMsgC2SReqMovieInfo);
	registerCBFun(PROTOCO_NAME(message::MsgC2SReqPlayVideo), &Session::parseMsgC2SReqPlayMovie);
	registerCBFun(PROTOCO_NAME(message::MsgC2SReqStopVideo), &Session::parseMsgC2SReqStopMovie);
	registerCBFun(PROTOCO_NAME(message::MsgC2SReqAddMovieToFavourite), &Session::parseMsgC2SReqAddMovieToFavourite);
	//parseMsgC2SReqAddMovieToFavourite
	//parseMsgC2SReqPlayMovie

	



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

void Session::parseMsgC2SReqAddMovieToFavourite(google::protobuf::Message* p)
{
	message::MsgC2SReqAddMovieToFavourite* msg = (message::MsgC2SReqAddMovieToFavourite*)p;
	_character->AddMovieToFavourite(msg->movie_id(), this);
}

void Session::parseMsgC2SReqStopMovie(google::protobuf::Message* p)
{
	message::MsgC2SReqStopVideo* msg = (message::MsgC2SReqStopVideo*)p;
	_character->StopVideo(msg->movie_id(), msg->video_id(), msg->progress());

	message::MsgC2SStopVideoACK msgACK;
	msgACK.set_movie_id(msg->movie_id());
	msgACK.set_video_id(msg->video_id());
	msgACK.set_error(message::MsgError_NO);
	sendPBMessage(&msgACK);
	
}

void Session::parseMsgC2SReqPlayMovie(google::protobuf::Message* p)
{
	message::MsgC2SReqPlayVideo* msg = (message::MsgC2SReqPlayVideo*)p;
	_character->PlayVideo(msg->movie_id(), msg->video_id());

	message::MsgC2SPlayVideoACK msgACK;
	msgACK.set_movie_id(msg->movie_id());
	msgACK.set_video_id(msg->video_id());
	msgACK.set_error(message::MsgError_NO);
	sendPBMessage(&msgACK);

}

void Session::parseMsgC2SReqMovieThemes(google::protobuf::Message* p)
{
	message::MsgC2SReqMovieThemes* msg = (message::MsgC2SReqMovieThemes*)p;
	message::MsgS2CMovieThemesACK msgACK;
	const std::map<s64, message::MsgMovieThemeExternal>* themes = gMovieManager.getThemes();
	std::map<s64, message::MsgMovieThemeExternal>::const_iterator it = themes->begin();
	for (; it != themes->end(); ++ it)
	{
		msgACK.add_infos()->CopyFrom(it->second);
	}
	if (_character != NULL)
	{
		msgACK.add_infos()->CopyFrom(*_character->GetFavourite());
		msgACK.add_infos()->CopyFrom(*_character->GetRecentlyPlay());
		msgACK.add_infos()->CopyFrom((gMovieManager.getRankMovieTheme()->theme_external()));

	}
	
	sendPBMessage(&msgACK);
	
}
void Session::parseMsgC2SReqThemeInfo(google::protobuf::Message* p)
{
	message::MsgC2SReqThemeInfo* msg = (message::MsgC2SReqThemeInfo*)p;

	message::MsgS2CThemeInfoACK msgACK;
	s64 theme_id = msg->theme_id();
	message::MsgMovieTheme* info = msgACK.mutable_info();
	message::MsgMovieThemeExternal* theme_external = NULL;
	if (theme_id == MyFavouriteID)
	{
		info->mutable_theme_external()->CopyFrom(*_character->GetFavourite());
		const std::list<s64>*  favourite_list = _character->GetFavouriteList();
		std::list<s64>::const_iterator it = favourite_list->begin();
		for (; it != favourite_list->end(); ++ it)
		{
			const message::MsgMovieExternal*  external = gMovieManager.getMovie(*it);
			if (external != NULL)
			{
				info->add_movies_externals()->CopyFrom(*external);
			}
		}
	}
	else if(theme_id == RecentlyPlayID)
	{
		info->mutable_theme_external()->CopyFrom(*_character->GetRecentlyPlay());
		const std::map<s64, message::MsgWatchRecordInfo>*  watchs = _character->getRecentlyWatch();
		std::map<s64, message::MsgWatchRecordInfo>::const_iterator it = watchs->begin();
		for (; it != watchs->end(); ++ it)
		{
			const message::MsgWatchRecordInfo watch_info = it->second;
			s64 movie_id = watch_info.movie_id();
			
			const message::MsgMovieExternal*  external = gMovieManager.getMovie(movie_id);
			if (external != NULL)
			{
				info->add_movies_externals()->CopyFrom(*external);
				message::MsgIntPair* entry_pair = info->add_movie_ratting();
				entry_pair->set_number_1(movie_id);
				entry_pair->set_number_2(watch_info.time());
			}
		}
	}
	else if (theme_id == RankID)
	{
		const std::vector<s64>* map_rank = gCharacterManager.getRankMovies();
		std::vector<s64>::const_iterator it_rank = map_rank->begin();
		for (; it_rank != map_rank->end(); ++ it_rank)
		{
			s64 movie_id = (*it_rank);
			const message::MsgMovieExternal*  external = gMovieManager.getMovie(movie_id);
			if (external != NULL)
			{
				info->add_movies_externals()->CopyFrom(*external);
				//message::MsgIntPair* entry_pair = info->add_movie_ratting();
				//entry_pair->set_number_1(movie_id);
				//entry_pair->set_number_2(0);
			}
		}


	}
	else
	{
		const std::list<std::pair<s64, s64>>* movies = gMovieManager.getThemeMovies(theme_id);
		std::list<std::pair<s64, s64>>::const_iterator it = movies->begin();
		for (; it != movies->end(); ++ it)
		{
			std::pair<s64, s64> entry_pair = (*it);
			s64 movie_id = entry_pair.first;
			s64 ratting = entry_pair.second;
			const message::MsgMovieExternal*  external = gMovieManager.getMovie(movie_id);
			if (external != NULL)
			{
				info->add_movies_externals()->CopyFrom(*external);
				message::MsgIntPair* entry_pair = info->add_movie_ratting();
				entry_pair->set_number_1(movie_id);
				entry_pair->set_number_2(ratting);
			}

		}
	}
	sendPBMessage(&msgACK);

}
void Session::parseMsgC2SReqMovieInfo(google::protobuf::Message* p)
{
	message::MsgC2SReqMovieInfo* msg = (message::MsgC2SReqMovieInfo*)p;
	message::MsgS2CMovieInfoACK msgACK;
	s64 movie_id = msg->movie_id();
	const message::MsgMovieExternal* movie_external = gMovieManager.getMovie(movie_id);
	if (movie_external != NULL)
	{
		message::MsgMovie* info = msgACK.mutable_info();
		info->mutable_external()->CopyFrom(*movie_external);
		const std::list<s64>* videos = gMovieManager.getMovieVideos(movie_id);
		std::list<s64>::const_iterator it_videos = videos->begin();
		for (; it_videos != videos->end(); ++ it_videos)
		{
			s64 video_id = (*it_videos);
			const message::MsgVideo* entry_video = gMovieManager.getVideo(video_id);
			if (entry_video != NULL)
			{
				info->add_videos()->CopyFrom(*entry_video);
			}			
		}
	}
	sendPBMessage(&msgACK);
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
	sprintf(sz_sql, "replace into `account_character_relationship`(`account`, `channel`, `character_id`, `key_word`) values(%llu, %d, %llu, '%s')",
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






