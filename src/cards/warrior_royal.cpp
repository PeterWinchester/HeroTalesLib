/* warrior_royal.cpp
   Created - 2025/2/7
*/

#include "cards/warrior_royal.h"

int sword, num_ordinary_targets, num_blade_targets, num_saint_sword_targets;
std::vector<int> ordinary_targets, blade_targets, saint_sword_targets;

bool WarriorRoyal(
   int          arg_player,
   int          arg_card,
   int          arg_status,
   int          arg_mode,
   HTBasicData& arg_global_data,
   HTBasicFunc& arg_basic_func
) {
    if (arg_status != CARD_STATUS_IN_HAND) return false;

    // 选择攻击对象
    int target = 0;
    if (arg_player == 1) {
        printf("请选择你的攻击对象（输入玩家编号）：");
        target = restricted_input_int(2, arg_global_data.num_players_);
    } else target = warrior_royal_choose_target(arg_player, arg_global_data);

    if (target == 0) return false; // 未找到目标直接返回

    arg_global_data.attacking_player_ = arg_player;
    player[arg_player].num_action_points_--;

    if (arg_player != 1) {
        printf("玩家 %d 打出 ", arg_player);
        DisplayCard(card[4]);
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
        // 丢弃勇者
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

            int card_to_abandon = restricted_input_int(1, player[target].num_cards_on_field_) - 1;

            // 丢弃对应卡牌
            AbandonCard(target, card_to_abandon, CARD_STATUS_ON_FIELD, arg_global_data);
            arg_basic_func.pfn_gaming_interface_(arg_global_data);
        } else { // 攻击者不是玩家 1
            // 随机丢弃目标玩家场上的一张牌
            int card_to_abandon = rand() % player[target].num_cards_on_field_;
            AbandonCard(target, card_to_abandon, CARD_STATUS_ON_FIELD, arg_global_data);
            arg_basic_func.pfn_gaming_interface_(arg_global_data);
        }

        if (target == 1) printf("你");
        else printf("玩家 %d ", target);

        printf("丢弃了");
        
        if (target == 1) printf("你");
        else printf("玩家 %d ", target);

        printf("场上的一张 ");
        DisplayCard(cards_abandoned.back());
        printf("。\n但是");

        if (target == 1) printf("你");
        else printf("玩家 %d ", target);

        printf("打出的勇者没有 Lv，无法获得金币。\n");
        Pause();

		CheckNun(target, arg_global_data);
        CheckMinister(target, arg_global_data, arg_basic_func);
    } else if (sword == USE_BLADE) { // 使用魔剑
        // 将勇者放到场上
        PutOnField(arg_player, arg_card, arg_mode, arg_global_data);
        arg_basic_func.pfn_gaming_interface_(arg_global_data);

        int target_card_num = 0; // 要放在场上的卡牌编号

        if (arg_player == 1) { // 攻击者为玩家 1
            // 检查目标玩家的手牌
            if (player[target].num_cards_in_hand_ == 0) { // 目标玩家没有手牌
                printf("该玩家没有手牌，攻击失败！\n"); // 结算
                Pause();
                CheckMinister(target, arg_global_data, arg_basic_func); // 检查大臣
                return true;
            }

            // 统计目标玩家黄色和紫色手牌的数量
            int num_yellow_cards = 0, num_purple_cards = 0;
            std::vector<int> yellow_cards, purple_cards; // 目标玩家手上两种颜色的卡牌的编号
            for (int i = 0; i < player[target].num_cards_in_hand_; i++) {
                if (player[target].cards_in_hand_[i].color_ == CARD_COLOR_YELLOW) {
                    num_yellow_cards++;
                    yellow_cards.push_back(i);
                } else {
                    num_purple_cards++;
                    purple_cards.push_back(i);
                }
            }

            if (num_yellow_cards && num_purple_cards) { // 既有黄牌又有紫牌，需要玩家进行选择
                printf(
                    "该玩家有 %d 张黄牌和 %d 张紫牌，请选择：1.黄 2.紫", num_yellow_cards,
                    num_purple_cards
                );
                while (1) {
                    char ch = _getch();
                    if (ch == '1') { // 选择黄牌
                        target_card_num = yellow_cards[rand() % num_yellow_cards];
                        break;
                    } else if (ch == '2') { // 选择紫牌
                        target_card_num = purple_cards[rand() % num_purple_cards];
                        break;
                    }
                }
            } else target_card_num = rand() % player[target].num_cards_in_hand_;
        } else target_card_num = rand() % player[target].num_cards_in_hand_;

        Card target_card = player[target].cards_in_hand_[target_card_num];

        // 结算，放置在场上的牌带有 Lv 或 [魔] 就可以加钱
        if (target_card.level_ != CARD_NO_LEVEL || target_card.armory_ & CARD_ARMORY_DAEMON) {
            // 加钱
            player[arg_player].num_coins_++;
            arg_basic_func.pfn_gaming_interface_(arg_global_data);
            printf("攻击成功，");
            
            if (arg_player == 1) printf("你");
            else printf("玩家 %d", arg_player);

            printf(" +1 金币！\n");

            // 判断是否获胜
            if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
                arg_global_data.win_player_ = arg_player;
                arg_global_data.game_status_ = 0;
                return true;
            }
            
            CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);
            
            CheckDancer(arg_player, arg_global_data, arg_basic_func);
            if (arg_global_data.game_status_ != 1) return true;
        }
        Pause();

        CheckMinister(target, arg_global_data, arg_basic_func);
    } else { // 不用剑
        // 统计目标玩家手上的紫牌
        int num_purple_cards = 0;
        std::vector<int> purple_cards;
        for (int i = 0; i < player[target].num_cards_in_hand_; i++) {
            if (player[target].cards_in_hand_[i].color_ == CARD_COLOR_PURPLE) {
                num_purple_cards++;
                purple_cards.push_back(i);
            }
        }
        
        if (arg_player == 1 && !num_purple_cards) { // 如果目标玩家手上没有紫牌
            printf("玩家 %d 手上没有紫牌，攻击失败！\n", target);
            Pause();
            return true;
        }

        // 随机选择目标玩家一张紫色手牌放在场上
        int target_card_num = purple_cards[rand() % num_purple_cards];
        Card target_card = player[target].cards_in_hand_[target_card_num];
        PutOnField(target, target_card_num, CARD_ORDINARY_MODE, arg_global_data);
        arg_basic_func.pfn_gaming_interface_(arg_global_data);

        // 结算
        if (target_card.level_ != CARD_NO_LEVEL || target_card.armory_ & CARD_ARMORY_DAEMON) {
            // 加钱
            player[arg_player].num_coins_++;
            arg_basic_func.pfn_gaming_interface_(arg_global_data);
            printf("攻击成功，");

            if (arg_player == 1) printf("你");
            else printf("玩家 %d", arg_player);

            printf(" +1 金币！\n");
            Pause();

            // 判断是否获胜
            if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
                arg_global_data.win_player_ = arg_player;
                arg_global_data.game_status_ = 0;
                return true;
            }

            CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);

            CheckDancer(arg_player, arg_global_data, arg_basic_func);
            if (arg_global_data.game_status_ != 1) return true;
        }
        Pause();

        CheckMinister(target, arg_global_data, arg_basic_func);
    }
    return true;
}

int warrior_royal_choose_target(int arg_player, HTBasicData& arg_global_data) {
    sword = warrior_royal_choose_sword(arg_player, arg_global_data);
    
    switch (sword) {
        case USE_BLADE:
        return blade_targets[rand() % num_blade_targets];

        case USE_SAINT_SWORD:
        return saint_sword_targets[rand() % num_saint_sword_targets];
    }
    if (num_ordinary_targets) return ordinary_targets[rand() % num_ordinary_targets];
    return 0; // 未找到目标，返回 0
}

int warrior_royal_choose_sword(int arg_player, HTBasicData& arg_global_data) {
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

int calc_using_pref_warrior_royal(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
    int preference = 0;

	// 检查其他玩家的紫牌，若有紫牌，则偏好值加 1
	if (CheckPurpleCards(arg_player, arg_global_data)) preference++;

	// 检查魔剑，若有魔剑，则偏好值加 1
	if (CheckBlade(arg_player)) preference++;

	return preference;
}
