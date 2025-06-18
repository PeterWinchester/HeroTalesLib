/* dragon_flame.cpp
   Created - 2025/4/14
*/

#include "cards/dragon_flame.h"

/* [火]龙炎[攻击]
   丢弃一名对手场上的一张牌，若那张牌带有 Lv，你 +1 金币。
*/
bool DragonFlame(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// 统计场上有牌的其他玩家
	int num_targets = 0; // 场上有牌的其他玩家数
	std::vector<int> targets; // 场上有牌的其他玩家编号
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[i].num_cards_on_field_) {
			num_targets++;
			targets.push_back(i);
		}
	}
	if (!num_targets) {
		if (arg_player == 1) {
			printf("其他玩家场上都没有牌，不能使用 ");

			if (arg_mode == CARD_DRAGON_MODE) DisplayCard(cards_abandoned[arg_card]);
			else DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
			
			printf("！\n");
			Pause();
		}
		return false;
	}

	player[arg_player].num_action_points_--;
	arg_global_data.attacking_player_ = arg_player;

	// 选择攻击对象
	int target;
	if (arg_player == 1) {
		printf("请选择你的攻击对象：\n");
		for (int i = 0; i < num_targets; i++) {
			printf("%d.玩家%d ", i + 1, targets[i]);
		}
		printf("\n");
		target = targets[restricted_input_int(1, num_targets) - 1];
	} else target = targets[rand() % num_targets];

	if (arg_player != 1) {
		printf("玩家 %d 打出了 ", arg_player);

		if (arg_mode == CARD_DRAGON_MODE) DisplayCard(cards_abandoned[arg_card]);
		else DisplayCard(player[arg_player].cards_in_hand_[arg_card]);

		printf("，目标指定为玩家 %d ！\n", target);

		if (arg_mode == CARD_DRAGON_MODE) IllustrateCard(cards_abandoned[arg_card]);
		else IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);

		Pause();
	}

	if (Defend(arg_player, target, arg_card, arg_status, arg_global_data, arg_basic_func)) {
		return true;
	}

	// 如果龙炎不是火龙打出的，需丢弃
	if (arg_mode != CARD_DRAGON_MODE) {
		AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		CheckNun(arg_player, arg_global_data);
	}

	int ch = rand() % player[target].num_cards_on_field_;

	if (arg_player == 1) {
		// 在目标玩家场上选择要丢弃的牌
		printf("请选择你要丢弃的对手场上的牌：\n");
		for (int i = 0; i < player[target].num_cards_on_field_; i++) {
			printf("%d.", i + 1);
			DisplayCard(player[target].cards_on_field_[i]);
		}
		printf("\n");
		ch = restricted_input_int(1, player[target].num_cards_on_field_) - 1;
	}

	// 丢弃相应卡牌
	AbandonCard(target, ch, CARD_STATUS_ON_FIELD, arg_global_data);
	Card card_chosen = cards_abandoned.back();
	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player != 1) {
		printf("玩家 %d 丢弃了", arg_player);
		
		if (target == 1) printf("你");
		else printf("玩家 %d", target);

		printf(" 场上的一张 ");
		DisplayCard(card_chosen);
		printf("。\n");
		Pause();
	}

	CheckNun(target, arg_global_data);

	// 结算
	if (card_chosen.level_ != CARD_NO_LEVEL) { // 丢弃的卡牌带有 Lv
		// 加钱
		player[arg_player].num_coins_++;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);
		
		printf("丢弃的卡牌带有 Lv，+1 金币！\n");
		Pause();

		// 判断是否获胜
		if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
			arg_global_data.win_player_ = arg_player;
			arg_global_data.game_status_ = GAME_STATUS_OVER;
			return true;
		}
			
		CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func); // 检查宝箱怪

		// 检查舞娘
		CheckDancer(arg_player, arg_global_data, arg_basic_func);
		if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
	}
		
	CheckMinister(target, arg_global_data, arg_basic_func); // 检查大臣
	return true;
}

int calc_using_pref_dragon_flame(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查其他玩家的场，如果有玩家的场上有带 Lv 的牌，则偏好值加 2
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		bool found_level = false;
		for (int j = 0; j < player[i].num_cards_on_field_; j++) {
			if (player[i].cards_on_field_[j].level_ != CARD_NO_LEVEL) {
				preference += 2;
				found_level = true;
				break;
			}
		}
		if (found_level) break;
	}

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
