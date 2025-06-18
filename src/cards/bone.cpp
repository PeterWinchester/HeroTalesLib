/* bone.cp
   Created - 2025/5/13
*/

#include "cards/bone.h"

bool Bone(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;
	// 检查弃牌区的紫牌
	int num_purple_cards = 0;     // 弃牌区紫牌数量
	std::vector<int> purple_cards; // 弃牌区紫牌编号
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].color_ == CARD_COLOR_PURPLE) {
			num_purple_cards++;
			purple_cards.push_back(i);
		}
	}
		
	if (!num_purple_cards) { // 弃牌区没有紫牌
		if (arg_player == 1) {
			printf("弃牌区没有紫色卡牌，不能使用 ");
			DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
			printf("！\n");
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

	// 丢弃白骨
	AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
	arg_basic_func.pfn_gaming_interface_(arg_global_data);
	CheckNun(arg_player, arg_global_data);

	// 检查魔王
	CheckTyrant(arg_player, arg_basic_func, arg_global_data);
	if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

	// 选择弃牌区的一张紫牌
	int ch = rand() % num_purple_cards;
	if (arg_player == 1) {
		printf("请选择弃牌区的一张紫色卡牌放在场上：\n");
		for (int i = 0; i < num_purple_cards; i++) {
			printf("%d.", i + 1);
			DisplayCard(cards_abandoned[purple_cards[i]]);
		}
		printf("\n");
		ch = restricted_input_int(1, num_purple_cards) - 1;
	}
	Card c = cards_abandoned[purple_cards[ch]];

	// 将选中的牌放到场上
	c.status_ = CARD_STATUS_ON_FIELD;
	player[arg_player].cards_on_field_.push_back(c);
	player[arg_player].num_cards_on_field_++;
	cards_abandoned.erase(cards_abandoned.begin() + purple_cards[ch]);
	arg_global_data.num_cards_abandoned_--;

	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player != 1) {
		printf("玩家 %d 将弃牌区的一张 ", arg_player);
		DisplayCard(c);
		printf("放在了场上。\n");
		Pause();
	}
	return true;
}

int calc_using_pref_bone(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
	int preference = 0;

	// 检查弃牌区，如果有紫色的持续牌，则偏好值加 1
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].color_ == CARD_COLOR_PURPLE &&
			cards_abandoned[i].type_ == CARD_TYPE_CONSISTENT) {
			preference++;
			break;
		}
	}

	// 检查其他玩家的场，如果有火龙，则偏好值减 1
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (CheckDragon(i)) {
			preference--;
			break;
		}
	}

	return preference;
}
