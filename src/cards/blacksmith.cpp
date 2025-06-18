/* blacksmith.cpp
   Created - 2025/2/8
*/

#include "cards/blacksmith.h"

bool BlackSmith(
    int          arg_player,
    int          arg_card,
    int          arg_status,
    int          arg_mode,
    HTBasicData& arg_global_data,
    HTBasicFunc& arg_basic_func
) {
    if (arg_status != CARD_STATUS_IN_HAND) return false;
    // 检查手牌数，若这张铁匠在手上，则手牌数不能小于 3；若这张铁匠是僧侣打出的，则手牌数不能小于 2
    if (player[arg_player].num_cards_in_hand_ < 3 - (arg_mode == CARD_MONK_MODE)) {
        if (arg_player != 1) return false;

        printf("你的手牌不足，不能使用 ");
        DisplayCard(card[7]);
        printf("！\n");
        Pause();
        return false;
    }

    player[arg_player].num_action_points_--;

    if (arg_player != 1) {
        printf("玩家 %d 打出了 ", arg_player);
        DisplayCard(card[7]);
        printf("。\n");
        IllustrateCard(card[7]);
        Pause();
    }

    // 若不是僧侣模式，则需将铁匠丢弃
    if (arg_mode != CARD_MONK_MODE) {
        AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
        arg_basic_func.pfn_gaming_interface_(arg_global_data);
        CheckNun(arg_player, arg_global_data);
    }

    int card1_chosen_num = 0, card2_chosen_num = 1; // 选择的两张手牌编号

    if (arg_player == 1) {
        // 选择两张手牌
        printf("请选择你要放在场上的两张牌（输入两个数字，一个数字各一行）：\n");
        for (int i = 0; i < player[1].num_cards_in_hand_; i++) {
            printf("%d.", i + 1);
            DisplayCard(player[1].cards_in_hand_[i]);
        }
        printf("\n");

        while (1) {
            card1_chosen_num = restricted_input_int(1, player[1].num_cards_in_hand_) - 1;
            card2_chosen_num = restricted_input_int(1, player[1].num_cards_in_hand_) - 1;
            if (card1_chosen_num == card2_chosen_num) {
                printf("请选择两张不同的牌！\n");
                Pause();
            } else break;
        }
    } else {
        // 选择两张手牌
        for (int i = 0; i < player[arg_player].num_cards_in_hand_ - 1; i++) {
            bool found_proper_cards = false;
            for (int j = i + 1; j < player[arg_player].num_cards_in_hand_; j++) {
                Card card_i = player[arg_player].cards_in_hand_[i];
                Card card_j = player[arg_player].cards_in_hand_[j];
                
                if (card_i.armory_ != CARD_ARMORY_NO_ARMORY && card_i.armory_ == card_j.armory_) {
                    card1_chosen_num = i;
                    card2_chosen_num = j;
                    found_proper_cards = true;
                    break;
                }

                if (card_i.level_ != CARD_NO_LEVEL && card_i.level_ == card_j.level_) {
                    card1_chosen_num = i;
                    card2_chosen_num = j;
                    found_proper_cards = true;
                    break;
                }
            }
            if (found_proper_cards) break;
        }
        // 如果在以上过程中没有找到合适的手牌，则 card1_chosen_num 和 card2_chosen_num 分别保持初始值 0 和 1
    }

    Card card1_chosen = player[arg_player].cards_in_hand_[card1_chosen_num];
    Card card2_chosen = player[arg_player].cards_in_hand_[card2_chosen_num];

    PutOnField(arg_player, std::max(card1_chosen_num, card2_chosen_num), CARD_ORDINARY_MODE, 
               arg_global_data);
    PutOnField(arg_player, std::min(card1_chosen_num, card2_chosen_num), CARD_ORDINARY_MODE,
               arg_global_data);

	// 结算
	bool get_coin = false;
    if (card1_chosen.armory_ != CARD_ARMORY_NO_ARMORY
        && card1_chosen.armory_ == card2_chosen.armory_) {
        // 加钱
		player[arg_player].num_coins_++;
		get_coin = true;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);

		printf("放的两张牌纹章相同，");
    } else if (card1_chosen.level_ != CARD_NO_LEVEL && card1_chosen.level_ == card2_chosen.level_) {
		// 加钱
		player[arg_player].num_coins_++;
		get_coin = true;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("你");
		else printf("玩家 %d ", arg_player);

		printf("放的两张牌 Lv 相同，");
	}

	if (!get_coin) return true;

	if (arg_player == 1) printf("你");
	else printf("玩家 %d", arg_player);

	printf(" +1 金币！\n");
	Pause();

	if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
		arg_global_data.win_player_ = arg_player;
		arg_global_data.game_status_ = 0;
		return true;
	}

	CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);
	CheckDancer(arg_player, arg_global_data, arg_basic_func);
    return true;
}

int calc_using_pref_blacksmith(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// 检查手牌，如果有 Lv 或纹章相同的，偏好值加 2
	for (int i = 0; i < player[arg_player].num_cards_in_hand_ - 1; i++) {
		for (int j = i + 1; j < player[arg_player].num_cards_in_hand_; j++) {
			Card card_i = player[arg_player].cards_in_hand_[i];
			Card card_j = player[arg_player].cards_in_hand_[j];
			
			if (card_i.level_ != CARD_NO_LEVEL && card_i.level_ == card_j.level_) {
				preference += 2;
				break;
			} else if (card_i.armory_ != CARD_ARMORY_NO_ARMORY
					   && card_i.armory_ == card_j.armory_) {
				preference += 2;
				break;
			}
		}
	}

	return preference;
}
