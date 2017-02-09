#pragma once
enum RecordType
{
	RecordTypeLogin,
	RecordTypeLoginOut,
	RecordTypeEnterGame,
	RecordTypeLeaveGame,
	RecordTypeTaskComplete,
	RecordTypeTaskAccepte,
	RecordTypeTaskGiveUp,
	RecordTypeChapterUnlock,
	RecordTypeGoldModify,
	RecordTypeBuyHero,
	RecordTypeDealWaitToPay,
	RecordTypeDealToPay,
	RecordTypeWaitToVerify,
	RecordTypeGiveUpDeal,
	RecordTypeRelive,
	RecordTypeOnlineCount,
	RecordTypeBuySpirit,
	RecordDailyGame,
	RecordDailyGameReward,
	RecordDailyLotteryRecord,
	RecordCreateName,
	RecordTypeMax
};


class RecordManager
{
public:
	typedef std::vector<std::string> RECORDS;
	enum GoldModifyType
	{
		GoldModify_LeaveGame,
		GoldModify_KillMonster,
		GoldModify_CompleteTask,
		GoldModify_UnlockChapter,
		GoldModify_BuyHero,
		GoldModify_BuyGold,
		GoldModify_AcceptTask,
		GoldModify_ReliveRecord,
		GoldModify_DailyGameReward,
		GoldModify_DailyLottery,
	};
public:
	RecordManager();
	virtual ~RecordManager();
public:
	const char* getCurTime();
	void update();
public:
	RECORDS _record[RecordTypeMax];
	std::string _sql_head[RecordTypeMax];
	char _szTemp[10240];
	std::string _cur_time;
};

