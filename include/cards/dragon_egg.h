/* dragon_egg.h
   Created - 2025/2/6
*/

#ifndef DRAGON_EGG_H
#define DRAGON_EGG_H

#include "htframe.h"
#include "htcards_basic.h"
#include "htplayer.h"
#include "htgame.h"

/* [火]龙蛋
   从紫色牌库或弃牌区选一张[火]加入手牌。
*/
bool DragonEgg(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_dragon_egg(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // DRAGON_EGG_H
