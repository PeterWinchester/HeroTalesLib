
/* warrior.cpp
   Created - 2025/2/8
*/

#include "cards/warrior.h"

bool CheckPurpleCards(int arg_player, HTBasicData& arg_global_data) {
    for (int i = 1; i <= arg_global_data.num_players_; i++) {
        if (i == arg_player) continue;
        for (int j = 0; j < player[i].num_cards_in_hand_; j++) {
            if (player[i].cards_in_hand_[j].color_ == CARD_COLOR_PURPLE) return true;
        }
    }
    return false;
}
