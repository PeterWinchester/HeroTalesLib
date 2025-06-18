/* witch.cpp
   Created - 2025/5/14
*/

#include "cards/witch.h"

bool Witch(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// 统计有牌的其他玩家
	int num_targets = 0;     // 有牌的其他玩家数
	std::vector<int> targets; // 有牌的其他玩家编号
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[i].num_cards_in_hand_ || player[i].num_cards_on_field_) {
			num_targets++;
			targets.push_back(i);
		}
	}
		
	if (!num_targets) { // 其他玩家都没牌
		if (arg_player == 1) {
			printf("其他玩家都没有牌，不能使用 ");
			DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
			printf("！\n");
			Pause();
		}
		return false;
	}
		
	player[arg_player].num_action_points_--;
	arg_global_data.attacking_player_ = arg_player;

	if (arg_player != 1) {
		printf("玩家 %d 打出了 ", arg_player);
		DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		printf("！\n");

		IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		Pause();
	}

	// 检查魔王
	CheckTyrant(arg_player, arg_basic_func, arg_global_data);
	if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

	// 选择目标
	int ch = rand() % num_targets;
	if (arg_player == 1) {
		printf("请选择你的攻击对象：\n");
		for (int i = 0; i < num_targets; i++) {
			printf("%d.玩家%d ", i + 1, targets[i]);
		}
		printf("\n");
		ch = restricted_input_int(1, num_targets) - 1;
	} else {
		printf("玩家 %d 将攻击目标指定为玩家 %d 。\n", arg_player, targets[ch]);
		Pause();
	}

	if (Defend(arg_player, targets[ch], arg_card, arg_mode, arg_global_data, arg_basic_func)) {
		return true;
	}

	// 丢弃女巫
	AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);
	CheckNun(arg_player, arg_global_data);

	// 选择要宣言的卡牌
	Card c = card[rand() % (kNumYellowCards + kNumPurpleCards) + 1];
	if (arg_player == 1) {
		printf("请选择你要宣言的卡牌：\n");
		printf("1.黄牌 2.紫牌\n");
		char ch1 = _getch();
		while (ch1 != '1' && ch1 != '2') ch1 = _getch();
		
		printf("请选择你要宣言的卡牌：\n");
		int num = 0;
		std::vector<int> ic;
		if (ch1 == '1') {
			for (int i = 1; i <= kNumYellowCards; i++) {
				if (!CompareCards(card[i], card[i - 1])) {
					printf("%d.", ++num);
					DisplayCard(card[i]);
					ic.push_back(i);
				}
			}
			printf("\n");
		} else {
			for (int i = kNumYellowCards + 1; i <= kNumYellowCards + kNumPurpleCards; i++) {
				if (!CompareCards(card[i], card[i - 1])) {
					printf("%d.", ++num);
					DisplayCard(card[i]);
					ic.push_back(i);
				}
			}
			printf("\n");
		}
		int ch2 = restricted_input_int(1, num) - 1;
		c = card[ic[ch2]];
	} else {
		printf("玩家 %d 向玩家 %d 宣言了一张 ", arg_player, targets[ch]);
		DisplayCard(c);
		printf("。\n");
		Pause();
	}

	// 检查目标玩家的手上和场上是否有指定卡牌
	bool has_in_hand = false, has_on_field = false;
	for (int i = 0; i < player[targets[ch]].num_cards_in_hand_; i++) {
		if (CompareCards(player[targets[ch]].cards_in_hand_[i], c)) {
			has_in_hand = true;
			break;
		}
	}
	for (int i = 0; i < player[targets[ch]].num_cards_on_field_; i++) {
		if (CompareCards(player[targets[ch]].cards_on_field_[i], c)) {
			has_on_field = true;
			break;
		}
	}

	int ch1 = -1;
	if (has_in_hand && has_on_field) { // 手上和场上都有
		ch1 = rand() % 2;
		if (targets[ch] == 1) {
			printf("你手上和场上都有玩家 %d 宣言的卡牌，请选择要交付手上的还是场上的：\n", arg_player);
			printf("1.手上 2.场上\n");
			char ch2 = _getch();
			while (ch2 != '1' && ch2 != '2') ch2 = _getch();
			ch1 = ch2 - '1';
		}
	} else if (has_in_hand) ch1 = 0; // 只有手上有
	else if (has_on_field) ch1 = 1; // 只有场上有
	else { // 手上和场上都没有
		printf("攻击失败，玩家 %d 没有该牌！\n", targets[ch]);
		Pause();
	}
	if (ch1 == 0) { // 目标玩家将手上的指定卡牌交给攻击者
		for (int i = 0; i < player[targets[ch]].num_cards_in_hand_; i++) {
			if (CompareCards(player[targets[ch]].cards_in_hand_[i], c)) {
				player[arg_player].cards_in_hand_.push_back(player[targets[ch]].cards_in_hand_[i]);
				player[arg_player].num_cards_in_hand_++;
				player[targets[ch]].cards_in_hand_.erase(
					player[targets[ch]].cards_in_hand_.begin() + i
				);
				player[targets[ch]].num_cards_in_hand_--;

				arg_basic_func.pfn_gaming_interface_(arg_global_data);
				printf("玩家 %d 将手上的一张 ", targets[ch]);
				DisplayCard(c);
				printf("交付到了");
				if (arg_player == 1) printf("你");
				else printf("玩家 %d ", arg_player);
				printf("的手上。\n");
				Pause();

				AbandonBomb(arg_player, arg_global_data, arg_basic_func);
				CheckMinister(targets[ch], arg_global_data, arg_basic_func);
				break;
			}
		}
	} else if (ch1 == 1) { // 目标玩家将场上的指定卡牌交给攻击者
		for (int i = 0; i < player[targets[ch]].num_cards_on_field_; i++) {
			if (CompareCards(player[targets[ch]].cards_on_field_[i], c)) {
				player[arg_player].cards_in_hand_.push_back(player[targets[ch]].cards_on_field_[i]);
				player[arg_player].num_cards_in_hand_++;
				player[targets[ch]].cards_on_field_.erase(
					player[targets[ch]].cards_on_field_.begin() + i
				);
				player[targets[ch]].num_cards_on_field_--;

				arg_basic_func.pfn_gaming_interface_(arg_global_data);
				printf("玩家 %d 将场上的一张 ", targets[ch]);
				DisplayCard(c);
				printf("交付到了");
				if (arg_player == 1) printf("你");
				else printf("玩家 %d ", arg_player);
				printf("的手上。\n");
				Pause();

				AbandonBomb(arg_player, arg_global_data, arg_basic_func);
				CheckMinister(targets[ch], arg_global_data, arg_basic_func);
				break;
			}
		}
	} else { // 目标玩家没有指定卡牌
		printf("攻击失败，玩家 %d 没有该牌！\n", targets[ch]);
		Pause();
	}
	return true;
}

int calc_using_pref_witch(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

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
