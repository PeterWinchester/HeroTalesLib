/* htframe.cpp
   Created - 2025/2/5
*/

#include "htframe.h"

HTBasicData::HTBasicData() {
	game_status_         = GAME_STATUS_OVER;
	num_players_         = 0;
	win_coin_number_     = 0;
	win_player_          = 0;
	num_cards_abandoned_ = 0;
	card_used_by_dragon_ = 0;
	card_used_by_monk_   = 0;
	attacking_player_    = 0;
}

HTBasicFunc::HTBasicFunc() {
	pfn_gaming_interface_ = nullptr;
}
