/* guard.cpp
   Created - 2025/2/7
*/

#include "cards/guard.h"

bool CheckGuard(int arg_player) {
    for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].name_ == "卫兵") return true;
	}
	return false;
}

void UseGuard(
	int          arg_attacker,
	int          arg_target,
	int          arg_card,
	int          arg_mode,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	PutOnField(arg_attacker, arg_card, arg_mode, arg_global_data);

	for (int i = 0; i < player[arg_target].num_cards_in_hand_; i++) {
		if (player[arg_target].cards_in_hand_[i].name_ == "卫兵") {
			// 丢弃卫兵
			AbandonCard(arg_target, i, CARD_STATUS_IN_HAND, arg_global_data);
			arg_basic_func.pfn_gaming_interface_(arg_global_data);
			CheckNun(arg_target, arg_global_data);

			// 从牌库抽一张牌
			GetOneCardFromLib(arg_target);
			AbandonBomb(arg_target, arg_global_data, arg_basic_func);
			break;
		}
	}

	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_target == 1) printf("你");
	else printf("玩家 %d ", arg_target);

	printf("的卫兵防住了");

	if (arg_attacker == 1) printf("你");
	else printf("玩家 %d ", arg_attacker);

	printf("的攻击。\n");
	Pause();
}
