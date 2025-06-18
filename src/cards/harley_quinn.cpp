/* harley_quinn.cpp
   Created - 2025/5/13
*/

#include "cards/harley_quinn.h"

bool HarleyQuinn(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// 统计有手牌的其他玩家
	int num_targets = 0;     // 有手牌的其他玩家数量
	std::vector<int> targets; // 有手牌的其他玩家编号
	for (int i = 2; i <= arg_global_data.num_players_; i++) {
		if (player[i].num_cards_in_hand_) {
			num_targets++;
			targets.push_back(i);
		}
	}
		
	if (!num_targets) { // 其他玩家没有手牌
		if (arg_player == 1) {
			printf("其他玩家都没有手牌，不能使用 ");
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
	if (arg_global_data.game_status_ != 1) return true;

	// 选择攻击对象
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

	if (Defend(arg_player, targets[ch], arg_card, arg_status, arg_global_data, arg_basic_func))
		return true;

	// 丢弃小丑女
	AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);
	CheckNun(arg_player, arg_global_data);

	Card c = card[rand() % (kNumYellowCards + kNumPurpleCards) + 1];

	if (arg_player == 1) {
		// 选择要宣言的卡牌
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

	// 检查目标玩家的手牌，如果有指定卡牌，则丢弃
	for (int i = 0; i < player[targets[ch]].num_cards_in_hand_; i++) {
		if (CompareCards(c, player[targets[ch]].cards_in_hand_[i])) {
			// 丢弃指定卡牌
			AbandonCard(targets[ch], i, CARD_STATUS_IN_HAND, arg_global_data);
			arg_basic_func.pfn_gaming_interface_(arg_global_data);
			printf("玩家 %d 丢弃了一张 ", targets[ch]);
			DisplayCard(c);
			printf("。\n");
			Pause();
			CheckNun(targets[ch], arg_global_data);

			// 结算
			if (c.level_ != CARD_NO_LEVEL) { // 带有 Lv
				// 加钱
				player[arg_player].num_coins_++;
				arg_basic_func.pfn_gaming_interface_(arg_global_data);
				printf("被丢弃的卡牌带有 Lv，");

				if (arg_player == 1) printf("你");
				else printf("玩家 %d", arg_player);

				printf(" +1 金币！\n");
				Pause();

				// 判断是否获胜
				if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
					arg_global_data.win_player_ = arg_player;
					arg_global_data.game_status_ = GAME_STATUS_OVER;
					return true;
				}

				// 检查宝箱怪
				CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);

				// 检查舞娘
				CheckDancer(arg_player, arg_global_data, arg_basic_func);
				if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
			}
			CheckMinister(targets[ch], arg_global_data, arg_basic_func); // 检查大臣
			return true;
		}
	}
	printf("攻击失败，玩家 %d 手上没有该牌！\n", targets[ch]);
	Pause();
		
	CheckMinister(targets[ch], arg_global_data, arg_basic_func); // 检查大臣
	return true;
}

int calc_using_pref_harley_quinn(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;
	// 暂时没有记牌机制，所以没有策略
	return preference;	
}
