/* minister.h
   Created - 2025/2/6
*/

#ifndef MINISTER_H
#define MINISTER_H

#include "htplayer.h"
#include "htgame.h"
#include "bomb.h"

// 检查玩家 arg_player 场上是否有大臣，如果有则选择是否横置
// 在 arg_player 受到的攻击结算后调用此函数
bool CheckMinister(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func);

/* [皇]大臣[持续]
   当你被[攻击]卡牌指定时，待[攻击]卡牌结算后，若本牌在你场上，可横置本牌，你抽一张牌。
*/
bool Minister(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

// 计算打出大臣的偏好值
int calc_using_pref_minister(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // MINISTER_H
