/* black_knight.h
   Created - 2025/2/6
*/

#ifndef BLACK_KNIGHT_H
#define BLACK_KNIGHT_H

#include "htframe.h"
#include "htcards_basic.h"
#include "htplayer.h"
#include "htgame.h"
#include "cards/mimic.h"

/* [皇][魔]黑骑士[攻击]
   放置一张对手手牌于其场上，若带有 Lv, 你 +1 金币；若带有纹章，则从任意处将“魔剑”加入手牌。
*/
bool BlackKnight(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_black_knight(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // BLACK_KNIGHT_H
