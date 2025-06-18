/* berserker.h
   Created - 2025/2/6
*/

#ifndef BERSERKER_H
#define BERSERKER_H

#include "cards/warrior.h"

/* Lv.4 狂战士[攻击]
   指定一名对手的全部非黄色手牌放置于其场上，若均带有 Lv，你 +1 金币，本牌名称也视作“勇者”。
*/
bool Berserker(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
);

// 狂战士 AI 选择攻击目标
int berserker_choose_target(int arg_player, HTBasicData& arg_global_data);

// 狂战士 AI 选择用剑
int berserker_choose_sword(int arg_player, HTBasicData& arg_global_data);

int calc_using_pref_berserker(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	);

#endif // BERSERKER_H
