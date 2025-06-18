/* demon.cpp
   Created - 2025/4/7
*/

#include "cards/demon.h"

bool Demon(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status == CARD_STATUS_IN_HAND) { // 状态在手上，则为打出
		player[arg_player].num_action_points_--;

		// 将妖精放到场上
		PutOnField(arg_player, arg_card, arg_mode, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);
		
		printf("将 ");
		DisplayCard(player[arg_player].cards_on_field_.back());
		printf("放在了场上。\n");

		if (arg_player != 1) IllustrateCard(player[arg_player].cards_on_field_.back());
		
		Pause();
		return true;
	} else if (arg_status == CARD_STATUS_ON_FIELD) { // 状态在场上，则为横置
		// 检查场上卡牌数量
		if (player[arg_player].num_cards_on_field_ > 1) { // 场上有其他牌
			// 生成场上其他牌的列表
			int num_cards_to_return = player[arg_player].num_cards_on_field_ - 1;
			std::vector<int> cards_to_return; // 场上其他牌的编号
			for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
				if (i == arg_card) continue;
				cards_to_return.push_back(i);
			}

			int ch = 0;
			
			if (arg_player != 1) {
				printf("玩家 %d 横置了场上的 ", arg_player);
				DisplayCard(player[arg_player].cards_on_field_[arg_card]);
				printf("。\n");

				IllustrateCard(player[arg_player].cards_on_field_[arg_card]);
				Pause();

				ch = rand() % num_cards_to_return; // 随机选择场上一张牌加入手牌
			} else {
				// 选择一张牌加入手牌
				printf("请选择你场上的一张牌加入手牌：\n");
				for (int i = 0; i < num_cards_to_return; i++) {
					printf("%d.", i + 1);
					DisplayCard(player[arg_player].cards_on_field_[cards_to_return[i]]);
				}
				printf("\n");
				ch = restricted_input_int(1, num_cards_to_return) - 1;
			}

			// 将选中的牌加入手牌
			ReturnCardOnField(arg_player, cards_to_return[ch]);
			arg_basic_func.pfn_gaming_interface_(arg_global_data);

			if (arg_player != 1) {
				printf("玩家 %d 将其场上的一张 ", arg_player);
				DisplayCard(player[arg_player].cards_in_hand_.back());
				printf("加入了手牌。\n");
				Pause();
			}
			return true;
		} else { // 场上没有其他牌
			if (arg_player == 1) {
				printf("你场上没有其它牌！\n");
				Pause();
			}
			return false;
		}
	}
	return false;
}

int calc_using_pref_demon(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查炸弹怪，若场上有炸弹怪，则偏好值加 1
	if (CheckBomb(arg_player)) preference++;

	return preference;
}
