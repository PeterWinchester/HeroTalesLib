/* holy_knight.cpp
   Created - 2025/2/7
*/

#include "cards/holy_knight.h"

bool CheckHolyKnight(int arg_player) {
    for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].name_ == "圣骑士") return true;
	}
	return false;
}

bool UseHolyKnight(
	int          arg_attacker,
	int          arg_target,
	int          arg_card,
	int          arg_mode,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	// 选择圣骑士使用方案
	char option_chosen = '1' + rand() % 2;

	if (arg_target == 1) {
		printf("请选择圣骑士使用方案：\n");
		printf("1.攻击有效，你抽两张牌\n");
		printf("2.攻击无效，你抽一张牌。\n");

		option_chosen = _getch();
		while (option_chosen != '1' && option_chosen != '2') option_chosen = _getch();
	} else {
		printf("玩家 %d 触发圣骑士，选择抽", arg_target);

		if (option_chosen == '1') printf("两张牌，此时攻击有效。\n");
		else printf("一张牌，此时攻击无效。\n");
		Pause();
	}

	// 丢弃圣骑士
	for (int i = 0; i < player[arg_target].num_cards_in_hand_; i++) {
		if (player[arg_target].cards_in_hand_[i].name_ == "圣骑士") {
			AbandonCard(arg_target, i, CARD_STATUS_IN_HAND, arg_global_data);
			arg_basic_func.pfn_gaming_interface_(arg_global_data);
			CheckNun(arg_target, arg_global_data);
			break;
		}
	}

	if (option_chosen == '1') { // 攻击有效
		// 从牌库抽取两张牌
		GetOneCardFromLib(arg_target);
		AbandonBomb(arg_target, arg_global_data, arg_basic_func);
		GetOneCardFromLib(arg_target);
		AbandonBomb(arg_target, arg_global_data, arg_basic_func);
		
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		return false;
	}

	// 攻击无效
	// 如果攻击卡牌是僧侣或火龙打出的，要从弃牌区将其取出，加入攻击者手牌
	if (arg_mode != CARD_ORDINARY_MODE) {
		AddAbandonedCardToHand(arg_attacker, arg_card, arg_global_data);
	}

	// 从牌库抽一张牌
	GetOneCardFromLib(arg_target);
	AbandonBomb(arg_target, arg_global_data, arg_basic_func);

	arg_basic_func.pfn_gaming_interface_(arg_global_data);
	return true;
}
