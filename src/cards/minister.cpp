/* minister.cpp
   Created - 2025/2/7
*/

#include "cards/minister.h"

bool CheckMinister(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
    for (int i = 0; i < player[arg_player].num_cards_on_field_; i++) {
        if (player[arg_player].cards_on_field_[i].name_ == "大臣") {
            char ch = 0;
            
            if (arg_player == 1) {
                printf("你场上有大臣，是否横置？(y/n)\n");

                while (ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N') ch = _getch();
            }

            if (arg_player != 1 || ch == 'y' || ch == 'Y') { // 横置大臣
                GetOneCardFromLib(arg_player);
                arg_basic_func.pfn_gaming_interface_(arg_global_data);

                if (arg_player == 1) printf("你");
                else printf("玩家 %d ", arg_player);
                printf("横置了场上的大臣，抽了一张牌。\n");
                Pause();

                AbandonBomb(arg_player, arg_global_data, arg_basic_func);
            }

            return true;
        }
    }
    return false;
}

bool Minister(
   int          arg_player,
   int          arg_card,
   int          arg_status,
   int          arg_mode,
   HTBasicData& arg_global_data,
   HTBasicFunc& arg_basic_func
) {
    if (arg_status == CARD_STATUS_IN_HAND) {
		player[arg_player].num_action_points_--;
		PutOnField(arg_player, arg_card, arg_mode, arg_global_data);

		arg_basic_func.pfn_gaming_interface_(arg_global_data);

        if (arg_player == 1) printf("你");
        else printf("玩家 %d ", arg_player);

		printf("将 ");
		DisplayCard(player[arg_player].cards_on_field_.back());
		printf("放在了场上。\n");
		Pause();

		return true;
	}
	return false;
}

int calc_using_pref_minister(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
    int preference = 0;

    // 检查炸弹怪，若有炸弹怪，则偏好值减 1
	if (CheckBomb(arg_player)) preference--;
	
	return preference;
}
