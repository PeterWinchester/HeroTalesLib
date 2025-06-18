/* nun.cpp
   Created - 2025/2/7
*/

#include "cards/nun.h"

bool CheckNun(int arg_player, HTBasicData& arg_global_data) {
    if (cards_abandoned.back().level_ == 1) return false;

	short num_players_with_nun = 0;
	std::vector<short> players_with_nun;

	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		for (int j = 0; j < player[i].num_cards_in_hand_; j++) {
			if (player[i].cards_in_hand_[j].name_ == "修女") {
				num_players_with_nun++;
				players_with_nun.push_back(i);
				break;
			}
		}
	}

	if (num_players_with_nun == 0) return false;
	if (num_players_with_nun == 1) { // 只有一个玩家有修女
		printf("玩家 %d 有修女，触发获得玩家 %d 弃置的 ", players_with_nun[0], arg_player);
		DisplayCard(cards_abandoned.back());
		printf(" 。\n");

		// 注意，此函数选择弃牌区最后一张牌加入手牌，所以在一有卡牌进入弃牌区时就要调用此函数
		player[players_with_nun[0]].cards_in_hand_.push_back(cards_abandoned.back());
		player[players_with_nun[0]].num_cards_in_hand_++;
		cards_abandoned.pop_back();
		arg_global_data.num_cards_abandoned_--;

		// 在刚刚进入弃牌区的卡牌加入手牌之后，再丢弃修女
		for (int i = 0; i < player[players_with_nun[0]].num_cards_in_hand_; i++) {
			if (player[players_with_nun[0]].cards_in_hand_[i].name_ == "修女") {
				AbandonCard(players_with_nun[0], i, CARD_STATUS_IN_HAND, arg_global_data);
				break;
			}
		}

        player[players_with_nun[0]].cards_in_hand_.back().status_ = CARD_STATUS_IN_HAND;
	} else if (num_players_with_nun > 1) { // 有多个玩家有修女
		printf("共 %d 名玩家手牌有修女，现随机触发。\n", num_players_with_nun);

		short x = rand() % num_players_with_nun;

		printf("玩家 %d 成功触发修女，获得玩家 %d 弃置的 ", players_with_nun[x], arg_player);
		DisplayCard(cards_abandoned.back());
		printf(" 。\n");

		player[players_with_nun[x]].cards_in_hand_.push_back(cards_abandoned.back());
		player[players_with_nun[x]].num_cards_in_hand_++;
		cards_abandoned.pop_back();
		arg_global_data.num_cards_abandoned_--;

		for (int i = 0; i < player[players_with_nun[x]].num_cards_in_hand_; i++) {
			if (player[players_with_nun[x]].cards_in_hand_[i].name_ == "修女") {
				AbandonCard(players_with_nun[x], i, CARD_STATUS_ABANDONED, arg_global_data);
				break;
			}
		}

		player[players_with_nun[x]].cards_in_hand_.back().status_ = CARD_STATUS_IN_HAND;
	}

	Pause();
	return true;
}