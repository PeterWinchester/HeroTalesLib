/* wolfman.cpp
   Created - 2025/5/13
*/

#include "cards/wolfman.h"

bool Wolfman(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// 统计弃牌区的纹章牌和带 Lv 的紫牌
	int num_purple_cards = 0, num_armory_cards = 0;
	std::vector<int> purple_cards, armory_cards;
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].color_ == CARD_COLOR_PURPLE &&
			cards_abandoned[i].level_ != CARD_NO_LEVEL) {
			num_purple_cards++;
			purple_cards.push_back(i);
		}
		if (cards_abandoned[i].armory_ != CARD_ARMORY_NO_ARMORY) {
			num_armory_cards++;
			armory_cards.push_back(i);
		}
	}
		
	if (!num_purple_cards && !num_armory_cards) { // 既没有带 Lv 的紫牌又没有纹章牌
		if (arg_player == 1) {
			printf("弃牌区既没有带 Lv 的紫牌，也没有带纹章的牌，不能使用 ");
			DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
			printf("！\n");
			Pause();
		}
		return false;
	}

	player[arg_player].num_action_points_--;

	if (arg_player != 1) {
		printf("玩家 %d 打出了 ", arg_player);
		DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		printf("。\n");

		IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		Pause();
	}

	// 丢弃狼人
	AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);
	CheckNun(arg_player, arg_global_data);

	// 检查魔王
	CheckTyrant(arg_player, arg_basic_func, arg_global_data);
	if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

	// 选择弃牌区符合要求的牌
	int ch = rand() % (num_purple_cards + num_armory_cards);
	if (arg_player == 1) {
		printf("请选择弃牌区的一张牌：\n");
		for (int i = 0; i < num_purple_cards; i++) {
			printf("%d.", i + 1);
			DisplayCard(cards_abandoned[purple_cards[i]]);
		}
		for (int i = 0; i < num_armory_cards; i++) {
			printf("%d.", i + 1 + num_purple_cards);
			DisplayCard(cards_abandoned[armory_cards[i]]);
		}
		printf("\n");
		ch = restricted_input_int(1, num_purple_cards + num_armory_cards) - 1;
	}

	if (ch < num_purple_cards) { // 选择带 Lv 的紫牌
		// 将选中牌放到场上
		Card c = cards_abandoned[purple_cards[ch]];
		
		c.status_ = CARD_STATUS_ON_FIELD;
		player[arg_player].cards_on_field_.push_back(c);
		player[arg_player].num_cards_on_field_++;
		cards_abandoned.erase(cards_abandoned.begin() + purple_cards[ch]);
		arg_global_data.num_cards_abandoned_--;

		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);

		printf("将弃牌区的一张 ");
		DisplayCard(c);
		printf("放在了场上。\n");
	} else { // 选择纹章牌
		AddAbandonedCardToHand(arg_player, armory_cards[ch - num_purple_cards], arg_global_data);

		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);

		printf("将弃牌区的一张 ");
		DisplayCard(player[arg_player].cards_in_hand_.back());
		printf("加入了手牌。\n");
	}
	Pause();
	return true;
}

int calc_using_pref_wolfman(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查其他玩家的场，如果有火龙，则偏好值减 1
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (CheckDragon(i)) {
			preference--;
			break;
		}
	}

	// 检查弃牌区，如果有纹章牌，则偏好值加 1
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].armory_ != CARD_ARMORY_NO_ARMORY) {
			preference++;
			break;
		}
	}

	return preference;
}
