/* tyrant.h
   Created - 2025/2/6
*/

#ifndef TYRANT_H
#define TYRANT_H

#include "htplayer.h"
#include "cards/mimic.h"
#include "cards/dancer.h"

// 检查玩家 arg_player 场上是否有魔王，如果有，选择是否横置
bool CheckTyrant(int arg_player, HTBasicFunc& arg_basic_func, HTBasicData& arg_global_data);

/* [魔]魔王[持续]
   当你打出一张带有 Lv 的紫色牌后，横置本牌，你 +1 金币。
*/
bool Tyrant(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_tyrant(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // TYRANT_H
