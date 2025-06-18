/* htplayer.cpp
   Created - 2025/2/5
*/

#include "htplayer.h"

Player player[kMaxNumPlayers + 1];

Player::Player() {
	num_coins_         = 0;
	num_action_points_ = 0;
	num_cards_in_hand_ = 0;
	num_cards_on_field_ = 0;
}
