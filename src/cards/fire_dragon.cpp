/* fire_dragon.cpp
   Created - 2025/2/7
*/

#include "cards/fire_dragon.h"

bool FireDragon(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status == CARD_STATUS_IN_HAND) { // 在手上，则打出
		player[arg_player].num_action_points_--;

		PutOnField(arg_player, arg_card, arg_mode, arg_global_data); // 将火龙放到场上

		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);

		printf("将 ");
		DisplayCard(player[arg_player].cards_on_field_.back());
		printf("放在了场上。\n");
		
		if (arg_player != 1) IllustrateCard(player[arg_player].cards_on_field_.back());
		
		Pause();
		return true;
	} else if (arg_status == CARD_STATUS_ON_FIELD) { // 在场上，则横置
		// 统计弃牌区的[火]并生成列表
		int num_fire_abandoned = 0;     // 弃牌区[火]的数量
		std::vector<int> fire_abandoned; // 弃牌区[火]的编号
		for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
			if (cards_abandoned[i].fire_property_ == CARD_PROPERTY_FIRE) {
				num_fire_abandoned++;
				fire_abandoned.push_back(i);
			}
		}

		// 检查弃牌区[火]的数量
		if (!num_fire_abandoned) { // 弃牌区没有[火]
			if (arg_player == 1) {
				printf("弃牌区没有[火]！\n");
				Pause();
			}
			return false;
		}

		int card_chosen = 0;
		char opt_chosen = '1';

		if (arg_player == 1) {
			// 选择弃牌区的一张[火]
			printf("请选择弃牌区的一张[火]：\n");
			for (int i = 0; i < num_fire_abandoned; i++) {
				printf("%d.", i + 1);
				DisplayCard(cards_abandoned[fire_abandoned[i]]);
			}
			printf("\n");
			card_chosen = fire_abandoned[restricted_input_int(1, num_fire_abandoned) - 1];

			// 选择不消耗行动点打出或加入手牌
			printf("请选择你要对其进行的操作：\n");
			printf("1.不消耗行动点打出 2.加入手牌\n");
			opt_chosen = _getch();
			while (opt_chosen != '1' && opt_chosen != '2') opt_chosen = _getch();
		} else {
			card_chosen = fire_abandoned[rand() % num_fire_abandoned]; // 随机选择一张[火]
			opt_chosen = '1' + rand() % 2; // 随机选择加入手牌或不消耗行动点打出

			printf("玩家 %d 横置了 ", arg_player);
			DisplayCard(player[arg_player].cards_on_field_[arg_card]);
			printf("，并选择了弃牌区的一张 ");
			DisplayCard(cards_abandoned[card_chosen]);
			printf("。\n");

			IllustrateCard(player[arg_player].cards_on_field_[arg_card]);
			Pause();
		}

		if (opt_chosen == '1') { // 不消耗行动点打出
			// 检查该卡牌是否为触发牌，触发牌不能打出
			if (cards_abandoned[card_chosen].type_ == CARD_TYPE_TRIGGER) {
				if (arg_player == 1) {
					printf("该卡牌为触发牌，不能主动打出。\n");
					Pause();
				}
				goto Dragon_Add_to_Hand; // 转到加入手牌
			}

			/* 不消耗行动点打出的实现方式：
			   打出卡牌前先保存当前行动点数的副本，打出卡牌后无论行动点是否减少，都恢复到副本保存的行动点数
			*/
			int tmp = player[arg_player].num_action_points_;    // 保存当前行动点数副本
			arg_global_data.card_used_by_dragon_ = card_chosen; // 保存僧侣打出的卡牌在弃牌区的编号
			bool res = cards_abandoned[card_chosen].pfn_function_(arg_player, card_chosen,
																  CARD_STATUS_IN_HAND,
																  CARD_DRAGON_MODE, arg_global_data,
																  arg_basic_func); // 打出卡牌
			player[arg_player].num_action_points_ = tmp;        // 从副本恢复行动点数

			if (!res) { // 不符合打出该卡牌的条件
				if (arg_player == 1) {
					printf("无法打出该卡牌，将其加入手牌。");
					Pause();
				}
				goto Dragon_Add_to_Hand;
			}
		} else { // 加入手牌
		Dragon_Add_to_Hand:
			AddAbandonedCardToHand(arg_player, card_chosen, arg_global_data);
			arg_basic_func.pfn_gaming_interface_(arg_global_data);

			if (arg_player != 1) printf("玩家 %d 将其加入了手牌。\n", arg_player);

			AbandonBomb(arg_player, arg_global_data, arg_basic_func);
		}
		return true;
	}
	return false;
}

int calc_using_pref_fire_dragon(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查弃牌区，若有[火]，则偏好值加 1
	bool found_fire_abandoned = false;
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].fire_property_ == CARD_PROPERTY_FIRE) {
			found_fire_abandoned = true;
			break;
		}
	}

	// 若弃牌区有[火]，则检查其他玩家的场牌，若其他玩家场上有带 Lv 的牌，则偏好值再加 1
	if (found_fire_abandoned) {
		preference++;
		for (int i = 1; i <= arg_global_data.num_players_; i++) {
			if (i == arg_player) continue;
			bool found_level = false;
			for (int j = 0; j < player[i].num_cards_on_field_; j++) {
				if (player[i].cards_on_field_[j].level_ != CARD_NO_LEVEL) {
					preference++;
					found_level = true;
					break;
				}
			}
			if (found_level) break;
		}
	}

	return preference;
}

bool CheckDragon(int arg_player) {
    for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
        if (player[arg_player].cards_on_field_[i].name_ == "火龙") return true;
    }
    return false;
}
