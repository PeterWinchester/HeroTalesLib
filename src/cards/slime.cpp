/* slime.cpp
   Created - 2025/4/29
*/
#include "cards/slime.h"

bool Slime(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// 统计弃牌区的 Lv.1 和 Lv.2 牌
	int num_target_cards = 0;      // 弃牌区 Lv.1 和 Lv.2 卡牌数量
	std::vector<int> target_cards; // 弃牌区 Lv.1 和 Lv.2 卡牌编号
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].level_ == 1 || cards_abandoned[i].level_ == 2) {
			num_target_cards++;
			target_cards.push_back(i);
		}
	}

	// 检查弃牌区是否有相应卡牌
	if (!num_target_cards) {
		if (arg_player == 1) {
			printf("弃牌区没有 Lv.1 或 Lv.2 卡牌！\n");
		    Pause();
		}
		return false;
	}

	player[arg_player].num_action_points_--;

	// 丢弃史莱姆
	AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);
	
	if (arg_player != 1) {
		printf("玩家 %d 打出了 ", arg_player);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		printf("。\n");

		IllustrateCard(cards_abandoned.back());
		Pause();
	}

	CheckNun(arg_player, arg_global_data);

	// 检查魔王
	CheckTyrant(arg_player, arg_basic_func, arg_global_data);
	if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

	int ch = rand() % num_target_cards;
	Card c = cards_abandoned[target_cards[ch]];

	if (arg_player == 1) {
		// 选择一张 Lv.1 或 Lv.2 牌
		printf("请选择一张牌加入手中：\n");
		for (int i = 0; i < num_target_cards; i++) {
			printf("%d.", i + 1);
			DisplayCard(cards_abandoned[target_cards[i]]);
		}
		printf("\n");
		ch = restricted_input_int(1, num_target_cards) - 1;
	}

	// 将选中牌加入手牌
	AddAbandonedCardToHand(arg_player, target_cards[ch], arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player != 1) {
		printf("玩家 %d 将弃牌区的一张 ", arg_player);
		DisplayCard(c);
		printf("加入了手牌。\n");
		Pause();
	}
	return true;
}

int calc_using_pref_slime(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;
	
	// 检查魔王，如果有魔王，偏好值加 2
	if (CheckTyrant(arg_player, arg_basic_func, arg_global_data)) preference += 2;

	return preference;
}
