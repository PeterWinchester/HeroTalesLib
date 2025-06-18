/* businessman.cpp
   Created - 2025/2/10
*/

#include "cards/businessman.h"

bool Businessman(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	// 先检查场上是否有牌
	if (!player[arg_player].num_cards_on_field_) {
		if (arg_player == 1) {
			printf("你场上没牌，不能使用 ");
			DisplayCard(player[arg_player].cards_in_hand_[arg_player]);
			printf("。\n");
			Pause();
		}
		return false;
	}

	// 统计有钱的其他玩家
	int num_players_with_coin = 0;      // 有钱的其他玩家数量
	std::vector<int> players_with_coin; // 有钱的其他玩家编号
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[i].num_coins_) {
			num_players_with_coin++;
			players_with_coin.push_back(i);
		}
	}

	if (!num_players_with_coin) {
		if (arg_player == 1) {
			printf("其他玩家没有金币，不能使用 ");
			DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
			printf("。\n");
			Pause();
		}
		return false;
	}

	arg_global_data.attacking_player_ = arg_player;
	player[arg_player].num_action_points_--;

	int target = players_with_coin[rand() % num_players_with_coin];

	if (arg_player == 1) {
		// 选择攻击对象
		printf("请选择你的攻击对象：");
		for (int i = 0; i < num_players_with_coin; i++) {
			printf("%d.玩家%d ", i + 1, players_with_coin[i]);
		}
		printf("\n");

		target = players_with_coin[restricted_input_int(1, num_players_with_coin) - 1];
	} else {
		printf("玩家 %d 打出了 ", arg_player);
		DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		printf("，目标指向");

		if (target == 1) printf("你");
		else printf("玩家 %d ", target);

		printf("！\n");
		IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		Pause();
	}

	if (Defend(arg_player, target, arg_card, arg_mode, arg_global_data, arg_basic_func)) {
		return true; // 如果防守成功则返回
	}

	int card_to_give = rand() % player[arg_player].num_cards_on_field_;

	if (arg_player == 1) {
		// 选择场上的一张牌
		printf("请选择你场上的一张牌交付给玩家 %d ：\n", target);
		for (int i = 0; i < player[1].num_cards_on_field_; i++) {
			printf("%d.", i + 1);
			DisplayCard(player[1].cards_on_field_[i]);
		}
		printf("\n");
		
		card_to_give = restricted_input_int(1, player[1].num_cards_on_field_) - 1;
	}

	if (arg_player != 1) {
		printf("玩家 %d 将其场上的一张 ", arg_player);
		DisplayCard(player[arg_player].cards_on_field_[card_to_give]);
		printf("交付到 ");

		if (target == 1) printf("你");
		else printf("玩家 %d ", target);

		printf("手中，");

		if (target == 1) printf("你");
		else printf("玩家 %d ", target);

		printf("向玩家 %d 支付 1 金币！\n", arg_player);
		Pause();
	}

	// 将选中的卡牌交付到目标玩家手中
	player[arg_player].cards_on_field_[card_to_give].status_ = CARD_STATUS_IN_HAND;
	player[target].cards_in_hand_.push_back(player[arg_player].cards_on_field_[card_to_give]);
	player[target].num_cards_in_hand_++;
	player[arg_player].cards_on_field_.erase(player[arg_player].cards_on_field_.begin()
											 + card_to_give);
	player[arg_player].num_cards_on_field_--;

	// 目标玩家交钱
	player[target].num_coins_--;
	player[arg_player].num_coins_++;

	AbandonCard(arg_player, arg_card, arg_status, arg_global_data); // 将商人丢弃

	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player == 1) {
		printf("你从玩家 %d 处获得 1 金币！\n", target);
		Pause();
	}

	// 判断是否获胜
	if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
		arg_global_data.win_player_ = arg_player;
		arg_global_data.game_status_ = 0;
		return true;
	}

	CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func); // 检查宝箱怪

	// 检查舞娘
	CheckDancer(arg_player, arg_global_data, arg_basic_func);
	if (arg_global_data.game_status_ != 1) return true;
			
	CheckMinister(target, arg_global_data, arg_basic_func);  // 检查大臣
	return true;
}

int calc_using_pref_businessman(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查场和其他玩家的金币数，若满足条件则偏好值加 2
	if (player[arg_player].num_cards_on_field_) {
		for (int i = 1; i <= arg_global_data.num_players_; i++) {
			if (i == arg_player) continue;
			if (player[i].num_coins_) {
				preference += 2;
				break;
			}
		}
	}

	return preference;
}
