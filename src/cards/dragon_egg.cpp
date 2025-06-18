/* dragon_egg.cpp
   Created - 2025/4/15
*/

#include "cards/dragon_egg.h"

bool DragonEgg(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	player[arg_player].num_action_points_--;

	// 如果不是火龙模式，需丢弃龙蛋
	if (arg_mode != CARD_DRAGON_MODE) {
		AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
	}

	if (arg_player != 1) {
		printf("玩家 %d 打出了 ", arg_player);

		if (arg_mode == CARD_DRAGON_MODE) DisplayCard(cards_abandoned[arg_card]);
		else DisplayCard(cards_abandoned.back());

		printf("。\n");

		if (arg_mode == CARD_DRAGON_MODE) IllustrateCard(cards_abandoned[arg_card]);
		else IllustrateCard(cards_abandoned.back());

		Pause();
	}

	if (arg_mode != CARD_DRAGON_MODE) CheckNun(arg_player, arg_global_data);

	// 统计弃牌区的[火]
	int num_fire_abandoned = 0;     // 弃牌区[火]的数量
	std::vector<int> fire_abandoned; // 弃牌区[火]的编号
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].fire_property_ == CARD_PROPERTY_FIRE) {
			num_fire_abandoned++;
			fire_abandoned.push_back(i);
		}
	}

	if (num_fire_abandoned) { // 弃牌区有[火]
		int ch = rand() % 2 + 1;
		if (arg_player == 1) {
			// 选择从牌库或弃牌区拿取[火]
			printf("牌库和弃牌区都有[火]，你想从哪里拿取？\n");
			printf("1.牌库 2.弃牌区\n");
			ch = restricted_input_int(1, 2);
		}

		if (ch == 1) { // 从牌库拿取[火]
			int ch1 = rand() % 3 + 1;
			if (arg_player == 1) {
				// 选择要拿取的[火]
				printf("请选择你想要的[火]：\n");
				printf("1.火龙 2.龙炎 3.龙幼崽 4.龙蛋\n");
				ch1 = restricted_input_int(1, 4);
			}

			int card_chosen;

			switch (ch1) {
			case 1: // 选择火龙
				for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
					if (card[i].name_ == "火龙") {
						card_chosen = i;
						break;
					}
				}
				break;
			case 2: // 选择龙炎
				for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
					if (card[i].name_ == "龙炎") {
						card_chosen = i;
						break;
					}
				}
				break;
			case 3: // 选择龙幼崽
				for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
					if (card[i].name_ == "龙幼崽") {
						card_chosen = i;
						break;
					}
				}
				break;
			case 4: // 选择龙蛋
				for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
					if (card[i].name_ == "龙蛋") {
						card_chosen = i;
						break;
					}
				}
				break;
			}

			card[card_chosen].status_ = CARD_STATUS_IN_HAND;
			player[arg_player].cards_in_hand_.push_back(card[card_chosen]);
			player[arg_player].num_cards_in_hand_++;
			card[card_chosen].status_ = CARD_STATUS_IN_LIBRARY;			

			if (arg_player != 1) {
				arg_basic_func.pfn_gaming_interface_(arg_global_data);
				printf("玩家 %d 从牌库获取了一张 ", arg_player);
				DisplayCard(player[arg_player].cards_in_hand_.back());
				printf("。\n");
				Pause();
			}
		} else { // 从弃牌区拿取[火]
			int ch1 = rand() % num_fire_abandoned;

			if (arg_player == 1) {
				// 选择弃牌区的[火]
				printf("请选择弃牌区的一张[火]：\n");
				for (int i = 0; i < num_fire_abandoned; i++) {
					printf("%d.", i + 1);
					DisplayCard(cards_abandoned[fire_abandoned[i]]);
				}
				printf("\n");
				ch1 = restricted_input_int(1, num_fire_abandoned) - 1;
			}

			AddAbandonedCardToHand(arg_player, fire_abandoned[ch1], arg_global_data);

			if (arg_player != 1) {
				arg_basic_func.pfn_gaming_interface_(arg_global_data);
				printf("玩家 %d 从弃牌区获取了一张 ", arg_player);
				DisplayCard(player[arg_player].cards_in_hand_.back());
				printf("。\n");
				Pause();
			}
		}
	} else { // 弃牌区没有[火]
		int ch1 = rand() % 3 + 1;
		if (arg_player == 1) {
			// 选择要拿取的[火]
			printf("请选择你想要的[火]：\n");
			printf("1.火龙 2.龙炎 3.龙幼崽 4.龙蛋\n");
			ch1 = restricted_input_int(1, 4);
		}

		int card_chosen;

		switch (ch1) {
		case 1: // 选择火龙
			for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
				if (card[i].name_ == "火龙") {
					card_chosen = i;
					break;
				}
			}
			break;
		case 2: // 选择龙炎
			for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
				if (card[i].name_ == "龙炎") {
					card_chosen = i;
					break;
				}
			}
			break;
		case 3: // 选择龙幼崽
			for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
				if (card[i].name_ == "龙幼崽") {
					card_chosen = i;
					break;
				}
			}
			break;
		case 4: // 选择龙蛋
			for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
				if (card[i].name_ == "龙蛋") {
					card_chosen = i;
					break;
				}
			}
			break;
		}

		card[card_chosen].status_ = CARD_STATUS_IN_HAND;
		player[arg_player].cards_in_hand_.push_back(card[card_chosen]);
		player[arg_player].num_cards_in_hand_++;
		card[card_chosen].status_ = CARD_STATUS_IN_LIBRARY;			

		if (arg_player != 1) {
			arg_basic_func.pfn_gaming_interface_(arg_global_data);
			printf("玩家 %d 从牌库获取了一张 ", arg_player);
			DisplayCard(player[arg_player].cards_in_hand_.back());
			printf("。\n");
			Pause();
		}
  	}
	return true;
}

int calc_using_pref_dragon_egg(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 2; // 直接拿火龙，不必多说
	return preference;
}
