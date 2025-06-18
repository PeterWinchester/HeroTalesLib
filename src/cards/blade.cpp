/* blade.cpp
   Created - 2025/2/7
*/

#include "cards/blade.h"

bool CheckBlade(int arg_player) {
    for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
		Card c = player[arg_player].cards_on_field_[i];
        if (c.name_ == "魔剑" && !c.is_transversed_) return true;
    }
    return false;
}

bool Blade(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	player[arg_player].num_action_points_--;

	PutOnField(arg_player, arg_card, arg_mode, arg_global_data);

	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player == 1) printf("你");
	else printf("玩家 %d ", arg_player);

	DisplayCard(player[arg_player].cards_on_field_.back());
	printf("放在了场上。\n");

	if (arg_player != 1) IllustrateCard(player[arg_player].cards_on_field_.back());
	Pause();
	return true;
}

int calc_using_pref_blade(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查手牌，如果有勇者或狂战士，则偏好值加 1
	for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].name_ == "勇者" ||
			player[arg_player].cards_in_hand_[i].name_ == "狂战士") {
			preference++;
			break;
		}
	}

	// 检查火龙，若其他玩家场上有火龙，则偏好值减 1
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (CheckDragon(i)) {
			preference--;
			break;
		}
	}

	return preference;
}
