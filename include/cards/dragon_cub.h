/* dragon_cub.h
   Created - 2025/2/6
*/

#ifndef DRAGON_CUB_H
#define DRAGON_CUB_H

#include "htframe.h"
#include "htcards_basic.h"
#include "htplayer.h"
#include "cards/guard.h"
#include "cards/holy_knight.h"
#include "cards/minister.h"
#include "cards/mimic.h"

/* [火]龙幼崽[攻击]
   选择每个场上有牌的对手，令他们场上的一张牌返回手牌。若那些牌均带有 Lv，你 +1 金币。
*/
bool DragonCub(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_dragon_cub(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // DRAGON_CUB_H
