/* htcards_init.cpp
   Created - 2025/2/6
*/

#include "htcards_init.h"

void InitCards() {
	int current_card = 0;
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_ROYAL;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "在你的准备阶段，若只差 1 金币获胜，则直接获胜。";
		card[current_card].name_                = "圣杯";
		card[current_card].pfn_function_        = Grail;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_grail;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_ROYAL;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "当你被[攻击]卡牌指定时，待[攻击]卡牌结算后，若本牌在你场上，可横置本牌，你抽一张牌。";
		card[current_card].name_                = "大臣";
		card[current_card].pfn_function_        = Minister;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_minister;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_ROYAL;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "打出本牌不消耗行动点，若本牌在你场上，在你的准备阶段，你 +1 金币。";
		card[current_card].name_                = "公主";
		card[current_card].pfn_function_        = Princess;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_princess;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_ROYAL;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "将一名对手的一张非黄色手牌置于其场上，若该手牌带有 Lv 或 [魔]，你 +1 金币。";
		card[current_card].name_                = "勇者";
		card[current_card].pfn_function_        = WarriorRoyal;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_warrior_royal;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_ROYAL;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "横置，将弃牌区的一张 Lv.4 勇者加入手牌。";
		card[current_card].name_                = "国王";
		card[current_card].pfn_function_        = King;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_king;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_ROYAL;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "当你使用勇者时，横置本牌，将勇者的效果改为丢弃对手场上的一张牌，若丢弃的牌 Lv 低于勇者，你 +1 金币。";
		card[current_card].name_                = "圣剑";
		card[current_card].pfn_function_        = SaintSword;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_saint_sword;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 0;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "将两张手牌放置在你场上，若因此放置的手牌 Lv 或纹章相同，你 +1 金币。";
		card[current_card].name_                = "铁匠";
		card[current_card].pfn_function_        = BlackSmith;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_blacksmith;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 0;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "将你的全部手牌放置在场上，若因此放置的手牌 Lv 之和为偶数且不存在纹章，你 +1 金币。";
		card[current_card].name_                = "格斗家";
		card[current_card].pfn_function_        = Fighter;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_fighter;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 1;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "从弃牌区选 1 张 Lv.1 以外的黄色卡牌不消耗行动点打出，或将其加入手牌。";
		card[current_card].name_                = "僧侣";
		card[current_card].pfn_function_        = Monk;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_monk;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 1;
		card[current_card].type_                = CARD_TYPE_TRIGGER;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "对手有 Lv.1 以外的卡牌进入弃牌区时，将要丢弃的卡牌加入你的手牌。";
		card[current_card].name_                = "修女";
		card[current_card].pfn_function_        = nullptr;
		card[current_card].pfn_calc_using_pref_ = nullptr;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 1;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "将你场上的一张牌加入对手的手牌，那名对手向你支付 1 金币。";
		card[current_card].name_                = "商人";
		card[current_card].pfn_function_        = Businessman;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_businessman;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 2;
		card[current_card].type_                = CARD_TYPE_TRIGGER;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "当你的准备阶段时，若有 2 张及以上的其它卡牌回到手中，你 +1 金币。";
		card[current_card].name_                = "送子鹤";
		card[current_card].pfn_function_        = nullptr;
		card[current_card].pfn_calc_using_pref_ = nullptr;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 2;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "打出后放置在你场上。若本牌在你场上，对手获得金币后，你可以丢弃此牌，并 +1 金币。";
		card[current_card].name_                = "舞娘";
		card[current_card].pfn_function_        = Dancer;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_dancer;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 2;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "向一名有手牌的对手宣言 1/2/3/4 中的一个数，他必须放置此等级的牌到其场上，否则你 +1 金币。";
		card[current_card].name_                = "法师";
		card[current_card].pfn_function_        = Master;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_master;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 3;
		card[current_card].type_                = CARD_TYPE_TRIGGER;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "当你被[攻击]卡牌指定时，令那张牌无效，并将其放置在出牌者场上，之后你抽一张牌。";
		card[current_card].name_                = "卫兵";
		card[current_card].pfn_function_        = nullptr;
		card[current_card].pfn_calc_using_pref_ = nullptr;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 3;
		card[current_card].type_                = CARD_TYPE_TRIGGER;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "当你被[攻击]卡牌指定时，你抽 2 张牌；或者，令该[攻击]卡牌无效并返回拥有者手中，你抽 1 张牌。";
		card[current_card].name_                = "圣骑士";
		card[current_card].pfn_function_        = nullptr;
		card[current_card].pfn_calc_using_pref_ = nullptr;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 4;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "指定一名对手的全部非黄色手牌放置于其场上，若均带有 Lv，你 +1 金币，本牌名称也视作“勇者”。";
		card[current_card].name_                = "狂战士";
		card[current_card].pfn_function_        = Berserker;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_berserker;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 4;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "指定一名对手的一张非黄色手牌放置于其场上，若本牌 Lv 更高，你 +1 金币。";
		card[current_card].name_                = "勇者";
		card[current_card].pfn_function_        = Warrior_Lv;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_warrior_lv;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_YELLOW;
		card[current_card].level_               = 5;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "指定一名对手的一张非黄色手牌放置于其场上，若本牌 Lv 更高，你 +1 金币。";
		card[current_card].name_                = "勇者";
		card[current_card].pfn_function_        = Warrior_Lv;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_warrior_lv;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_ROYAL | CARD_ARMORY_DAEMON;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "放置一张对手手牌于其场上，若带有 Lv, 你 +1 金币；若带有纹章，则从任意处将“魔剑”加入手牌。";
		card[current_card].name_                = "黑骑士";
		card[current_card].pfn_function_        = BlackKnight;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_black_knight;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_DAEMON;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "横置，将你场上的一张牌加入手牌。";
		card[current_card].name_                = "妖精";
		card[current_card].pfn_function_        = Demon;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_demon;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].fire_property_       = CARD_PROPERTY_FIRE;
		card[current_card].armory_              = CARD_ARMORY_DAEMON;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "横置，将弃牌区的一张[火]不消耗行动点打出，或将其加入手牌。";
		card[current_card].name_                = "火龙";
		card[current_card].pfn_function_        = FireDragon;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_fire_dragon;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_DAEMON;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "当你打出一张带有 Lv 的紫色牌后，横置本牌，你 +1 金币。";
		card[current_card].name_                = "魔王";
		card[current_card].pfn_function_        = Tyrant;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_tyrant;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_DAEMON;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_TRIGGER;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "当对手获得金币后，你抽两张牌；或者，当对手 2 行动点均抽牌后，你 +1 金币。";
		card[current_card].name_                = "宝箱怪";
		card[current_card].pfn_function_        = NULL;
		card[current_card].pfn_calc_using_pref_ = NULL;
	}
	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_DAEMON;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "你打出“勇者”时，横置本牌，该勇者打出后放置于你的场上无需丢弃，且“勇者”的效果可指定任意一种颜色。";
		card[current_card].name_                = "魔剑";
		card[current_card].pfn_function_        = Blade;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_blade;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].fire_property_       = CARD_PROPERTY_FIRE;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "选择每个场上有牌的对手，令他们场上的一张牌返回手牌。若那些牌均带有 Lv，你 +1 金币。";
		card[current_card].name_                = "龙幼崽";
		card[current_card].pfn_function_        = DragonCub;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_dragon_cub;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].fire_property_       = CARD_PROPERTY_FIRE;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "丢弃一名对手场上的一张牌，若那张牌带有 Lv，你 +1 金币。";
		card[current_card].name_                = "龙炎";
		card[current_card].pfn_function_        = DragonFlame;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_dragon_flame;
	}

	for (int i = 1; i <= 1; i++) {
		current_card++;
		card[current_card].fire_property_       = CARD_PROPERTY_FIRE;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = CARD_NO_LEVEL;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "从紫色牌库或弃牌区选一张[火]加入手牌。";
		card[current_card].name_                = "龙蛋";
		card[current_card].pfn_function_        = DragonEgg;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_dragon_egg;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 0;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "将弃牌区的一张 Lv.1 牌或者 Lv.2 牌加入你的手牌。";
		card[current_card].name_                = "史莱姆";
		card[current_card].pfn_function_        = Slime;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_slime;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 1;
		card[current_card].type_                = CARD_TYPE_CONSISTENT;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "放置到对手场上成为他的牌。若你的场上放置了本牌，在准备阶段前，需选择你场上另一张牌返回手中。任何情况使你手牌数不小于5时，可丢弃本牌。";
		card[current_card].name_                = "炸弹怪";
		card[current_card].pfn_function_        = Bomb;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_bomb;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 1;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "秘密查看一名对手的全部手牌，之后令他场上的牌全部回到手牌。";
		card[current_card].name_                = "蝙蝠";
		card[current_card].pfn_function_        = Bat;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_bat;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 2;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "从紫色弃牌区选择一张牌，放置到你的场上。";
		card[current_card].name_                = "白骨";
		card[current_card].pfn_function_        = Bone;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_bone;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 2;
		card[current_card].type_                = CARD_TYPE_ORDINARY;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "从紫色弃牌区选择一张带有 Lv 的牌放置到场上；或者，从任意弃牌区选一张带有纹章的牌加入手牌。";
		card[current_card].name_                = "狼人";
		card[current_card].pfn_function_        = Wolfman;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_wolfman;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 3;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "指定一名对手，向他宣言一张牌的名称，若对手的手牌拥有该牌，将其丢弃；若带有 Lv，你 +1 金币。";
		card[current_card].name_                = "小丑女";
		card[current_card].pfn_function_        = HarleyQuinn;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_harley_quinn;
	}
	for (int i = 1; i <= 2; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 3;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "指定一名对手，向他宣言一张牌的名称，若他的手牌或场上拥有该牌，必须将一张交付到你的手牌。";
		card[current_card].name_                = "女巫";
		card[current_card].pfn_function_        = Witch;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_witch;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 4;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "指定一名金币比你多的对手，向你支付 1 金币。";
		card[current_card].name_                = "哥布林";
		card[current_card].pfn_function_        = Goblin;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_goblin;
	}
	for (int i = 1; i <= 4; i++) {
		current_card++;
		card[current_card].armory_              = CARD_ARMORY_NO_ARMORY;
		card[current_card].color_               = CARD_COLOR_PURPLE;
		card[current_card].level_               = 4;
		card[current_card].type_                = CARD_TYPE_ATTACK;
		card[current_card].number_              = current_card;
		card[current_card].description_         = "指定一名对手场上所有带纹章的卡牌，由他决定交付那些卡牌到你手牌，或向你支付 1 金币。";
		card[current_card].name_                = "牛头人";
		card[current_card].pfn_function_        = Tauren;
		card[current_card].pfn_calc_using_pref_ = calc_using_pref_tauren;
	}
}
