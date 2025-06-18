/* baby_crane.cpp
   Created - 2025/6/18
*/

#include "cards/baby_crane.h"

bool CheckBabyCrane(int arg_player) {
	for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].name_ == "送子鹤") return true;
	}
	return false;
}
