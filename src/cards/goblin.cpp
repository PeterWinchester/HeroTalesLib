/* goblin.cpp
   Created - 2025/5/17
*/

#include "cards/goblin.h"

bool Goblin(
   int          arg_player,      // 卡牌的使用者
   int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
   int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
   int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
   HTBasicData& arg_global_data, // 全局数据，描述游戏状态
   HTBasicFunc& arg_basic_func   // 基本函数集合
) {
    if (arg_status != CARD_STATUS_IN_HAND) return false;
    // 寻找目标
    int num_targets = 0;     // 钱比自己多的其他玩家数
    std::vector<int> targets; // 钱比自己多的其他玩家编号
    for (int i = 1; i <= arg_global_data.num_players_; i++) {
        if (i == arg_player) continue;
        if (player[i].num_coins_ > player[arg_player].num_coins_) {
            num_targets++;
            targets.push_back(i);
        }
    }
    
    if (!num_targets) { // 未发现目标
        if (arg_player == 1) {
            printf("没有比你钱多的玩家，不能使用 ");
            DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
            printf("！\n");
            Pause();
        }
        return false;
    }

    player[arg_player].num_action_points_--;
    arg_global_data.attacking_player_ = arg_player;

    if (arg_player != 1) {
        printf("玩家 %d 打出了 ", arg_player);
        DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
        printf("！\n");

        IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
        Pause();
    }

    // 检查魔王
    CheckTyrant(arg_player, arg_basic_func, arg_global_data);
    if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;

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

    // 丢弃哥布林
    AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
    arg_basic_func.pfn_gaming_interface_(arg_global_data);
    CheckNun(arg_player, arg_global_data);

    // 从目标玩家那里抢一块钱
    player[targets[ch]].num_coins_--;
    player[arg_player].num_coins_++;
    arg_basic_func.pfn_gaming_interface_(arg_global_data);
    printf("玩家 %d 向", targets[ch]);
    
    if (arg_player == 1) printf("你");
    else printf("玩家 %d ", arg_player);

    printf("支付了 1 金币！\n");
    Pause();
    
    // 判断是否获胜
    if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
        arg_global_data.win_player_ = arg_player;
        arg_global_data.game_status_ = GAME_STATUS_OVER;
        return true;
    }

    CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func); // 检查宝箱怪

    // 检查舞娘
    CheckDancer(arg_player, arg_global_data, arg_basic_func);
    if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
    
    CheckMinister(targets[ch], arg_global_data, arg_basic_func); // 检查大臣
    return true;
}

int calc_using_pref_goblin(
    int          arg_player, 
    HTBasicData& arg_global_data, 
    HTBasicFunc& arg_basic_func
) {
    int preference = 0;

	// 检查其他玩家的钱，如果有比自己钱多的玩家，偏好值加 2
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;
		if (player[i].num_coins_ > player[arg_player].num_coins_) {
			preference += 2;
			break;
		}
	}

	return preference;
}