/* holy_knight.h
   Created - 2025/2/6
*/

#ifndef HOLY_KNIGHT_H
#define HOLY_KNIGHT_H

#include "htplayer.h"
#include "htgame.h"
#include "cards/nun.h"
#include "cards/bomb.h"

// 检查玩家 arg_player 手中是否有圣骑士
bool CheckHolyKnight(int arg_player);

// 使用圣骑士（攻击有效返回 false，攻击无效返回 true）
bool UseHolyKnight(
	int          arg_attacker,
	int          arg_target,
	int          arg_card,
	int          arg_mode,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // HOLY_KNIGHT_H
