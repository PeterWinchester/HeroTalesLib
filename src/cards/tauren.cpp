/* tauren.cpp
   Created - 2025/5/17
*/

#include "cards/tauren.h"

bool Tauren(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
) {
    if (arg_status != CARD_STATUS_IN_HAND) return false;
    // 寻找目标
    int num_targets = 0;     // 场上有纹章牌的其他玩家数
    std::vector<int> targets; // 场上有纹章牌的其他玩家编号
    for (int i = 1; i <= arg_global_data.num_players_; i++) {
        if (i == arg_player) continue;
        bool has_armory = false;
        for (int j = 0; j < player[i].num_cards_on_field_; j++) {
            if (player[i].cards_on_field_[j].armory_ != CARD_ARMORY_NO_ARMORY) {
                has_armory = true;
                break;
            }
        }
        if (has_armory) {
            num_targets++;
            targets.push_back(i);
        }
    }
    
    if (!num_targets) { // 未发现目标
        if (arg_player == 1) {
            printf("没有其他玩家场上有纹章牌，不能使用 ");
            DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
            printf("！\n");
            Pause();
        }
        return false;
    }

    player[arg_player].num_action_points_--;
    arg_global_data.attacking_player_ = arg_player;

    // 检查魔王
    CheckTyrant(arg_player, arg_basic_func, arg_global_data);
    if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

    // 选择攻击目标
    int ch = rand() % num_targets; // 随机选择一个目标
    if (arg_player == 1) {
        printf("请选择你的攻击对象：\n");
        for (int i = 0; i < num_targets; i++) {
            printf("%d.玩家%d ", i + 1, targets[i]);
        }
        printf("\n");
        ch = restricted_input_int(1, num_targets) - 1;
    } else {
        printf("玩家 %d 将攻击对象指定为玩家 %d 。\n", arg_player, targets[ch]);
        Pause();
    }

    if (Defend(arg_player, targets[ch], arg_card, arg_mode, arg_global_data, arg_basic_func)) {
        return true;
    }

    // 丢弃牛头人
    AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
    arg_basic_func.pfn_gaming_interface_(arg_global_data);
    CheckNun(arg_player, arg_global_data);

    // 目标玩家进行选择
    int ch1 = rand() % 2 + 1; // 随机选择交付或支付
    if (targets[ch] == 1) {
        printf("请选择：\n");
        printf("1.支付 1 金币 2.交出场上所有的纹章牌\n");
        
        ch1 = restricted_input_int(1, 2);
        if (ch1 == 1 && !player[targets[ch]].num_coins_) {
            printf("你没有金币，只能交出场上的纹章牌！\n");
            Pause();
            ch1 = 2;
        }
    }
    if (ch1 == 1 && !player[targets[ch]].num_coins_) ch1 = 2;

    if (ch1 == 1) { // 目标玩家选择给钱
        player[targets[ch]].num_coins_--;
        player[arg_player].num_coins_++;

        arg_basic_func.pfn_gaming_interface_(arg_global_data);

        if (targets[ch] == 1) printf("你");
        else printf("玩家 %d ", targets[ch]);

        printf("向");

        if (arg_player == 1) printf("你");
        else printf("玩家 %d ", arg_player);

        printf("支付了 1 金币！\n");
        Pause();

        // 判断是否获胜
        if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
            arg_global_data.win_player_ = arg_player;
            arg_global_data.game_status_ = GAME_STATUS_RUNNING;
            return true;
        }

        CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func); // 检查宝箱怪

        // 检查舞娘
        CheckDancer(arg_player, arg_global_data, arg_basic_func);
        if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

        CheckMinister(targets[ch], arg_global_data, arg_basic_func); // 检查大臣
    } else { // 目标玩家选择给牌
		// 将目标玩家场上所有的纹章牌交给玩家 1
        for (int i = 0; i < player[targets[ch]].num_cards_on_field_;) {
            if (player[targets[ch]].cards_on_field_[i].armory_ != CARD_ARMORY_NO_ARMORY) {
                Card c = player[targets[ch]].cards_on_field_[i];

                c.status_ = CARD_STATUS_IN_HAND;
                player[arg_player].cards_in_hand_.push_back(c);
                player[arg_player].num_cards_in_hand_++;
                player[targets[ch]].cards_on_field_.erase(
                    player[targets[ch]].cards_on_field_.begin() + i
                );
                player[targets[ch]].num_cards_on_field_--;
            } else i++;
        }

        arg_basic_func.pfn_gaming_interface_(arg_global_data);

        if (targets[ch] == 1) printf("你");
        else printf("玩家 %d ", targets[ch]);
        
        printf("将场上的所有纹章牌交付到了");

        if (arg_player == 1) printf("你");
        else printf("玩家 %d ", arg_player);

        printf("手上。\n");
        Pause();
        
        AbandonBomb(arg_player, arg_global_data, arg_basic_func); // 检查炸弹怪
    }
    return true;
}

int calc_using_pref_tauren(
    int          arg_player,
    HTBasicData& arg_global_data,
    HTBasicFunc& arg_basic_func) {
    int preference = 0;

	// 检查其他玩家的场，如果有纹章牌，则偏好值加 2
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		bool found_armory = false;
		for (int j = 0; j < player[i].num_cards_on_field_; j++) {
			if (player[i].cards_on_field_[j].armory_ != CARD_ARMORY_NO_ARMORY) {
				preference += 2;
				found_armory = true;
				break;
			}
		}
		if (found_armory) break;
	}
	
	return preference;
}