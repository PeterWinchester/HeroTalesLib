/* bomb.cpp
   Created - 2025/2/7
*/

#include "cards/bomb.h"

void AbandonBomb(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
    if (player[arg_player].num_cards_in_hand_ <= 4) return; // 确认是否超过四张手牌
    if (!CheckBomb(arg_player)) return;                     // 确认是否有炸弹怪

    char ch = 0;

    if (arg_player == 1) {
        printf("现在你的手牌超过 4 张，是否丢弃你场上所有的 ");
        DisplayCard(card[69]);
        printf("？(y/n)\n");

        while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N') ch = _getch();
    }

    if (arg_player != 1 || ch == 'y' || ch == 'Y') { // 丢弃炸弹怪
        for (int i = 0; i < player[arg_player].num_cards_on_field_;) {
            if (player[arg_player].cards_on_field_[i].name_ == "炸弹怪") {
                AbandonCard(arg_player, i, CARD_STATUS_ON_FIELD, arg_global_data);
            } else i++;
        }
        arg_basic_func.pfn_gaming_interface_(arg_global_data);
    }

    if (arg_player != 1) {
        printf("此时玩家 %d 的手牌超过 4 张，丢弃了场上所有的 ", arg_player);
        DisplayCard(card[69]);
        printf("。\n");
        Pause();
    }
}

bool CheckBomb(int arg_player) {
    for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
        if (player[arg_player].cards_on_field_[i].name_ == "炸弹怪") return true;
    }
    return false;
}

bool Bomb(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	player[arg_player].num_action_points_--;

	int target = rand() % arg_global_data.num_players_ + 1;
	while (target == arg_player) target = rand() % arg_global_data.num_players_ + 1;

	if (arg_player == 1) {
		// 选择一名玩家的场放置炸弹怪
		printf("请选择你要在其场上放置 ");
		DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		printf("的玩家（输入玩家编号）：\n");
		target = restricted_input_int(2, arg_global_data.num_players_);
	}

	// 将炸弹怪放置在指定玩家场上
	player[arg_player].cards_in_hand_[arg_card].status_ = CARD_STATUS_ON_FIELD;
	player[target].cards_on_field_.push_back(player[arg_player].cards_in_hand_[arg_card]);
	player[target].num_cards_on_field_++;
	player[arg_player].cards_in_hand_.erase(player[arg_player].cards_in_hand_.begin() + arg_card);
	player[arg_player].num_cards_in_hand_--;
	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player != 1) {
		printf("玩家 %d 将 ", arg_player);
		DisplayCard(player[target].cards_on_field_.back());
		printf("放在了玩家 %d 的场上。\n", target);

		IllustrateCard(player[target].cards_on_field_.back());
		Pause();
	}

	CheckTyrant(arg_player, arg_basic_func, arg_global_data); // 检查魔王
	return true;
}

int calc_using_pref_bomb(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
	int preference = 0;

	// 检查魔王，如果有魔王，偏好值加 2
	if (CheckTyrant(arg_player, arg_basic_func, arg_global_data)) preference += 2;

	// 检查其他玩家的场，如果有持续牌，偏好值加 1
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		bool found_consistent = false;
		for (int j = 0; j < player[i].num_cards_on_field_; j++) {
			if (player[i].cards_on_field_[j].type_ == CARD_TYPE_CONSISTENT) {
				preference++;
				found_consistent = true;
				break;
			}
		}
		if (found_consistent) break;
	}

	return preference;
}
