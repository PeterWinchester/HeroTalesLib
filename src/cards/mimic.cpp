/* mimic.cpp
   Created - 2025/2/7
*/

#include "cards/mimic.h"

bool CheckMimic(
    int          arg_player,
    int          arg_type,
    HTBasicData& arg_global_data,
    HTBasicFunc& arg_basic_func
) {
    short num_players_with_mimic = 0;
	std::vector<short> players_with_mimic;

	// 统计有宝箱怪的玩家数
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		for (int j = 0; j < player[i].num_cards_in_hand_; j++) {
			if (player[i].cards_in_hand_[j].name_ == "宝箱怪") {
				num_players_with_mimic++;
				players_with_mimic.push_back(i);
				break;
			}
		}
	}

	if (num_players_with_mimic == 0) return false;
    
    short player_successfully_trigger = 0; // 触发宝箱怪的玩家
	
    if (num_players_with_mimic > 1) { // 多名玩家有宝箱怪
        printf("共 %d 名玩家手牌有 ", num_players_with_mimic);
		DisplayCard(card[54]);
		printf("，现随机触发。\n");

        player_successfully_trigger = rand() % num_players_with_mimic;
    }

    // 丢弃宝箱怪
    for (
        int i = 0;
        i < player[players_with_mimic[player_successfully_trigger]].num_cards_in_hand_;
        i++
    ) {
        if (player[players_with_mimic[player_successfully_trigger]].cards_in_hand_[i].name_
            == "宝箱怪") {
            AbandonCard(
                players_with_mimic[player_successfully_trigger], i, CARD_STATUS_IN_HAND,
                arg_global_data
            );
            break;
        }
    }

    if (arg_type == MIMIC_TRIGGER_GET_COIN) {
        GetOneCardFromLib(players_with_mimic[player_successfully_trigger]);
        AbandonBomb(
            players_with_mimic[player_successfully_trigger], arg_global_data, arg_basic_func
        );
        GetOneCardFromLib(players_with_mimic[player_successfully_trigger]);
        AbandonBomb(
            players_with_mimic[player_successfully_trigger], arg_global_data, arg_basic_func
        );

        arg_basic_func.pfn_gaming_interface_(arg_global_data);
        printf("玩家 %d 触发 ", players_with_mimic[player_successfully_trigger]);
        DisplayCard(card[54]);
        printf("，抽两张牌。\n");
        Pause();
    } else if (arg_type == MIMIC_TRIGGER_GET_TWO_CARDS) {
        player[players_with_mimic[player_successfully_trigger]].num_coins_++;

        arg_basic_func.pfn_gaming_interface_(arg_global_data);
        printf("玩家 %d 触发 ", players_with_mimic[player_successfully_trigger]);
        DisplayCard(card[54]);
        printf("， +1 金币。\n");
        Pause();

        if (player[players_with_mimic[player_successfully_trigger]].num_coins_
            == arg_global_data.win_coin_number_) {
            arg_global_data.win_player_ = players_with_mimic[player_successfully_trigger];
            arg_global_data.game_status_ = 0;
            return true;
        }

        CheckMimic(
            players_with_mimic[player_successfully_trigger], MIMIC_TRIGGER_GET_COIN,
            arg_global_data, arg_basic_func
        );

        CheckDancer(
            players_with_mimic[player_successfully_trigger], arg_global_data, arg_basic_func
        );
        if (arg_global_data.game_status_ != 1) return true;
    }
	return true;
}
