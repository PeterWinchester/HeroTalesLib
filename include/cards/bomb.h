/* bomb.h
   Created - 2025/2/6
*/

#ifndef BOMB_H
#define BOMB_H

#include "htplayer.h"
#include "htgame.h"
#include "htcards_basic.h"
#include "htframe.h"
#include "cards/tyrant.h"

// 检查玩家 arg_player 场上是否有炸弹怪，如果有，检查是否可以丢弃
void AbandonBomb(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func);

// 检查玩家 arg_player 场上是否有炸弹怪
bool CheckBomb(int arg_player);

/* Lv.1 炸弹怪[持续]
   放置到对手场上成为他的牌。若你的场上放置了本牌，在准备阶段前，需选择你场上另一张牌返回手中。
   任何情况使你手牌数不小于5时，可丢弃本牌。
*/
bool Bomb(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

int calc_using_pref_bomb(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func);

#endif // BOMB_H
