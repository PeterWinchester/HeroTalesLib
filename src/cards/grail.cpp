/* grail.cpp
   Created - 2025/2/7
*/

#include "cards/grail.h"

bool CheckGrail(int arg_player, HTBasicData& arg_global_data) {
	if (player[arg_player].num_coins_ < arg_global_data.win_coin_number_ - 1) return false;
	for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
		if (player[arg_player].cards_on_field_[i].name_ == "圣杯") return true;
	}
    return false;
}

bool Grail(
	int          arg_player,
	int          arg_card,
	int          arg_status,
	int          arg_mode,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
) {
	if (arg_status == CARD_STATUS_IN_HAND) {                       // 如果圣杯的状态为在手中
		player[arg_player].num_action_points_--;
		PutOnField(arg_player, arg_card, arg_mode, arg_global_data);

		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);

		printf("将 ");
		DisplayCard(player[1].cards_on_field_.back());
		printf("放在了场上。\n");
		Pause();
		return true;
	}
	return false;
}

int calc_using_pref_grail(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查金币数，若差一个获胜，则偏好值加 2；若差 2 个获胜，则偏好值加 1
	if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_ - 1) preference += 2;
	else if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_ - 2) preference++;

	// 检查炸弹怪，若有炸弹怪，则偏好值减 1
	if (CheckBomb(arg_player)) preference--;

	return preference;
}
