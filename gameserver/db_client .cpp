#include "stdafx.h"
#include "message/msg_gate_login.pb.h"
#include "session.h"
//#include "DreamHero.h"
GameDBClient::GameDBClient():tcp_client( *net_global::get_io_service() )
{
	_proto_user_ptr = this;
	m_isreconnect = true;
}

GameDBClient::~GameDBClient()
{
}

void GameDBClient::parseDBMsgDefault(google::protobuf::Message* p, pb_flag_type flag)
{
    if (flag != INVALID_TRANS_ID)
    {
        Session* pkSession = gGSGateManager.getUser(flag);
        if (p && pkSession)
        {
            pkSession->sendPBMessage(p);
        }
    }
}

//void GameDBClient::parseQueryChar(google::protobuf::Message* p, pb_flag_type flag)
//{
//
//}
//
//void GameDBClient::parseNeedCreateHero(google::protobuf::Message* p, pb_flag_type flag)
//{
//	Session* pkSession = gGSGateManager.getUser(flag);
//	if (p && pkSession)
//	{
//		pkSession->parseDBQueryNeedCreateHero();
//	}
//
//}
//
//void GameDBClient::parseQueryHeroInfo(google::protobuf::Message* p, pb_flag_type flag)
//{
//	message::MsgHeroDataDB2GS* HeroDataMsg = (message::MsgHeroDataDB2GS*)p;
//	Session* pkSession = gGSGateManager.getUser(flag);
//	if (pkSession)
//	{
//		pkSession->praseDBQueryHeroInfo(HeroDataMsg);
//	}
//}

void GameDBClient::parseMsgSaveAllHeroes(google::protobuf::Message* p, pb_flag_type flag)
{
	//gDreamHeroManager.save_all_heroes_ok();
}

void GameDBClient::parseMsgNeedCreateCharacterDB2GS(google::protobuf::Message* p, pb_flag_type flag)
{
	Session* pkSession = gGSGateManager.getUser(flag);
	if (p && pkSession)
	{
		pkSession->parseCreateCharacter();
	}
}

void GameDBClient::parseMsgCharacterDataDB2GSACK(google::protobuf::Message* p, pb_flag_type flag)
{
	message::MsgCharacterDataDB2GSACK* msg = (message::MsgCharacterDataDB2GSACK*)p;
	gCharacterManager.CreateCharacter(msg);	
}

void GameDBClient::parseMsgCharacterIDDB2GSACK(google::protobuf::Message* p, pb_flag_type flag)
{
	Session* pkSession = gGSGateManager.getUser(flag);
	if (p && pkSession)
	{
		message::MsgCharacterIDDB2GSACK* msg = (message::MsgCharacterIDDB2GSACK*)p;
		pkSession->parseMsgCharacterIDDB2GSACK(msg);
	}
}

void GameDBClient::initPBModule()
{
	ProtocMsgBase<GameDBClient>::registerSDFun(&GameDBClient::send_message, &GameDBClient::parseDBMsgDefault);
	ProtocMsgBase<GameDBClient>::registerCBFun(PROTOCO_NAME(message::MsgCharacterDataDB2GSACK), &GameDBClient::parseMsgCharacterDataDB2GSACK);

	ProtocMsgBase<GameDBClient>::registerCBFun(PROTOCO_NAME(message::MsgNeedCreateCharacterDB2GS), &GameDBClient::parseMsgNeedCreateCharacterDB2GS);
	ProtocMsgBase<GameDBClient>::registerCBFun(PROTOCO_NAME(message::MsgCharacterIDDB2GSACK), &GameDBClient::parseMsgCharacterIDDB2GSACK);
}

void GameDBClient::on_close( const boost::system::error_code& error )
{
	tcp_session::on_close( error );
	Mylog::log_server(LOG_INFO, "DB server close");
}

void GameDBClient::on_connect()
{
	tcp_client::on_connect();
	Mylog::log_server(LOG_INFO, "connect db server success!");
    const service_config& conf = gGameServer.getServiceConf();
    message::MsgServerRegister msg;
    msg.set_serverid(conf.id);
    message::ServerVersion* p2 = msg.mutable_version();
    p2->set_major(gGSVersion.nMajor);
    p2->set_minor(gGSVersion.nMinor);
    p2->set_build(gGSVersion.nBuild);
    p2->set_appsvn(gGSVersion.nAppSvn);
    sendPBMessage(&msg);
}

void GameDBClient::on_connect_failed( boost::system::error_code error )
{
	 Mylog::log_server(LOG_ERROR, "connect DBServer ip:[%s] failed!", get_remote_address_string().c_str());
}

void GameDBClient::proc_message( const message_t& msg )
{
	parsePBMessage(msg.data, msg.len, msg.base64);
}
