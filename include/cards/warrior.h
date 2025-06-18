/* warrior.h
   Created - 2025/2/7
*/

#ifndef WARRIOR_H
#define WARRIOR_H

#define DONNOT_USE_SWORD 0
#define USE_SAINT_SWORD  1
#define USE_BLADE        2

#include <vector>
#include "htframe.h"
#include "htcards_basic.h"
#include "htplayer.h"
#include "htgame.h"
#include "cards/saint_sword.h"
#include "cards/nun.h"
#include "cards/minister.h"
#include "cards/mimic.h"
#include "cards/blade.h"

// 检查 arg_player 以外的玩家手上是否有紫牌
bool CheckPurpleCards(int arg_player, HTBasicData& arg_global_data);

#endif // WARRIOR_H
