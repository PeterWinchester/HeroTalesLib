/* black_knight.cpp
   Created - 2025/4/3
*/

#include "cards/black_knight.h"

bool BlackKnight(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	arg_global_data.attacking_player_ = arg_player;

	int target = 0;
	if (arg_player == 1) {
		target = restricted_input_int(2, arg_global_data.num_players_);

		// 检查目标玩家手牌数
		if (!player[target].num_cards_in_hand_) {
			printf("该玩家没有手牌！\n");
			Pause();
			return false; // 没有手牌则直接返回
		}
	} else {
		int num_players_with_cards_in_hand = 0;
		std::vector<int> players_with_cards_in_hand;

		for (int i = 1; i <= arg_global_data.num_players_; i++) {
			if (i == arg_player) continue;
			if (player[i].num_cards_in_hand_) {
				num_players_with_cards_in_hand++;
				players_with_cards_in_hand.push_back(i);
			}
		}
		if (!num_players_with_cards_in_hand) return false;

		target = players_with_cards_in_hand[rand() % num_players_with_cards_in_hand];

		printf("玩家 %d 打出了 ", arg_player);
		DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		printf("，目标指定为玩家 %d ！\n", target);

		IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		Pause();
	}

	player[arg_player].num_action_points_--;

	if (Defend(arg_player, target, arg_card, arg_status, arg_global_data, arg_basic_func)) {
		return true;
	}

	AbandonCard(arg_player, arg_card, arg_mode, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);
	CheckNun(arg_player, arg_global_data);

	int x = rand() % player[target].num_cards_in_hand_;
	Card c = player[target].cards_in_hand_[x];
	PutOnField(target, x, CARD_ORDINARY_MODE, arg_global_data);

	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player == 1) printf("你");
	else printf("玩家 %d ", arg_player);

	printf("将");

	if (target == 1) printf("你");
	else printf("玩家 %d ", target);

	printf("手中的一张 ");
	DisplayCard(player[target].cards_on_field_.back());
	printf("放在了场上。\n");
	Pause();

	if (c.level_ != CARD_NO_LEVEL) {
		player[arg_player].num_coins_++;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		printf("攻击成功，");

		if (arg_player == 1) printf("你");
		else printf("玩家 %d", arg_player);

		printf(" +1 金币！\n");
		Pause();

		if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
			arg_global_data.win_player_ = arg_player;
			arg_global_data.game_status_ = GAME_STATUS_OVER;
			return true;
		}

		CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);

		CheckDancer(arg_player, arg_global_data, arg_basic_func);
		if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
	} else if (c.armory_ != CARD_ARMORY_NO_ARMORY) {
		// 检查弃牌区是否有魔剑
		int blade_abandoned = -1; // 弃牌区中魔剑的编号
		for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
			if (cards_abandoned[i].name_ == "魔剑") {
				blade_abandoned = i;
				break;
			}
		}

		if (arg_player == 1) {
			if (blade_abandoned != -1) { // 弃牌区有魔剑
				// 选择从弃牌区或牌库拿取魔剑
				printf("牌库和弃牌区都有 ");
				DisplayCard(card[55]);
				printf("，你想从哪里拿取？\n");
				printf("1.牌库 2.弃牌区\n");
				int ch = restricted_input_int(1, 2);
				
				if (ch == 1) { // 从牌库拿取魔剑
					card[55].status_ = CARD_STATUS_IN_HAND;
					player[1].cards_in_hand_.push_back(card[55]);
					player[1].num_cards_in_hand_++;
					card[55].status_ = CARD_STATUS_IN_LIBRARY;
				} else AddAbandonedCardToHand(1, blade_abandoned, arg_global_data); // 从弃牌区拿取魔剑
			} else { // 弃牌区没有魔剑，从牌库拿取
				player[1].cards_in_hand_.push_back(card[55]);
				player[1].num_cards_in_hand_++;
			}
			
			arg_basic_func.pfn_gaming_interface_(arg_global_data);
			printf("你将 ");
			DisplayCard(card[55]);
			printf("加入了手牌。\n");
			Pause();
			
			AbandonBomb(arg_player, arg_global_data, arg_basic_func);
		} else {
			if (blade_abandoned != -1) {
				AddAbandonedCardToHand(arg_player, blade_abandoned, arg_global_data);
				
				printf("玩家 %d 将弃牌区的一张 ", arg_player);
				DisplayCard(card[55]);
				printf("加入了手牌。\n");
			} else {
				card[55].status_ = CARD_STATUS_IN_HAND;
				player[arg_player].cards_in_hand_.push_back(card[55]);
				player[arg_player].num_cards_in_hand_++;
				card[55].status_ = CARD_STATUS_IN_LIBRARY;
				
				printf("玩家 %d 将牌库的一张 ", arg_player);
				DisplayCard(card[55]);
				printf("加入了手牌。\n");
			}
			Pause();

			AbandonBomb(arg_player, arg_global_data, arg_basic_func);
		}
	}
	return true;
}

int calc_using_pref_black_knight(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查其他玩家的手牌，若其他玩家有手牌，则偏好值加 2
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[arg_player].num_cards_in_hand_) {
			preference += 2;
			break;
		}
	}

	return preference;
}
