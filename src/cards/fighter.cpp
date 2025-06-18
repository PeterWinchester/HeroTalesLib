/* fighter.cpp
   Created - 2025/2/9
*/

#include "cards/fighter.h"

bool Fighter(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	// 检查手牌数，若为僧侣模式，则手牌数不能小于 1；若不是僧侣模式，则手牌数不能小于 2
	if (player[arg_player].num_cards_in_hand_ < 2 - (arg_mode == CARD_MONK_MODE)) {
		if (arg_player == 1) {
			printf("你的手牌不足！\n");
			Pause();
		}
		return false;
	}

	player[arg_player].num_action_points_--;

	if (arg_player != 1) {
		printf("玩家 %d 打出了 ", arg_player);

		if (arg_mode == CARD_ORDINARY_MODE) DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		else DisplayCard(cards_abandoned[arg_card]);

		printf("。\n");

		if (arg_mode == CARD_ORDINARY_MODE) {
			IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		} else IllustrateCard(cards_abandoned[arg_card]);
		
		Pause();
	}

	// 如果不是僧侣模式，需丢弃手上的格斗家
	if (arg_mode == CARD_ORDINARY_MODE) {
		AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		CheckNun(arg_player, arg_global_data);
	}

	// 将全部手牌放到场上，并统计 Lv 总和（没有 Lv 的卡牌按 Lv.0 计算），检查纹章
	int sum_level = 0;
	bool found_armory = false;
	while (player[arg_player].num_cards_in_hand_) {
		if (player[arg_player].cards_in_hand_[0].level_ != CARD_NO_LEVEL) {
			sum_level += player[1].cards_in_hand_[0].level_;
		}
		if (player[arg_player].cards_in_hand_[0].armory_ != CARD_ARMORY_NO_ARMORY) {
			found_armory = true;
		}
		PutOnField(arg_player, 0, CARD_ORDINARY_MODE, arg_global_data);
	}

	// 结算
	if (sum_level % 2 == 0 && !found_armory) { // Lv 之和为偶数且不存在纹章，加钱
		// 加钱
		player[arg_player].num_coins_++;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);
		
		printf("放置在场上的手牌 Lv 之和为偶数且不存在纹章，+1 金币！\n");
		Pause();

		// 判断获胜
		if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
			arg_global_data.win_player_ = arg_player;
			arg_global_data.game_status_ = 0;
			return true;
		}

		CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);
		CheckDancer(arg_player, arg_global_data, arg_basic_func);
	}
	return true;
}

int calc_using_pref_fighter(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查手牌，如果所有手牌的 Lv 之和为偶数且不存在纹章，则偏好值加 2
	bool found_armory = false;
	int sum_level = 0;
	for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].armory_ != CARD_ARMORY_NO_ARMORY) {
			found_armory = true;
			break;
		}
		sum_level += player[arg_player].cards_in_hand_[i].level_;
	}
	if (!found_armory && sum_level % 2 == 0) preference += 2;
	
	return preference;
}
