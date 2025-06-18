/* htframe.h
   Created - 2025/2/5
*/

#ifndef HTFRAME_H
#define HTFRAME_H

// 游戏状态相关宏定义
#define GAME_STATUS_RUNNING          1 // 游戏正在运行
#define GAME_STATUS_OVER             0 // 游戏结束
#define GAME_STATUS_EXIT            -1 // 游戏中止

const int kMaxNumPlayers = 10; // 最大玩家数
const int kNumYellowCards = 49, kNumPurpleCards = 49;

class HTBasicData { // 用于保存全局变量的类，使用时定义一个此类的对象以存储全局变量
public:
	// game_status_：游戏状态，决定游戏正在进行或已经结束。
	// 可取值宏：
	// GAME_STATUS_RUNNING 正在进行
	// GAME_STATUS_OVER    正常结束，即分出胜负
	// GAME_STATUS_EXIT    非正常结束，即玩家中止游戏
	int game_status_;
	// num_player_：每局游戏的玩家数量，在每一局游戏开始前由玩家设定，其值不应超过 kMaxNumPlayers
	int num_players_;
	// win_coin_number_：每局游戏的获胜金币数，在每一局游戏开始前由玩家设定。
	// 理论上来说可以是 int 范围内的任何正整数(>_<!)
	int win_coin_number_;
	// win_player_：获胜的玩家，当这个值确定时，往往是游戏结束的时候
	int win_player_;
	// num_cards_abandoned_：弃牌区的卡牌数量，在每一局游戏开始前都会清零
	int num_cards_abandoned_;
	// card_used_by_monk_：被僧侣使用的卡牌在弃牌区内的编号
	int card_used_by_monk_;
	// card_used_by_dragon_：被火龙使用的卡牌在弃牌区的编号
	int card_used_by_dragon_;
	// attacking_player_：正在发动攻击的玩家编号
	int attacking_player_;

	HTBasicData();
};

class HTBasicFunc { // 用于保存常用的基本函数指针的类，这些基本函数可以使用默认的，也可以自定义
	public:
	void (*pfn_gaming_interface_)(HTBasicData&); // 游戏中界面显示函数指针

	HTBasicFunc();
};

#endif // HTFRAME_H
