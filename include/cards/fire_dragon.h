/* fire_dragon.h
   Created - 2025/2/6
*/

#ifndef FIRE_DRAGON_H
#define FIRE_DRAGON_H

#include "htplayer.h"
#include "htgame.h"

/* [魔][火]火龙[持续]
   横置，将弃牌区的一张[火]不消耗行动点打出，或将其加入手牌。
*/
bool FireDragon(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_fire_dragon(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

// 检查玩家 arg_player 场上是否有火龙
bool CheckDragon(int arg_player);

#endif // FIRE_DRAGON_H
