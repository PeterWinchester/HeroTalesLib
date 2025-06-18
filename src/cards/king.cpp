/* king.cpp
   Created - 2025/2/8
*/

#include "cards/king.h"

bool King(
    int          arg_player,
    int          arg_card,
    int          arg_status,
    int          arg_mode,
    HTBasicData& arg_global_data,
    HTBasicFunc& arg_basic_func
) {
    if (arg_status == CARD_STATUS_IN_HAND) { // 在手上，对应打出
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
    } else if (arg_status == CARD_STATUS_ON_FIELD) { // 在场上，对应横置
        // 在弃牌区寻找 Lv.4 勇者
        for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
            if (cards_abandoned[i].name_ == "勇者" && cards_abandoned[i].level_ == 4) {
                AddAbandonedCardToHand(arg_player, i, arg_global_data); // 将勇者加入手牌
                arg_basic_func.pfn_gaming_interface_(arg_global_data);

                if (arg_player == 1) printf("你");
                else printf("玩家 %d ", arg_player);

                printf("横置 ");
                DisplayCard(player[arg_player].cards_on_field_[arg_card]);
                printf("，将弃牌区的一张 ");
                DisplayCard(player[arg_player].cards_in_hand_.back());
                printf("加入了手牌。\n");
                Pause();

                AbandonBomb(arg_player, arg_global_data, arg_basic_func);
                return true;
            }
        }

        // 未找到勇者
        if (arg_player == 1) printf("你");
        else printf("玩家 %d ", arg_player);

        printf("横置了 ");
        DisplayCard(player[arg_player].cards_on_field_[arg_card]);
        printf("，但是弃牌区没有 ");
        DisplayCard(card[48]);
        printf("。\n");
        Pause();
        return true;
    }
    return false;
}

int calc_using_pref_king(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
    int preference = 0;

	// 检查弃牌区，若有 Lv.4 勇者，则偏好值加 1
	for (int i = 0; i < arg_global_data.num_cards_abandoned_; i++) {
		if (cards_abandoned[i].name_ == "勇者" && cards_abandoned[i].level_ == 4) {
			preference++;
			break;
		}
	}

	return preference;
}
