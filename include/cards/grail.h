/* grail.h
   Created - 2025/2/6
*/

#ifndef GRAIL_H
#define GRAIL_H

#include "htframe.h"
#include "htplayer.h"
#include "htgame.h"
#include "cards/bomb.h"

// 检查圣杯，此函数在玩家 arg_player 场上有圣杯且只差一块钱获胜时返回真
bool CheckGrail(int arg_player, HTBasicData& arg_global_data);

/* [皇]圣杯[持续]
   在你的准备阶段，若只差 1 金币获胜，则直接获胜。
*/
bool Grail(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

// 计算打出圣杯的偏好值
int calc_using_pref_grail(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // GRAIL_H
