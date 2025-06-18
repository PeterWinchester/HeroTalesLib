/* monk.cpp
   Created - 2025/2/9
*/

#include "cards/monk.h"

bool Monk(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	// 统计弃牌区的 Lv.1 以外的黄色卡牌
	int num_yellow_cards = 0;
	std::vector<int> yellow_cards; // 弃牌区 Lv.1 以外黄色卡牌编号
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].color_ == CARD_COLOR_YELLOW && cards_abandoned[i].level_ != 1) {
			num_yellow_cards++;
			yellow_cards.push_back(i);
		}
	}

	if (!num_yellow_cards) { // 弃牌区没有 Lv.1 以外的黄色卡牌
		if (arg_player == 1) {
			printf("弃牌区没有 Lv.1 以外的黄色手牌！\n");
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

	// 将僧侣丢弃
	AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	int card_chosen_num = yellow_cards[0];

	if (arg_player == 1) {
		// 选择一张 Lv.1 以外的黄色卡牌
		printf("请选择弃牌区的一张 Lv.1 以外的黄色卡牌：\n");
		for (int i = 0; i < num_yellow_cards; i++) {
			printf("%d.", i + 1);
			DisplayCard(cards_abandoned[yellow_cards[i]]);
		}
		printf("\n");

		int card_chosen_num = yellow_cards[restricted_input_int(1, num_yellow_cards) - 1];
		
		printf("你选中了 ");
		DisplayCard(cards_abandoned[card_chosen_num]);
		printf("。\n");
	} else card_chosen_num = yellow_cards[rand() % num_yellow_cards];

	int operation_chosen = 0;

	if (arg_player == 1) {
		// 不消耗行动点打出或加入手牌
		printf("请选择你要对其进行的操作：\n");
		printf("1.不消耗行动点打出 2.加入手牌\n");

		char ch = _getch();
		while (ch != '1' && ch != '2') ch = _getch();

		operation_chosen = ch - '1';
	} else operation_chosen = rand() % 2;

	if (operation_chosen) { // 加入手牌
	Monk_Add_to_Hand:
		// 加入手牌
		AddAbandonedCardToHand(arg_player, card_chosen_num, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player != 1) printf("玩家 %d 将其加入了手牌。\n", arg_player);

		AbandonBomb(arg_player, arg_global_data, arg_basic_func);
	} else {
		// 检查该卡牌是否为触发牌，触发牌不能打出
		if (cards_abandoned[card_chosen_num].type_ == CARD_TYPE_TRIGGER) {
			if (arg_player == 1) {
				printf("该卡牌为触发牌，不能主动打出。\n");
				Pause();
			}
			goto Monk_Add_to_Hand; // 转到加入手牌
		}

		/* 不消耗行动点打出的实现方式：
		   打出卡牌前先保存当前行动点数的副本，打出卡牌后无论行动点是否减少，都恢复到副本保存的行动点数
		*/
		int tmp = player[arg_player].num_action_points_;      // 保存当前行动点数副本
		arg_global_data.card_used_by_monk_ = card_chosen_num; // 保存僧侣打出的卡牌在弃牌区的编号
		bool res = cards_abandoned[card_chosen_num].pfn_function_(arg_player, card_chosen_num,
																  CARD_STATUS_IN_HAND,
																  CARD_MONK_MODE, arg_global_data,
																  arg_basic_func); // 打出卡牌
		player[arg_player].num_action_points_ = tmp;          // 从副本恢复行动点数

		if (!res) { // 不符合打出该卡牌的条件
			if (arg_player == 1) {
				printf("无法打出该卡牌，将其加入手牌。");
				Pause();
			}
			goto Monk_Add_to_Hand;
		}
	}
	return true;
}

int calc_using_pref_monk(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
	int preference = 0;

	// 检查弃牌区，如果有 Lv.1 以外的黄色卡牌，则偏好值加 1
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].level_ != 1 && cards_abandoned[i].color_ == CARD_COLOR_YELLOW) {
			preference++;
			break;
		}
	}

	return preference;
}
