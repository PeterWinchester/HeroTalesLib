
/* htplayer.h
   Created - 2025/2/5
*/

#ifndef HTPLAYER_H
#define HTPLAYER_H

#include <vector>
#include "htframe.h"
#include "htcards_basic.h"

class Player { // 玩家类
public:
	int num_coins_;         // 金币数
	int num_action_points_; // 行动点数
	int num_cards_in_hand_; // 手牌数
	int num_cards_on_field_; // 场牌数

	std::vector<Card> cards_in_hand_, cards_on_field_;

	Player();
};

extern Player player[kMaxNumPlayers + 1]; // 玩家数据

#endif // HTPLAYER_H
