/* blacksmith.h
   Created - 2025/2/6
*/

#ifndef BLACKSMITH_H
#define BLACKSMITH_H

#include "htframe.h"
#include "htcards_basic.h"
#include "htplayer.h"
#include "htgame.h"
#include "cards/nun.h"
#include "cards/dancer.h"

/* Lv.0 铁匠
   将两张手牌放置在你场上，若因此放置的手牌 Lv 或纹章相同，你 +1 金币。
*/
bool BlackSmith(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

// 计算打出铁匠的偏好值
int calc_using_pref_blacksmith(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // BLACKSMITH_H
