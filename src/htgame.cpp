/* htgame.cpp
   Created - 2025/2/6
*/

#include "htgame.h"

void DefaultGamingInterface(HTBasicData& arg_global_data) {
	ClearScreen();
	SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_WHITE);

	// 显示玩家 1 的钱和手牌
	printf("你（玩家1）金币：%d/%d 手牌：", player[1].num_coins_, arg_global_data.win_coin_number_);
	if (!player[1].num_cards_in_hand_) printf("无 ");
	for (int i = 0; i < player[1].num_cards_in_hand_; i++) DisplayCard(player[1].cards_in_hand_[i]);
	
	// 显示玩家 1 的场牌
	printf("\n    场牌：");
	if (!player[1].num_cards_on_field_) printf("无 ");
	for (int i = 0; i < player[1].num_cards_on_field_; i++) {
		DisplayCard(player[1].cards_on_field_[i]);
	}
	printf("\n");

	for (int i = 2; i <= arg_global_data.num_players_; i++) {
		// 显示玩家 i 的金币
		printf("玩家%d 金币：", i);
		if (player[i].num_coins_ == arg_global_data.win_coin_number_ - 1) {
			SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_RED);
		}
		printf("%d", player[i].num_coins_);
		SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_WHITE);

		// 显示玩家 i 的手牌
		printf("/%d 手牌：", arg_global_data.win_coin_number_);
		if (!player[i].num_cards_in_hand_) printf("无 ");
		else {
			int num_yellow = 0, num_purple = 0;
			for (int j = 0; j < player[i].num_cards_in_hand_; j++) {
				if (player[i].cards_in_hand_[j].color_ == CARD_COLOR_YELLOW) num_yellow++;
				else num_purple++;
			}
			printf("%d黄%d紫", num_yellow, num_purple);
		}

		// 显示玩家 i 的场牌
		printf("\n    场牌：");
		if (!player[i].num_cards_on_field_) printf("无 ");
		for (int j = 0; j < player[i].num_cards_on_field_; j++) {
			DisplayCard(player[i].cards_on_field_[j]);
		}
		printf("\n");
	}
	printf("---------------------------------------\n");
}

void ReturnCardOnField(int arg_player, int arg_card) {
	player[arg_player].cards_on_field_[arg_card].is_transversed_ = false;
	player[arg_player].cards_on_field_[arg_card].status_ = CARD_STATUS_IN_HAND;
	player[arg_player].cards_in_hand_.push_back(player[arg_player].cards_on_field_[arg_card]);
	player[arg_player].cards_on_field_.erase(player[arg_player].cards_on_field_.begin() + arg_card);
	player[arg_player].num_cards_on_field_--;
	player[arg_player].num_cards_in_hand_++;
}

void PutOnField(int arg_player, int arg_card, int arg_mode, HTBasicData& arg_global_data) {
	Card c;
	if (arg_mode == CARD_MONK_MODE || arg_mode == CARD_DRAGON_MODE) {
		// 如果是僧侣或火龙模式，则指定卡牌在弃牌区
		c = cards_abandoned[arg_card];
		cards_abandoned.erase(cards_abandoned.begin() + arg_card);
		arg_global_data.num_cards_abandoned_--;
	} else { // 否则指定卡牌在指定玩家手中
		c = player[arg_player].cards_in_hand_[arg_card];
		player[arg_player].cards_in_hand_.erase(
			player[arg_player].cards_in_hand_.begin() + arg_card
		);
		player[arg_player].num_cards_in_hand_--;
	}

	c.is_transversed_ = false;
	c.status_ = CARD_STATUS_ON_FIELD;
	player[arg_player].cards_on_field_.push_back(c);
	player[arg_player].num_cards_on_field_++;
}

void AbandonCard(int arg_player, int arg_card, int arg_status, HTBasicData& arg_global_data) {
	Card c;
	if (arg_status == CARD_STATUS_IN_HAND) {
		c = player[arg_player].cards_in_hand_[arg_card];
		player[arg_player].cards_in_hand_.erase(
			player[arg_player].cards_in_hand_.begin() + arg_card
		);
		player[arg_player].num_cards_in_hand_--;
	} else if (arg_status == CARD_STATUS_ON_FIELD) {
		c = player[arg_player].cards_on_field_[arg_card];
		player[arg_player].cards_on_field_.erase(
			player[arg_player].cards_on_field_.begin() + arg_card
		);
		player[arg_player].num_cards_on_field_--;
	}
	c.status_ = CARD_STATUS_ABANDONED;
	cards_abandoned.push_back(c);
	arg_global_data.num_cards_abandoned_++;
}

void GetOneCardFromLib(int arg_player) {
	int x = rand() % (kNumYellowCards + kNumPurpleCards) + 1;

	card[x].status_ = CARD_STATUS_IN_HAND;
	player[arg_player].cards_in_hand_.push_back(card[x]);
	player[arg_player].num_cards_in_hand_++;
	card[x].status_ = CARD_STATUS_IN_LIBRARY;
}

void AddAbandonedCardToHand(int arg_player, int arg_card, HTBasicData& arg_global_data) {
	cards_abandoned[arg_card].status_ = CARD_STATUS_IN_HAND;
	player[arg_player].cards_in_hand_.push_back(cards_abandoned[arg_card]);
	player[arg_player].num_cards_in_hand_++;
	cards_abandoned.erase(cards_abandoned.begin() + arg_card);
	arg_global_data.num_cards_abandoned_--;
}

bool Defend(
	int          arg_attacker,
	int          arg_target, 
	int          arg_card,
	int          arg_mode,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
) {
	// 检查卫兵和圣骑士
	bool found_guard = CheckGuard(arg_target), found_holy_knight = CheckHolyKnight(arg_target);

	if (found_guard && found_holy_knight) { // 既有卫兵又有圣骑士
		char option_chosen = '1' + rand() % 2; // 选择卫兵或圣骑士

		if (arg_target == 1) {
			printf("你手中同时有卫兵和圣骑士，请选择触发：\n");
			printf("1.卫兵 2.圣骑士\n");

			option_chosen = _getch();
			while (option_chosen != '1' && option_chosen != '2') option_chosen = _getch();
		}

		if (option_chosen == '1') {
			UseGuard(arg_attacker, arg_target, arg_card, arg_mode, arg_global_data, arg_basic_func);
			return true;
		}  else {
			return UseHolyKnight(arg_attacker, arg_target, arg_card, arg_mode, arg_global_data,
								 arg_basic_func);
		}
	} else if (found_guard) { // 只有卫兵
		UseGuard(arg_attacker, arg_target, arg_card, arg_mode, arg_global_data, arg_basic_func);
		return true;
	} else if (found_holy_knight) { // 只有圣骑士
		return UseHolyKnight(arg_attacker, arg_target, arg_card, arg_mode, arg_global_data,
							 arg_basic_func);
	}
	return false;
}
