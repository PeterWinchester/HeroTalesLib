/* berserker.cpp
   Created - 2025/2/18
*/

#include "cards/berserker.h"

int sword, num_ordinary_targets, num_blade_targets, num_saint_sword_targets;
std::vector<int> ordinary_targets, blade_targets, saint_sword_targets;

bool Berserker(
	int          arg_player,      // 卡牌的使用者
	int          arg_card,        // 卡牌编号（在手中、场上或弃牌区中的编号）
	int          arg_status,      // 卡牌状态（在手中、场上或弃牌区）
	int          arg_mode,        // 卡牌使用模式（主动打出还是被僧侣或火龙打出）
	HTBasicData& arg_global_data, // 全局数据，描述游戏状态
	HTBasicFunc& arg_basic_func   // 基本函数集合
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	// 选择攻击对象
    int target = 0;
    if (arg_player == 1) {
        printf("请选择你的攻击对象（输入玩家编号）：");
        target = restricted_input_int(2, arg_global_data.num_players_);
    } else target = berserker_choose_target(arg_player, arg_global_data);

    if (target == 0) return false; // 未找到目标直接返回

    arg_global_data.attacking_player_ = arg_player;
    player[arg_player].num_action_points_--;

	if (arg_player != 1) {
		printf("玩家 %d 打出 ", arg_player);

		if (arg_mode == CARD_MONK_MODE) DisplayCard(cards_abandoned[arg_card]);
		else DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		
        printf("，目标指定为玩家 %d ", target);

	    if (sword == USE_SAINT_SWORD) {
            printf("，并横置了 ");
            DisplayCard(card[6]);
            printf("。\n");
            IllustrateCard(card[4]);
            IllustrateCard(card[6]);
        } else if (sword == USE_BLADE) {
            printf("，并横置了 ");
            DisplayCard(card[55]);
            printf("。\n");
            IllustrateCard(card[4]);
            IllustrateCard(card[55]);
        } else {
            printf("。\n");
            IllustrateCard(card[4]);
        }

		Pause();
	}

	if (Defend(arg_player, target, arg_card, arg_mode, arg_global_data, arg_basic_func)) {
        return true;
    }

	if (arg_player == 1) {
		sword = DONNOT_USE_SWORD;

		if (CheckSaintSword(1)) { // 检查到圣剑
			printf("你场上有 ");
            DisplayCard(card[6]);
            printf("，是否横置？(y/n)\n");

            while (1) {
                char ch = _getch();
                if (ch == 'y' || ch == 'Y') { // 横置圣剑
                    sword = USE_SAINT_SWORD;
                    break;
                } else if (ch == 'n' || ch == 'N') break; // 不横置
            }
		}
        // 如果没有横置圣剑，则检查魔剑
        if (sword != USE_SAINT_SWORD && CheckBlade(1)) { // 检查到魔剑
            printf("你场上有 ");
            DisplayCard(card[55]);
            printf("，是否横置？(y/n)\n");

            while (1) {
                char ch = _getch();
                if (ch == 'y' || ch == 'Y') { // 横置魔剑
                    sword = USE_BLADE;
                    break;
                } else if (ch == 'n' || ch == 'N') break; // 不横置
            }
        }
	}

	if (sword != USE_BLADE) {
        // 丢弃狂战士
        if (arg_mode != CARD_MONK_MODE) {
            AbandonCard(arg_player, arg_card, CARD_STATUS_IN_HAND, arg_global_data);
            arg_basic_func.pfn_gaming_interface_(arg_global_data);
            CheckNun(arg_player, arg_global_data);
        }
    }

	if (sword == USE_SAINT_SWORD) { // 使用圣剑
		
        if (arg_player == 1) { // 攻击者为玩家 1
            if (player[target].num_cards_on_field_ == 0) { // 目标玩家场上没牌
                printf("攻击失败，对手场上没牌！\n");
                Pause();
                CheckMinister(target, arg_global_data, arg_basic_func);
                return true;
            }
            // 目标玩家场上有牌
            // 列出目标玩家场上的牌
            printf("请选择你要丢弃的对手场上的牌：\n");
            for (int i = 0; i < player[target].num_cards_on_field_; i++) {
                printf("%d.", i + 1);
                DisplayCard(player[target].cards_on_field_[i]);
            }
            printf("\n");

            int card_to_abandon = restricted_input_int(1, player[target].num_cards_on_field_);

            // 丢弃对应卡牌
            AbandonCard(target, card_to_abandon, CARD_STATUS_ON_FIELD, arg_global_data);
            arg_basic_func.pfn_gaming_interface_(arg_global_data);
            CheckNun(arg_player, arg_global_data);
        } else { // 攻击者不是玩家 1
            // 随机丢弃目标玩家场上的一张牌
            int card_to_abandon = rand() % player[target].num_cards_on_field_;
            AbandonCard(target, card_to_abandon, CARD_STATUS_ON_FIELD, arg_global_data);
            arg_basic_func.pfn_gaming_interface_(arg_global_data);
            CheckNun(target, arg_global_data);
        }

        if (target == 1) printf("你");
        else printf("玩家 %d ", target);

        printf("丢弃了");
        
        if (target == 1) printf("你");
        else printf("玩家 %d ", target);

        printf("场上的一张 ");
        DisplayCard(cards_abandoned.back());
        printf("。\n");

        // 结算
		if (cards_abandoned.back().level_ != CARD_NO_LEVEL && cards_abandoned.back().level_ < 4) {
			player[arg_player].num_coins_++;

			if (arg_player == 1) printf("你");
			else printf("玩家 %d ", arg_player);

			printf("丢弃的卡牌 Lv 小于 4，加 1 金币！\n");
			Pause();

			if (player[arg_player].num_action_points_ == arg_global_data.win_coin_number_) {
				arg_global_data.win_player_ = arg_player;
				arg_global_data.game_status_ = 0;
				return true;
			}

			CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);
			
			CheckDancer(arg_player, arg_global_data, arg_basic_func);
			if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
		}
    } else if (sword == USE_BLADE) { // 使用魔剑
		// 将狂战士放到场上
        PutOnField(arg_player, arg_card, arg_mode, arg_global_data);
        arg_basic_func.pfn_gaming_interface_(arg_global_data);

        int target_color = 0; // 要放在场上的卡牌颜色

        if (arg_player == 1) { // 攻击者为玩家 1
            // 检查目标玩家的手牌
            if (player[target].num_cards_in_hand_ == 0) { // 目标玩家没有手牌
                printf("该玩家没有手牌，攻击失败！\n"); // 结算
                Pause();
                CheckMinister(target, arg_global_data, arg_basic_func); // 检查大臣
                return true;
            }

            // 判断目标玩家黄色和紫色手牌的数量
            bool has_yellow_cards = 0, has_purple_cards = 0;
            for (int i = 0; i < player[target].num_cards_in_hand_; i++) {
                if (player[target].cards_in_hand_[i].color_ == CARD_COLOR_YELLOW) {
                    has_yellow_cards = true;
                } else has_purple_cards = true;
            }

            if (has_yellow_cards && has_purple_cards) { // 既有黄牌又有紫牌，需要玩家进行选择
                printf("该玩家既有黄牌又有紫牌，请选择：1.黄 2.紫");
                while (1) {
                    char ch = _getch();
                    if (ch == '1') { // 选择黄牌
                        target_color = CARD_COLOR_YELLOW;
                        break;
                    } else if (ch == '2') { // 选择紫牌
                        target_color = CARD_COLOR_PURPLE;
                        break;
                    }
                }
            } else target_color = rand() % 2;
        } else {
			// 判断目标玩家黄色和紫色手牌的数量
			bool has_yellow_cards = 0, has_purple_cards = 0;
            for (int i = 0; i < player[target].num_cards_in_hand_; i++) {
                if (player[target].cards_in_hand_[i].color_ == CARD_COLOR_YELLOW) {
                    has_yellow_cards = true;
                } else has_purple_cards = true;
            }

			if (has_yellow_cards && has_purple_cards) target_color = rand() % 2;
			else if (has_yellow_cards) target_color = CARD_COLOR_YELLOW;
			else target_color = CARD_COLOR_PURPLE;
		}

        bool res = true; // 是否可以拿钱

        // 将指定颜色的卡牌放到场上
		for (int i = 0; i < player[target].num_cards_in_hand_;) {
			if (player[target].cards_in_hand_[i].color_ == target_color) {
                if (player[target].cards_in_hand_[i].level_ == CARD_NO_LEVEL) res = false;
				PutOnField(target, i, CARD_ORDINARY_MODE, arg_global_data);
			} else i++;
		}

        // 结算
        if (res) { // 可以拿钱
            player[arg_player].num_coins_++;
            printf("攻击成功，");

            if (arg_player == 1) printf("你");
            else printf("玩家 %d", arg_player);

            printf(" +1 金币！\n");

			if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
				arg_global_data.win_player_ = arg_player;
				arg_global_data.game_status_ = GAME_STATUS_EXIT;
				return true;
			}

			CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);

			CheckDancer(arg_player, arg_global_data, arg_basic_func);
			if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
        }
	} else { // 不用剑
		bool res = true; // 是否可以拿钱
		// 将目标玩家手上的紫牌放到场上，若没有，则攻击失败
		int num_purple_cards = 0;
		for (int i = 0; i < player[target].num_cards_in_hand_; i++) {
			if (player[target].cards_in_hand_[i].color_ == CARD_COLOR_PURPLE) {
				num_purple_cards++;
				if (player[target].cards_in_hand_[i].level_ == CARD_NO_LEVEL) res = false;
				PutOnField(target, i, CARD_ORDINARY_MODE, arg_global_data);
			} else i++;
		}
		
		if (!num_purple_cards) { // 没有紫牌
			if (arg_player == 1) {
				printf("攻击失败，该玩家手上没有紫牌！\n");
				Pause();
			}
			CheckMinister(target, arg_global_data, arg_basic_func);
			return true;
		}

		if (res) { // 可以拿钱
			player[arg_player].num_coins_++;
            printf("攻击成功，");

            if (arg_player == 1) printf("你");
            else printf("玩家 %d", arg_player);

            printf(" +1 金币！\n");
        
			if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
				arg_global_data.win_player_ = arg_player;
				arg_global_data.game_status_ = GAME_STATUS_EXIT;
				return true;
			}

			CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);

			CheckDancer(arg_player, arg_global_data, arg_basic_func);
			if (arg_global_data.game_status_ != GAME_STATUS_RUNNING) return true;
		}
	}	
	CheckMinister(target, arg_global_data, arg_basic_func);
	return true;
}

