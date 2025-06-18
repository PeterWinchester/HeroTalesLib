/* dancer.cpp
   Created - 2025/2/7
*/

#include "cards/dancer.h"

bool CheckDancer(int arg_player, HTBasicData& arg_global_data, HTBasicFunc& arg_basic_func) {
    for (int i = 1; i <= arg_global_data.num_players_; i++) {
        if (i == arg_player) continue;

        for (int j = 0; j < player[i].num_cards_on_field_; j++) {
            if (player[i].cards_on_field_[j].name_ == "舞娘") {
                char ch = 0;

                if (i == 1) {
                    printf("你场上有 ");
					DisplayCard(player[i].cards_on_field_[j]);
					printf("，是否丢弃一张获得一个金币？(y/n)\n");

                    while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N') ch = _getch();
                }

                if (i != 1 || ch == 'y' || ch == 'Y') {
                    AbandonCard(i, j, CARD_STATUS_ON_FIELD, arg_global_data);
                    player[i].num_coins_++;

                    arg_basic_func.pfn_gaming_interface_(arg_global_data);

                    if (i != 1) {
                        printf("玩家 %d 丢弃了场上的 ", i);
                        DisplayCard(cards_abandoned.back());
                        printf("，获得了一个金币！\n");
                        Pause();
                    }
                    
                    CheckNun(i, arg_global_data);

                    if (player[i].num_coins_ == arg_global_data.win_coin_number_) {
                        arg_global_data.win_player_ = i;
                        arg_global_data.game_status_ = 0;
                        return true;
                    }

                    CheckMimic(i, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);

                    CheckDancer(i, arg_global_data, arg_basic_func);
                    if (arg_global_data.game_status_ != 1) return true;
                }
            }
        }
    }
    return true;
}

bool Dancer(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	player[arg_player].num_action_points_--;
	PutOnField(arg_player, arg_card, arg_mode, arg_global_data);

	arg_basic_func.pfn_gaming_interface_(arg_global_data);

	if (arg_player == 1) printf("你");
	else printf("玩家 %d ", arg_player);

	printf("将 ");
	DisplayCard(player[arg_player].cards_on_field_.back());
	printf("放在了场上。\n");
	IllustrateCard(player[arg_player].cards_on_field_.back());
	Pause();
	return true;
}

int calc_using_pref_dancer(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 1; // 舞娘相当于一块钱，初始值给高一点

	// 检查火龙，若其他玩家场上有火龙，则偏好值减 1
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (CheckDragon(i)) {
			preference--;
			break;
		}
	}
	
	return preference;
}
