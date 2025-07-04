/* tyrant.cpp
   Created - 2025/2/7
*/

#include "cards/tyrant.h"

bool CheckTyrant(int arg_player, HTBasicFunc& arg_basic_func, HTBasicData& arg_global_data) {
    bool found_tyrant = false;
    for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
        if (player[arg_player].cards_on_field_[i].name_ == "魔王") {
            found_tyrant = true;
            break;
        }
    }
    if (!found_tyrant) return false;

    char ch = 0;

    if (arg_player == 1) {
        printf("你场上有 ");
		DisplayCard(card[53]);
		printf("，是否横置？(y/n)\n");

        while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N') ch = _getch();
    }

    if (arg_player != 1 || ch == 'y' || ch == 'Y') {
        player[arg_player].num_coins_++;

        arg_basic_func.pfn_gaming_interface_(arg_global_data);

        if (arg_player == 1) printf("你");
        else printf("玩家 %d ", arg_player);

        printf("横置了 ");
        DisplayCard(card[53]);
        printf("，+1 金币！\n");
        Pause();

        if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
            arg_global_data.win_player_ = arg_player;
            arg_global_data.game_status_ = 0;
            return true;
        }

        CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);

        CheckDancer(arg_player, arg_global_data, arg_basic_func);
        if (arg_global_data.game_status_ != 1) return true;
    }
    return false;
}

bool Tyrant(
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

	printf("将 ");
	DisplayCard(player[arg_player].cards_on_field_.back());
	printf("放在了场上。\n");
	if (arg_player != 1) IllustrateCard(player[arg_player].cards_on_field_.back());
	Pause();
	return true;
}

int calc_using_pref_fire_dragon(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 2; // 魔王太厉害了，初始值应该是 2

	// 检查手牌，如果有带 Lv 的紫牌，则偏好值加 2
	for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].color_ == CARD_COLOR_PURPLE
			&& player[arg_player].cards_in_hand_[i].level_ != CARD_NO_LEVEL) {
			preference += 2;
			break;
		}
	}

	// 检查火龙，如果其他玩家有火龙，则偏好值减 1
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (CheckDragon(i)) {
			preference--;
			break;
		}
	}

	return preference;
}
