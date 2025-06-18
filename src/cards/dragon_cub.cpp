/* dragon_cub.cpp
   Created - 2025/4/9
*/

#include "cards/dragon_cub.h"

bool DragonCub(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// num_targets 为场上有牌的玩家数，num_defenders 为手上有防牌的玩家数
	int num_targets = 0, num_defenders = 0;
	// targets 为场上有牌的玩家编号，defenders 为手上有防牌的玩家编号
	std::vector<int> targets, defenders;

	// 统计场上有牌的玩家
	for (int i = 2; i <= arg_global_data.num_players_; i++) {
		if (player[i].num_cards_on_field_) {
			num_targets++;
			targets.push_back(i);
		}
	}

	// 检查是否有其他玩家场上有牌
	if (!num_targets) {
		if (arg_player == 1) {
			printf("其他玩家场上都没有牌，不能使用 ");
			if (arg_mode == CARD_ORDINARY_MODE) {
				DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
			} else if (arg_mode == CARD_DRAGON_MODE) DisplayCard(cards_abandoned[arg_card]);
			printf("！\n");
			Pause();
		}
		return false;
	}

	player[arg_player].num_action_points_--;
	arg_global_data.attacking_player_ = arg_player;

	if (arg_player != 1) {
		printf("玩家 %d 打出了 ", arg_player);

		if (arg_mode == CARD_DRAGON_MODE) DisplayCard(cards_abandoned[arg_card]);
		else DisplayCard(player[arg_player].cards_in_hand_[arg_card]);

		printf("。\n");

		if (arg_mode == CARD_DRAGON_MODE) IllustrateCard(cards_abandoned[arg_card]);
		else IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);

		Pause();
	}

	// 统计手上有防牌的玩家
	for (int i = 0; i < num_targets; i++) {
		if (CheckGuard(targets[i]) || CheckHolyKnight(targets[i])) {
			num_defenders++;
			defenders.push_back(targets[i]);
		}
	}
		
	if (num_defenders == 1) { // 只有一个目标玩家有防牌
		if (Defend(arg_player, defenders[0], arg_card, arg_status, arg_global_data,
				   arg_basic_func)) return true;
	} else if (num_defenders > 1) { // 有多个目标玩家有防牌
		printf("共 %d 名目标玩家有防牌，现随机触发。\n", num_defenders);
		Pause();
		if (Defend(arg_player, defenders[rand() % num_defenders], arg_card, arg_status,
				   arg_global_data, arg_basic_func)) return true;
	}

	// 如果不是火龙模式，则将龙幼崽丢弃
	if (arg_mode != CARD_DRAGON_MODE) {
		AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		CheckNun(arg_player, arg_global_data);
	}

	bool res = true; // 是否可以加钱

	// 选择每个目标玩家场上的一张牌回手
	for (int i = 0; i < num_targets; i++) {
		if (arg_player == 1) {
			// 选择场上一张牌
			printf("请选择玩家 %d 场上的一张牌回到手牌：\n", targets[i]);
			for (int j = 0; j < player[targets[i]].num_cards_on_field_; j++) {
				printf("%d.", j + 1);
				DisplayCard(player[targets[i]].cards_on_field_[j]);
			}
			printf("\n");
			int ch = restricted_input_int(1, player[targets[i]].num_cards_on_field_) - 1;
			ReturnCardOnField(targets[i], ch); // 回手
			
			// 回手的牌没有 Lv 则不能加钱
			if (player[targets[i]].cards_in_hand_.back().level_ == CARD_NO_LEVEL) res = false;
			
			arg_basic_func.pfn_gaming_interface_(arg_global_data);
		} else {
			bool find = false; // 该目标玩家场上是否有带有 Lv 的卡牌
			for (int j = 0; j < player[targets[i]].num_cards_on_field_; j++) {
				if (player[targets[i]].cards_on_field_[j].level_ != CARD_NO_LEVEL) {
					ReturnCardOnField(targets[i], j);
					find = true;
					break;
				}
			}
			if (!find) {
				ReturnCardOnField(targets[i], rand() % player[targets[i]].num_cards_on_field_);
				res = false;
			}

			arg_basic_func.pfn_gaming_interface_(arg_global_data);
			printf("玩家 %d 将玩家 %d 场上的一张 ", arg_player, targets[i]);
			DisplayCard(player[targets[i]].cards_in_hand_.back());
			printf("收回了手上。\n");
			Pause();
		}
		CheckMinister(targets[i], arg_global_data, arg_basic_func);
	}

	// 结算
	if (res) {
		// 加钱
		player[arg_player].num_coins_++;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		printf("攻击成功，");

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
			
		CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func); // 检查宝箱怪

		// 检查舞娘
		CheckDancer(arg_player, arg_global_data, arg_basic_func);
		if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
	}
	return true;
}

int calc_using_pref_dragon_cub(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查其他玩家的场，如果所有场上有牌的玩家的场上都有带 Lv 的牌，则偏好值加 2
	bool exist_card_on_field = false;
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[i].num_cards_on_field_) {
			exist_card_on_field = true;
			break;
		}
	}
	if (exist_card_on_field) {
		bool all_level_on_field = true;
		for (int i = 1; i <= arg_global_data.num_players_; i++) {
			if (i == arg_player) continue;
			if (player[i].num_cards_on_field_) {
				bool found_level = false;
				for (int j = 0; j < player[i].num_cards_on_field_; j++) {
					if (player[i].cards_on_field_[j].level_ != CARD_NO_LEVEL) {
						found_level = true;
						break;
					}
				}
				if (!found_level) {
					all_level_on_field = false;
					break;
				}
			}
		}
		if (all_level_on_field) preference += 2;
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
