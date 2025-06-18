/* princess.h
   Created - 2025/2/6
*/

#ifndef PRINCESS_H
#define PRINCESS_H

#include "htplayer.h"
#include "htgame.h"
#include "cards/fire_dragon.h"
#include "cards/bomb.h"

// 检查公主，此函数返回玩家 arg_player 场上是否有公主
bool CheckPrincess(int arg_player);

/* [皇]公主[持续]
   打出本牌不消耗行动点，若本牌在你场上，在你的准备阶段，你 +1 金币。
*/
bool Princess(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

// 计算打出公主的偏好值
int calc_using_pref_princess(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // PRINCESS_H
