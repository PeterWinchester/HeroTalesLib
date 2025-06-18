/* saint_sword.h
   Created - 2025/2/6
*/

#ifndef SAINT_SWORD_H
#define SAINT_SWORD_H

#include "htplayer.h"
#include "htgame.h"
#include "cards/fire_dragon.h"

// 检查玩家 arg_player 场上是否有圣剑
bool CheckSaintSword(int arg_player);

/* [皇]圣剑[持续]
   当你使用勇者时，横置本牌，将勇者的效果改为丢弃对手场上的一张牌，若丢弃的牌 Lv 低于勇者，你 +1 金币。
*/
bool SaintSword(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

// 计算打出圣剑的偏好值
int calc_using_pref_saint_sword(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

// 横置玩家场上的一张圣剑
void TransverseSaintSword(int arg_player);

#endif // SAINT_SWORD_H