int berserker_choose_target(int arg_player, HTBasicData& arg_global_data) {
	sword = berserker_choose_sword(arg_player, arg_global_data);

	switch (sword) {
	case USE_BLADE:
		return blade_targets[rand() % num_blade_targets];

	case USE_SAINT_SWORD:
		return saint_sword_targets[rand() % num_saint_sword_targets];
	}

	if (num_ordinary_targets) return ordinary_targets[rand() % num_ordinary_targets];
	return 0;
}

int berserker_choose_sword(int arg_player, HTBasicData& arg_global_data) {
	num_blade_targets       = 0;
	num_saint_sword_targets = 0;
	num_ordinary_targets    = 0;

	blade_targets.clear();
	saint_sword_targets.clear();
	ordinary_targets.clear();

	// 分别统计不使用圣剑和魔剑可以攻击的玩家、使用圣剑可以攻击的玩家、使用魔剑可以攻击的玩家
	for (int i = 1; i <= arg_global_data.num_players_; i++) {
		if (i == arg_player) continue;

		// 手上有牌就可以使用魔剑攻击
		if (player[i].num_cards_in_hand_) {
			num_blade_targets++;
			blade_targets.push_back(i);
		}

		// 场上有牌就可以用圣剑
		if (player[i].num_cards_on_field_) {
			num_saint_sword_targets++;
			saint_sword_targets.push_back(i);
		}

		// 手上有紫牌可以不用剑
		for (int j = 0; j < player[i].num_cards_in_hand_; j++) {
			if (player[i].cards_in_hand_[j].color_ == CARD_COLOR_PURPLE) {
				num_ordinary_targets++;
				ordinary_targets.push_back(i);
				break;
			}
		}
	}

	if (num_blade_targets && CheckBlade(arg_player)) return USE_BLADE;
	if (num_saint_sword_targets && CheckSaintSword(arg_player)) return USE_SAINT_SWORD;
	return DONNOT_USE_SWORD;
}

int calc_using_pref_berserker(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;
	
	// 检查其他玩家的手牌，若有紫牌，则偏好值加 1
	if (CheckPurpleCards(arg_player, arg_global_data)) preference++;

	return preference;
}
