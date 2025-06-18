/* bat.cpp
   Created - 2025/5/13
*/

#include "cards/bat.h"

bool Bat(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// 统计可以作为目标的玩家数，只要手上或场上有牌都可以作为目标
	int num_targets = 0;
	std::vector<int> targets;
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_status) continue;
		if (!player[i].num_cards_in_hand_ && !player[i].num_cards_on_field_) continue;
		targets.push_back(i);
		num_targets++;
	}
		
	if (!num_targets) { // 没有符合要求的玩家
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
		printf("。\n");

		IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		Pause();
	}

	// 检查魔王
	CheckTyrant(arg_player, arg_basic_func, arg_global_data);
	if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

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

	// 丢弃蝙蝠
	AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player == 1) {
		// 检查目标玩家是否有手牌
		if (player[targets[ch]].num_cards_in_hand_) { // 有手牌则展示出来
			printf("这些是玩家 %d 的手牌：\n", targets[ch]);
			for (int i = 0; i < player[targets[ch]].num_cards_in_hand_; i++) {
				DisplayCard(player[targets[ch]].cards_in_hand_[i]);
			}
			printf("\n");
			Pause();
		}
	}

	// 将目标玩家场上的牌全部回手
	while (player[targets[ch]].num_cards_on_field_) ReturnCardOnField(targets[ch], 0);

	arg_basic_func.pfn_gaming_interface_(arg_global_data); // 场上没牌了，不必检查大臣
	return true;
}

int calc_using_pref_bat(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
	int preference = 0;

	// 检查魔王，如果有魔王，偏好值加 2
	if (CheckTyrant(arg_player, arg_basic_func, arg_global_data)) preference += 2;

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
