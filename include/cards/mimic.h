/* mimic.h
   Created - 2025/2/6
*/

#ifndef MIMIC_H
#define MIMIC_H

// 宝箱怪触发类型相关宏定义
#define MIMIC_TRIGGER_GET_COIN       0 // 拿钱
#define MIMIC_TRIGGER_GET_TWO_CARDS  1 // 摸两张牌

#include "htplayer.h"
#include "htgame.h"
#include "cards/bomb.h"
#include "cards/dancer.h"

// 检查 arg_player 以外的玩家是否有宝箱怪，如果有，则触发。
// arg_type 为玩家 arg_player 触发宝箱怪的方式，即摸两张牌或获得金币
bool CheckMimic(
   int          arg_player,
   int          arg_type,
   HTBasicData& arg_global_data,
   HTBasicFunc& arg_basic_func
);

#endif // MIMIC_H
