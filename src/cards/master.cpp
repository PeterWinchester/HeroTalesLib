/* master.cpp
   Created - 2025/2/10
*/

#include "cards/master.h"

bool Master(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	// 统计有手牌的其他玩家数量
	int num_players_with_cards_in_hand = 0;      // 有手牌的其他玩家数量
	std::vector<int> players_with_cards_in_hand; // 有手牌的其他玩家编号
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[i].num_cards_in_hand_) {
			num_players_with_cards_in_hand++;
			players_with_cards_in_hand.push_back(i);
		}
	}

	if (!num_players_with_cards_in_hand) { // 如果没有查到有手牌的其他玩家
		if (arg_player == 1) {
			printf("其他玩家都没有手牌，不能使用 ");
		
			if (arg_mode == CARD_ORDINARY_MODE) DisplayCard(player[1].cards_in_hand_[arg_player]);
			else DisplayCard(cards_abandoned[arg_card]);
		
			printf("！\n");
			Pause();
		}
		return false;
	}

	arg_global_data.attacking_player_ = arg_player;
	player[arg_player].num_action_points_--;

	int target = players_with_cards_in_hand[rand() % num_players_with_cards_in_hand];

	if (arg_player == 1) {
		// 选择攻击对象
		printf("请指定你的攻击对象：\n");
		for (int i = 0; i < num_players_with_cards_in_hand; i++) {
			printf("%d.玩家%d ", i + 1, players_with_cards_in_hand[i]);
		}
		printf("\n");

		target = restricted_input_int(1, num_players_with_cards_in_hand) - 1;
		target = players_with_cards_in_hand[target];
	} else {
		printf("玩家 %d 打出了 ", arg_player);

		if (arg_mode == CARD_ORDINARY_MODE) DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		else DisplayCard(cards_abandoned[arg_card]);

		printf("，目标指向");

		if (target == 1) printf("你");
		else printf("玩家 %d ", target);

		printf("！\n");

		if (arg_mode == CARD_ORDINARY_MODE) {
			IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		} else IllustrateCard(cards_abandoned[arg_card]);
		
		Pause();
	}

	if (Defend(arg_player, target, arg_card, arg_mode, arg_global_data, arg_basic_func)) {
		return true; // 如被防守则返回
	}

	// 如果不是僧侣模式，则将法师丢弃
	if (arg_mode != CARD_MONK_MODE) {
		AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		CheckNun(arg_player, arg_global_data);
	}

	int lv_chosen = rand() % 4 + 1;

	if (arg_player) {
		// 选择要求放置的手牌 Lv
		printf("请输入你要求放置的手牌 Lv（1/2/3/4）：");
		lv_chosen = restricted_input_int(1, 4);
	} else {
		printf("玩家 %d 要求", arg_player);

		if (target == 1) printf("你");
		else printf("玩家 %d ", target);

		printf("放置一张 Lv.%d 的手牌在场上。\n", lv_chosen);
		Pause();
	}

	// 在目标玩家手中寻找指定 Lv 的卡牌
	int num_cards_available = 0;
	std::vector<int> cards_available;

	for (int i = 0; i < player[target].num_cards_in_hand_; i++) {
		if (player[target].cards_in_hand_[i].level_ == lv_chosen) {
			num_cards_available++;
			cards_available.push_back(i);
		}
	}

	if (num_cards_available) { // 有指定 Lv 的卡牌，放到场上
		int card_chosen = cards_available[rand() % num_cards_available];
		
		if (target == 1) {
			printf("请选择你的一张 Lv.%d 手牌放在场上：\n", lv_chosen);
			for (int i = 0; i < num_cards_available; i++) {
				printf("%d.", i + 1);
			    DisplayCard(player[1].cards_in_hand_[cards_available[i]]);
			}
			printf("\n");

			card_chosen = cards_available[restricted_input_int(1, num_cards_available) - 1];
		}

		PutOnField(target, card_chosen, CARD_ORDINARY_MODE, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) {
			printf("太遗憾了，玩家 %d 有 Lv.%d 的手牌！\n", target, lv_chosen);
			Pause();
		}
	} else { // 没有指定 Lv 的卡牌，加钱
		player[arg_player].num_coins_++;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (target == 1) printf("你");
		else printf("玩家 %d ", target);
		
		printf("没有 Lv.%d 的手牌，", lv_chosen);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d", arg_player);

		printf(" +1 金币！\n");
		Pause();

		// 判断是否获胜
		if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
			arg_global_data.win_player_ = 1;
			arg_global_data.game_status_ = 0;
			return true;
		}

		CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);
		
		CheckDancer(arg_player, arg_global_data, arg_basic_func);
		if (arg_global_data.game_status_ != 1) return true;
	}
	CheckMinister(target, arg_global_data, arg_basic_func);
	return true;
}

int calc_using_pref_master(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查其他玩家的手牌数，若有玩家的手牌数小于 4，偏好值加 1
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[arg_player].num_cards_in_hand_ < 4 && player[arg_player].num_cards_in_hand_ > 0) {
			preference++;
			break;
		}
	}

	return preference;
}
