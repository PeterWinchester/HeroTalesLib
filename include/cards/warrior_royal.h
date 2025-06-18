/* warrior_royal.h
   Created - 2025/2/6
*/

#ifndef WARRIOR_ROYAL_H
#define WARRIOR_ROYAL_H

#include "cards/warrior.h"

/* [皇]勇者[攻击]
   将一名对手的一张非黄色手牌置于其场上，若该手牌带有 Lv 或 [魔]，你 +1 金币。
*/
bool WarriorRoyal(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

// [皇]勇者 AI 选择攻击目标
int warrior_royal_choose_target(int arg_player, HTBasicData& arg_global_data);

// [皇]勇者 AI 选择用剑
int warrior_royal_choose_sword(int arg_player, HTBasicData& arg_global_data);

// 计算打出[皇]勇者的偏好值
int calc_using_pref_warrior_royal(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // WARRIOR_ROYAL_H
