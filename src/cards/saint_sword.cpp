/* saint_sword.cpp
   Created - 2025/2/7
*/

#include "cards/saint_sword.h"

bool CheckSaintSword(int arg_player) {
    for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
        if (player[arg_player].cards_on_field_[i].name_ == "圣剑") return true;
    }
    return false;
}

bool SaintSword(
    int          arg_player,
    int          arg_card,
    int          arg_status,
    int          arg_mode,
    HTBasicData& arg_global_data,
    HTBasicFunc& arg_basic_func
) {
    if (arg_status != CARD_STATUS_IN_HAND) return false;
    
    player[arg_player].num_action_points_--;
    PutOnField(arg_player, arg_card, arg_mode, arg_global_data);

    arg_basic_func.pfn_gaming_interface_(arg_global_data);
    
    if (arg_player == 1) printf("你");
    else printf("玩家 %d ", arg_player);

    printf("将");
    DisplayCard(player[arg_player].cards_on_field_.back());
    printf("放在了场上。\n");
    Pause();
    return true;
}

int calc_using_pref_saint_sword(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
    int preference = 0;

	// 检查手牌，如果有勇者或狂战士，则偏好值加 1
	for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].name_ == "勇者"
            || player[arg_player].cards_in_hand_[i].name_ == "狂战士") {
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

void TransverseSaintSword(int arg_player) {
	for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
		Card c = player[arg_player].cards_on_field_[i];
	}
}
