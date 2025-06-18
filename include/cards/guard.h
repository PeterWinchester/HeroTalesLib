/* guard.h
   Created - 2025/2/6
*/

#ifndef GUARD_H
#define GUARD_H

#include "htplayer.h"
#include "htgame.h"
#include "cards/nun.h"
#include "cards/bomb.h"

// 检查玩家 arg_player 手中是否有卫兵
bool CheckGuard(int arg_player);

// 使用卫兵，参数含义同 Defend 函数
void UseGuard(
	int          arg_attacker,
	int          arg_target,
	int          arg_card,
	int          arg_mode,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // GUARD_H
