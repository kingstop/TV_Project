#include "stdafx.h"
#include "GameConfig.h"

//
//GameConfig::GameConfig()
//{
//
//	
//}
//
//
//GameConfig::~GameConfig()
//{
//}
//
//
//const message::MsgShopConfigInfo* GameConfig::getShopConfig(int  grid_id)
//{
//	message::MsgShopConfigInfo* shop_config = NULL;
//	MAPSHOPHEROCONFIGS::iterator it = _shop_heroes.find(grid_id);
//	if (it != _shop_heroes.end())
//	{
//		shop_config = &it->second;
//	}
//	return shop_config;
//}
//
//const MAPSHOPHEROCONFIGS* GameConfig::getShopConfigs()
//{
//	return &_shop_heroes;
//}
//const MAPTASKS* GameConfig::getMapTasks()
//{
//	return &_tasks;
//}
//
//const MAPGOLDSHOPCONFIGINFOS* GameConfig::getGoldShopConfigInfos(int channel)
//{
//	MAPGOLDSHOPCONFIGINFOS* entry = NULL;
//	CHANNELMAPGOLDSHOPCONFIGINFOS::iterator it = _gold_shop_config_infos.find(channel);
//	if (it != _gold_shop_config_infos.end())
//	{
//		entry = &it->second;
//	}
//	return entry;
//}
//
//
//const GoldShopConfigInfo* GameConfig::getGoldShopConfigInfo(int channel, const char* appstore_product_id)
//{
//
//	const MAPGOLDSHOPCONFIGINFOS* map_configs = getGoldShopConfigInfos(channel);
//	if (map_configs)
//	{
//		MAPGOLDSHOPCONFIGINFOS::const_iterator it = map_configs->begin();
//		for (; it != map_configs->end(); ++it)
//		{
//			if (it->second.appstore_product_id_ == appstore_product_id)
//			{
//				return &it->second;
//
//			}
//		}
//	}
//	return NULL;
//}
//
//const GoldShopConfigInfo* GameConfig::getGoldShopConfigInfo(int channel, int id)
//{
//	const MAPGOLDSHOPCONFIGINFOS* map_configs = getGoldShopConfigInfos(channel);
//
//	GoldShopConfigInfo* entry = NULL;
//	MAPGOLDSHOPCONFIGINFOS::const_iterator it = map_configs->find(id);
//	if (it != map_configs->end())
//	{
//		return &it->second;
//	}
//	return NULL;
//}
//
//
//const  message::MsgChapterConfigInfo* GameConfig::getChapterConfigInfo(int id)
//{
//	message::MsgChapterConfigInfo* info_config = NULL;
//	MAPCHAPTERCONFIGINFOS::iterator it = _chapter_config_infos.find(id);
//	if (it != _chapter_config_infos.end())
//	{
//		info_config = &it->second;
//	}
//	return info_config;
//}
//
//void GameConfig::setServerOpenTime(u64 time_open)
//{
//	_server_open_time = time_open;
//}
//void GameConfig::setServerID(char server_id)
//{
//	_server_char = server_id;
//}
//
//u64 GameConfig::getServerOpenTime()
//{
//	return _server_open_time;
//}
//char GameConfig::getServerID()
//{
//	return _server_char;
//}
//
//
//const message::MsgTaskConfigInfo* GameConfig::getMapTask(int id)
//{
//	message::MsgTaskConfigInfo* info_temp = NULL;
//	MAPTASKS::iterator it = _tasks.find(id);
//	if (it != _tasks.end())
//	{
//		info_temp = &it->second;
//	}
//	return info_temp;
//
//}
//
//const MAPCHAPTERCONFIGINFOS* GameConfig::getChapterConfigInfos()
//{
//	return &_chapter_config_infos;
//}
//
//const MAPTIMESHOPSALESPROMOTIONCONFIGS* GameConfig::getTimeShopSalesPromotionConfigs()
//{
//	return &_shop_time_sales_promotion;
//}
//
//
//const TimeShopSalesPromotionConfig* GameConfig::getTimeShopSalesPromotionConfig(int id)
//{
//	TimeShopSalesPromotionConfig* config = NULL;
//	MAPTIMESHOPSALESPROMOTIONCONFIGS::iterator it = _shop_time_sales_promotion.find(id);
//	if (it != _shop_time_sales_promotion.end())
//	{
//		config = &it->second;
//	}
//	return config;
//}
//
//
//const MAPLOTIONSHOPCONFIGS* GameConfig::getLotionShop()
//{
//	return &_map_lotion_shop_configs;
//}
//const message::MsgLotionShopConfigInfo* GameConfig::getLotionShop(int index)
//{
//	message::MsgLotionShopConfigInfo* entry = NULL;
//	MAPLOTIONSHOPCONFIGS::iterator it = _map_lotion_shop_configs.find(index);
//	if (it != _map_lotion_shop_configs.end())
//	{
//		entry = &it->second;
//	}
//	return entry;
//}
//
//
//const MAPTYPEDROPBOXCONFIGS* GameConfig::getMapDropBox(int chapter_id, int section_id)
//{
//	MAPTYPEDROPBOXCONFIGS* ret = NULL;
//	std::pair<int, int> entry_pair;
//	entry_pair.first = chapter_id;
//	entry_pair.second = section_id;
//	MAPMAPDROPBOXCONFIGS::iterator it = _map_drop_box_configs.find(entry_pair);
//	if (it != _map_drop_box_configs.end())
//	{
//		ret = &it->second;
//	}
//	return ret;
//}
//
//const MAPSPIRITSHOP* GameConfig::getSpiritShop()
//{
//	return &_map_spirit_shop;
//}
//const message::MsgSpiritShopInfo* GameConfig::getSpiritShop(int index)
//{
//	message::MsgSpiritShopInfo* entry = NULL;
//	MAPSPIRITSHOP::iterator it = _map_spirit_shop.find(index);
//	if (it != _map_spirit_shop.end())
//	{
//		entry = &it->second;
//	}
//	return entry;
//}
//
//const globalConfig& GameConfig::getGlobalConfig()
//{
//	return _global_config;
//}
//void GameConfig::setNeedConnectPlatform(bool b)
//{
//	_need_connect_platform = b;
//}
//void GameConfig::setPlatformServerIp(const char* ip)
//{
//	_platform_ip = ip;
//}
//void GameConfig::setPlatformServerPort(int port)
//{
//	_platform_port = port;
//}
//
//void GameConfig::setGameID(int game_id)
//{
//	_game_id = game_id;
//}
//int GameConfig::getGameID()
//{
//	return _game_id;
//}
//
//
//void GameConfig::setServerType(int t)
//{
//	_server_type = t;
//}
//int GameConfig::getServerType()
//{
//	return _server_type;
//}
//
//bool GameConfig::isNeedConnectPlatform()
//{
//	return _need_connect_platform;
//}
//const char* GameConfig::getPlatformServerIp()
//{
//	return _platform_ip.c_str();
//}
//int GameConfig::getPlatformServerPort()
//{
//	return _platform_port;
//}
//
//
//const DAILYGAMEPRIZECONFIGS* GameConfig::getDailyGamePrizeConfigs()
//{
//	return &_daily_game_prize_configs;
//}
//
//void GameConfig::setPlatformHttpUrl(const char* http)
//{
//	_platform_http = http;
//}
//
//const char* GameConfig::getPlatformHttpUrl()
//{
//	return _platform_http.c_str();
//}
//
//const VCLOTTERYDRAWBOXSCONFIGS* GameConfig::getLotteryDrawBoxs()
//{
//	return &_lottery_draw_configs;
//}
//bool GameConfig::isInToday(u32 time)
//{
//	std::string time_str;
//	std::string time_cur;
//	build_unix_time_to_string(time, time_str);
//	build_unix_time_to_string(g_server_time, time_cur);
//	Mylog::log_server(LOG_INFO, "server time[%s]  time1[%s]!", time_str.c_str(), time_cur.c_str());
//
//	int day_offset_time = _global_config.day_Refresh_time_ * 60 * 60;
//
//	time_t _t1 = (time_t)g_server_time;
//	tm* p1 = localtime(&_t1);
//	p1->tm_min = 0;
//	p1->tm_sec = 0;
//	p1->tm_hour = _global_config.day_Refresh_time_;
//	time_t today_refresh_time =  mktime(p1); //utf ʱ���
//	time_t Tomorrow_refresh_time = today_refresh_time + (24 * 60 * 60 );
//	bool ret = false;
//	if (time < Tomorrow_refresh_time && time >= today_refresh_time)
//	{
//		ret = true;
//	}
//	
//	return ret;
//}
//void GameConfig::Load(DBQuery* p)
//{
//
//	if (p)
//	{
//		DBQuery& query = *p;
//		query << "select * from `dream_heroes_task_config`;";
//		SDBResult sResult = query.store();
//		int rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i ++)
//		{
//			DBRow& row = sResult[i];
//			message::MsgTaskConfigInfo TaskInfoConfig;
//			TaskInfoConfig.set_taskid(row["task_id"]);	
//
//			message::MsgTaskConditionInfo* info_1 = TaskInfoConfig.add_task_condition();
//			int tempType = row["type_1"];
//			int argument = row["argument_1"];
//			int argument_1 = row["argument_1_1"];
//			info_1->set_tasktype((message::TaskType)(tempType));
//			info_1->set_argument_1(argument);
//			info_1->set_argument_2(argument_1);
//
//			message::MsgTaskConditionInfo* info_2 = TaskInfoConfig.add_task_condition();
//			tempType = row["type_2"];
//			argument = row["argument_2"];
//			argument_1 = row["argument_2_1"];
//			message::TaskType type_task = (message::TaskType)(tempType);
//			info_2->set_tasktype(type_task);
//			info_2->set_argument_1(argument);
//			info_2->set_argument_2(argument_1);
//
//			
//			TaskInfoConfig.set_require_unlock_chapter(row["require_chapter"]);
//			TaskInfoConfig.set_require_unlock_section(row["require_section"]);
//			TaskInfoConfig.set_require_time(row["require_time"]);
//			TaskInfoConfig.set_require_unlock_complete_task_count(row["require_complete_task_count"]);
//			TaskInfoConfig.set_gift_gold(row["gift_gold"]);
//			TaskInfoConfig.set_difficulty(row["difficulty"]);
//			TaskInfoConfig.set_describe(row["describe"]);
//			_tasks.insert(MAPTASKS::value_type(TaskInfoConfig.taskid(), TaskInfoConfig));
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from `hero_shop_config`;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i ++)
//		{
//			DBRow& row = sResult[i];
//			message::MsgShopConfigInfo ShopConfig;
//			ShopConfig.set_grid_id(row["grid_id"]);
//			ShopConfig.set_hero_id(row["hero_id"]);
//			ShopConfig.set_require_gold(row["require_gold"]);
//			ShopConfig.set_cheape_gold(0);
//			ShopConfig.set_require_chapter_id(row["require_chapter_id"]);
//			ShopConfig.set_require_section_id(row["require_section_id"]);
//			ShopConfig.set_describe(row["describe"].c_str());
//			
//			_shop_heroes.insert(MAPSHOPHEROCONFIGS::value_type(ShopConfig.grid_id(), ShopConfig));
//		}
//		query.reset();
//		sResult.clear();
//
//		query << "select * from `chapter_unlock_config`;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			message::MsgChapterConfigInfo ChapterConfig;
//			ChapterConfig.set_chapter_id(row["chapter_id"]);
//			ChapterConfig.set_required_chapter_id(row["require_chapter_id"]);
//			ChapterConfig.set_required_section_id(row["require_section_id"]);
//			ChapterConfig.set_required_task_complete_count(row["require_task_complete_count"]);
//			ChapterConfig.set_require_gold(row["require_gold"]);
//			ChapterConfig.set_max_section_count(row["max_section_count"]);
//			ChapterConfig.set_describe(row["describe"].c_str());
//			_chapter_config_infos.insert(MAPCHAPTERCONFIGINFOS::value_type(ChapterConfig.chapter_id(), ChapterConfig));
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from `global_config`;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		if (rows_length != 0)
//		{
//			DBRow& row = sResult[0];
//			_global_config.config_gold_ = row["config_gold"];
//			_global_config.hero_unlock_count_ = row["hero_unlock_count"];
//			_global_config.day_Refresh_time_ = row["day_refresh_time"];
//			_global_config.day_free_task_count_ = row["day_free_task_count"];
//			_global_config.day_task_advertisement_task_cd_ = row["day_task_advertisement_task_cd"];
//			_global_config.hero_max_tasks_count_ =  row["hero_max_tasks_count"];
//			_global_config.channel_id_ = row["channel_id"];
//			_global_config.game_id_ = row["game_id"];
//			_global_config.refresh_task_gold_ = row["refresh_task_gold"];
//			_global_config.relive_gold_ = row["relive_gold"];
//			_global_config.config_jewel_ = row["config_jewel"];
//			_global_config.config_recover_spirit_ = row["config_recover_spirit"];
//			_global_config.config_recover_spirit_minute_ = row["config_recover_spirit_minute"];
//			_global_config.config_max_spirit_ = row["config_max_spirit"];
//			_global_config.config_enter_game_use_spirit_ = row["config_enter_game_use_spirit"];
//			_global_config.config_day_buy_spirit_ = row["config_day_buy_spirit"];
//			int max_daily_game_rank_size = row["daily_game_max_rank_size"];
//			gRankManager.setDailyMaxRankSize(max_daily_game_rank_size);
//			int max_daily_game_progress = row["daily_game_max_progress"];
//			gRankManager.setMaxDailyProgress(max_daily_game_progress);
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * , UNIX_TIMESTAMP(`begin_time`), UNIX_TIMESTAMP(`end_time`) from `time_shop_sales_promotion`;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i ++)
//		{
//			DBRow& row = sResult[i];
//			TimeShopSalesPromotionConfig SalesPromotionConfig;
//			SalesPromotionConfig.id_ = row["sales_promotion_id"];
//			SalesPromotionConfig.grid_id_ = row["grid_id"];
//			SalesPromotionConfig.cheap_gold_ = row["cheap_gold"];
//			SalesPromotionConfig.begin_time_ = row["UNIX_TIMESTAMP(`begin_time`)"];
//			SalesPromotionConfig.end_time_ = row["UNIX_TIMESTAMP(`end_time`)"];
//			_shop_time_sales_promotion.insert(MAPTIMESHOPSALESPROMOTIONCONFIGS::value_type(SalesPromotionConfig.id_, SalesPromotionConfig));
//		}
//
//
//		query.reset();
//		sResult.clear();
//		query << "select * from gold_shop_config_info;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			GoldShopConfigInfo info_entry;
//			int channel = row["channel"];
//			CHANNELMAPGOLDSHOPCONFIGINFOS::iterator it = _gold_shop_config_infos.find(channel);
//			if (it == _gold_shop_config_infos.end())
//			{
//				MAPGOLDSHOPCONFIGINFOS map_config_entry;
//				_gold_shop_config_infos[channel] = map_config_entry;
//			}
//			info_entry.info_.set_id(row["shop_id"]);
//			info_entry.info_.set_describe(row["describe"]);
//			info_entry.info_.set_gold(row["gold"]);
//			info_entry.info_.set_resource_id(row["resource_id"]);
//			info_entry.info_.set_money(row["money"]);
//			info_entry.info_.set_product_id(row["appstore_key"].c_str());
//			info_entry.appstore_product_id_ = row["appstore_key"].c_str();
//			info_entry.info_.set_jewel(row["jewel"]);
//			
//			_gold_shop_config_infos[channel][info_entry.info_.id()] = info_entry;
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from drop_box;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			ObjDropBoxConfig entry;
//			entry.obj_id_ = row["obj_id"];
//			int temp = row["obj_type"];
//			entry.type_ = (message::SubType)temp;
//			entry.base_gold_ = row["base_gold"];
//			entry.random_gold_ = row["random_gold"];
//
//			MAPTYPEDROPBOXCONFIGS::iterator it = _drop_box_configs.find(entry.type_);
//			if (it == _drop_box_configs.end())
//			{
//				MAPDROPBOXCONFIGS entry_map;
//				_drop_box_configs.insert(MAPTYPEDROPBOXCONFIGS::value_type(entry.type_, entry_map));
//			}
//			_drop_box_configs[entry.type_][entry.obj_id_] = entry;
//
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from map_obj_count;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			MapBehaviorConfig entry;
//			entry.key_.first = row["chapter_id"];
//			entry.key_.second = row["section_id"];
//			entry.obj_behavior_id_ = row["obj_behavior_id"];
//			entry.obj_count_ = row["obj_count"];
//			entry.max_pos_count_ = row["max_pos_count"];
//			
//			MAPALLBEHAVIORCONFIGS::iterator it = _map_behavior_config.find(entry.key_);
//			if (it == _map_behavior_config.end())
//			{
//				MAPBEHAVIORCONFIGS map_entry;
//				_map_behavior_config.insert(MAPALLBEHAVIORCONFIGS::value_type(entry.key_, map_entry));
//			}
//			_map_behavior_config[entry.key_][entry.obj_behavior_id_] = entry;
//			
//		}
//
//
//		query.reset();
//		sResult.clear();
//		query << "select * from random_object;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			std::pair<int, int> entry_pair;
//			int behavior_id = row["behavior_id"];
//			entry_pair.first = row["chapter_id"];
//			entry_pair.second = row["section_id"];
//			MapRandomObjConfig entry;
//			entry.obj_id_ = row["obj_id"];
//			int temp = row["obj_type"];
//			entry.type_ = (message::SubType)temp;
//			
//			MAPALLRANDOMOBJCONFIGS::iterator it = _map_random_obj_configs.find(entry_pair);
//			if (it == _map_random_obj_configs.end())
//			{
//				MAPRANDOMOBJCONFIGS map_entry;
//				_map_random_obj_configs.insert(MAPALLRANDOMOBJCONFIGS::value_type(entry_pair, map_entry));
//			}
//
//
//
//			//// drop config
//			MAPTYPEDROPBOXCONFIGS::iterator it_temp = _drop_box_configs.find(entry.type_);
//			if (it_temp != _drop_box_configs.end())
//			{
//				MAPDROPBOXCONFIGS::iterator it_temp_id_config = _drop_box_configs[entry.type_].find(entry.obj_id_);
//				if (it_temp_id_config != _drop_box_configs[entry.type_].end())
//				{					
//					MAPRANDOMOBJCONFIGS::iterator it_configs = _map_random_obj_configs[entry_pair].find(behavior_id);
//					if (it_configs == _map_random_obj_configs[entry_pair].end())
//					{
//						MapRandomObjsConfig entry;
//						entry.key_ = entry_pair;
//						entry.obj_behavior_id_ = behavior_id;
//						_map_random_obj_configs[entry_pair].insert(MAPRANDOMOBJCONFIGS::value_type(entry.obj_behavior_id_, entry));
//					}
//					_map_random_obj_configs[entry_pair][behavior_id].objs_.push_back(entry);
//
//					MAPMAPDROPBOXCONFIGS::iterator it_drop_box_config = _map_drop_box_configs.find(entry_pair);
//					if (it_drop_box_config == _map_drop_box_configs.end())
//					{
//						MAPTYPEDROPBOXCONFIGS map_entry;
//						_map_drop_box_configs.insert(MAPMAPDROPBOXCONFIGS::value_type(entry_pair, map_entry));
//					}
//
//					MAPTYPEDROPBOXCONFIGS::iterator it_type_drop_box_config = _map_drop_box_configs[entry_pair].find(entry.type_);
//					if (it_type_drop_box_config == _map_drop_box_configs[entry_pair].end())
//					{
//						MAPDROPBOXCONFIGS map_entry;
//						_map_drop_box_configs[entry_pair].insert(MAPTYPEDROPBOXCONFIGS::value_type(entry.type_, map_entry));
//					}
//					_map_drop_box_configs[entry_pair][entry.type_][entry.obj_id_] = it_temp_id_config->second;
//					
//				}
//				
//			}			
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from `spirit_shop_config`;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			message::MsgSpiritShopInfo entry;
//			entry.set_index(row["index"]);
//			entry.set_spirit(row["spirit"]);
//			entry.set_need_jewel(row["need_jewel"]);
//			entry.set_resource_id(row["resource_id"]);
//			
//			std::string script = row["describe"].c_str();
//			entry.set_describe(script.c_str());
//			_map_spirit_shop[entry.index()] = entry;
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from `lotion_shop_config`;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			message::MsgLotionShopConfigInfo entry_config;
//			entry_config.set_lotion_id(row["lotion_id"]);
//			int use_type = row["use_type"];
//			entry_config.set_use_type((message::LotionUseType)use_type);
//			entry_config.set_use_count(row["use_count"]);
//			entry_config.set_resource_id(row["resource_id"]);
//			entry_config.set_describe(row["describe"].c_str());
//			entry_config.set_big_resource_id(row["big_resource_id"]);
//			entry_config.set_name(row["name"].c_str());
//			entry_config.set_spell_id(row["spell_id"]);
//			_map_lotion_shop_configs[entry_config.lotion_id()] = entry_config;
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from `lottery_draw_box_config`;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			LotteryDrawBoxConfig lotteryConfig;
//			DBRow& row = sResult[i];
//			int temp_type = row["type"];
//
//			lotteryConfig.lottery_type_ = (message::enLotteryBox)temp_type;
//			lotteryConfig.sub_index_ = row["sub_type"];
//			lotteryConfig.base_count_ = row["base_count"];
//			lotteryConfig.random_count_ = row["randdom_count"];
//			lotteryConfig.rating_ = row["rating"];
//			_lottery_draw_configs.push_back(lotteryConfig);
//		}
//		gHttpManager.setChannel(_global_config.channel_id_);
//		gHttpManager.setGameID(_global_config.game_id_);
//
//		query.reset();
//		sResult.clear();
//		query << "select * from daily_game_prize;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			DailyGamePrizeConfig entry;
//			entry.begin_rank_ = row["rank_begin"];
//			entry.end_rank_ = row["rank_end"];
//			entry.prize_gold_ = row["gold"];
//			_daily_game_prize_configs.push_back(entry);
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from daily_game_record_config ORDER by daily_game_record_progress ASC;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			int daily_game_record_progress = row["daily_game_record_progress"];
//			_global_config.daily_game_record_config_.push_back(daily_game_record_progress);
//		}
//
//		query.reset();
//		sResult.clear();
//		query << "select * from daily_game_reset_config ORDER by reset_jewel ASC;";
//		sResult = query.store();
//		rows_length = sResult.num_rows();
//		for (int i = 0; i < rows_length; i++)
//		{
//			DBRow& row = sResult[i];
//			int reset_jewel = row["reset_jewel"];
//			_global_config.daily_game_reset_jewel_config_.push_back(reset_jewel);
//		}
//
//
//
//
//	}	
//	
//	//sprintf(sz_temp, "%d;%d;%d", _game_id, _server_char, _server_type);
//	//_server_title = sz_temp;
//}
//
//void GameConfig::generateTitle()
//{
//	char sz_temp[512];
//	sprintf(sz_temp, "%d;%d;%d", _game_id, _server_char, _server_type);
//	_server_title = sz_temp;
//}
//
//const char* GameConfig::getServerTitle()
//{
//	return _server_title.c_str();
//}