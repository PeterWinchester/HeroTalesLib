/* nun.h
   Created - 2025/2/6
*/

#ifndef NUN_H
#define NUN_H

#include "htplayer.h"
#include "htcards_basic.h"
#include "htframe.h"
#include "htgame.h"

// 此函数检查 arg_player 以外的玩家是否有修女，如果有修女，进行触发（当有牌进入弃牌区时调用此函数）
bool CheckNun(int arg_player, HTBasicData& arg_global_data);

#endif // NUN_H
