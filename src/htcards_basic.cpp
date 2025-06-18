/* htcards_basic.cpp
   Created - 2025/2/5
*/

#include "htcards_basic.h"

Card::Card() {
	level_               = CARD_NO_LEVEL;
	armory_              = CARD_ARMORY_NO_ARMORY;
	type_                = CARD_TYPE_ORDINARY;
	color_               = 0;
	status_              = 0;
	fire_property_       = CARD_PROPERTY_NO_FIRE;
	using_preference_    = 0;
	number_              = 0;
	is_transversed_      = false;
	pfn_calc_using_pref_ = NULL;
	pfn_function_        = NULL;
}

Card card[kNumYellowCards + kNumPurpleCards + 1];
std::vector<Card> cards_abandoned;

bool CompareCards(Card arg_card1, Card arg_card2) {
	if (arg_card1.level_         != arg_card2.level_)         return false;
	if (arg_card1.armory_        != arg_card2.armory_)        return false;
	if (arg_card1.type_          != arg_card2.type_)          return false;
	if (arg_card1.color_         != arg_card2.color_)         return false;
	if (arg_card1.fire_property_ != arg_card2.fire_property_) return false;
	if (arg_card1.name_          != arg_card2.name_)          return false;
	return true;
}

void DisplayCard(Card c) {
	// 设置卡牌显示颜色，黄牌用黄色，紫牌有紫色
	if (c.color_ == CARD_COLOR_YELLOW) SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_YELLOW);
	else SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_PURPLE);

	if (c.fire_property_ == CARD_PROPERTY_FIRE) printf("[火]"); // 如果是[火]类的牌，显示标签

	// 如果有纹章，显示纹章，否则显示 Lv
	if (c.armory_ & CARD_ARMORY_ROYAL)  printf("[皇]");
	if (c.armory_ & CARD_ARMORY_DAEMON) printf("[魔]");
	if (c.level_ != CARD_NO_LEVEL)      printf("Lv.%d", c.level_);

	std::cout << c.name_; // 显示卡牌名称

	// 显示卡牌类型
	if (c.type_ == CARD_TYPE_ATTACK) printf("[攻击]");
	else if (c.type_ == CARD_TYPE_CONSISTENT) printf("[持续]");
	else if (c.type_ == CARD_TYPE_TRIGGER) printf("[触发]");

	printf(" ");
	SetColor(HT_FCOLOR_WHITE | HT_BCOLOR_BLACK); // 将颜色调回白色
}

void IllustrateCard(Card c) {
	if (c.color_ == CARD_COLOR_YELLOW) SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_YELLOW);
	else SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_PURPLE);

	printf("*** ");
	DisplayCard(c);

	if (c.color_ == CARD_COLOR_YELLOW) SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_YELLOW);
	else SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_PURPLE);

	std::cout << "：" << c.description_ << "***" << std::endl;

	SetColor(HT_BCOLOR_BLACK | HT_FCOLOR_WHITE);
}