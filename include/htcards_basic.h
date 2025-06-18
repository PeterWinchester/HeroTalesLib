/* htcards_basic.h
   Created - 2025/2/5
 */

#ifndef HTCARDS_BASIC_H
#define HTCARDS_BASIC_H

#include <string>
#include <vector>
#include "htframe.h"
#include "htsys.h"

// 卡牌纹章相关宏定义（可用 | 运算将两种纹章进行组合）
#define CARD_ARMORY_NO_ARMORY   0 // 无纹章
#define CARD_ARMORY_ROYAL       1 // 带[皇]纹章
#define CARD_ARMORY_DAEMON      2 // 带[魔]纹章

// 卡牌类型相关宏定义
#define CARD_TYPE_ORDINARY      0 // 普通牌
#define CARD_TYPE_ATTACK        1 // [攻击]牌
#define CARD_TYPE_CONSISTENT    2 // [持续]牌
#define CARD_TYPE_TRIGGER       3 // [触发]牌

// 卡牌颜色相关宏定义
#define CARD_COLOR_YELLOW       0 // 黄色
#define CARD_COLOR_PURPLE       1 // 紫色

#define CARD_NO_LEVEL          -1 // 无等级（不带有 Lv 的卡牌的 Lv 值）

// 卡牌状态相关宏定义
#define CARD_STATUS_IN_LIBRARY  0 // 在牌库中
#define CARD_STATUS_IN_HAND     1 // 在手上
#define CARD_STATUS_ON_FIELD    2 // 在场上
#define CARD_STATUS_ABANDONED   3 // 在弃牌区

// 卡牌[火]属性相关宏定义
#define CARD_PROPERTY_NO_FIRE   0 // 没有[火]
#define CARD_PROPERTY_FIRE      1 // 有[火]

// 卡牌使用模式相关宏定义
#define CARD_ORDINARY_MODE      0 // 卡牌正常打出
#define CARD_MONK_MODE          1 // 卡牌被僧侣打出
#define CARD_DRAGON_MODE        2 // 卡牌被火龙打出

typedef int (*PfnCardUsingPrefCalc)(int, HTBasicData&, HTBasicFunc&); // 卡牌使用的偏好值计算函数指针类型
typedef bool (*PfnCardFunc)(int, int, int, int, HTBasicData&, HTBasicFunc&); // 卡牌功能函数指针类型

class Card { // 卡牌类
public:
	int level_;               // Lv，即等级
	int armory_;              // 纹章，取值为定义好的宏
	int type_;                // 卡牌类型（[攻击]或[持续]等等）
	int color_;               // 颜色
	int status_;              // 状态（横置、手上、场上）
	int fire_property_;       // 是否有[火]的属性
	int using_preference_;    // 使用偏好（此数值越高，AI 选择打出此牌的倾向越大）
	int number_;              // 卡牌编号，用于标记每一张卡牌

	bool is_transversed_;     // 是否已经横置过

	std::string name_;        // 名称
	std::string description_; // 卡牌功能描述

	PfnCardUsingPrefCalc pfn_calc_using_pref_; // 指向使用偏好值计算函数的指针
	PfnCardFunc          pfn_function_;        // 指向功能函数的指针

	Card();
};

// card[]：牌库的卡牌。在这个数组中，每种卡牌都有相应数量，影响每种卡牌被抽到的概率。
// 牌库的卡牌并不会减少，只是用于存储卡牌基本信息，并确定卡牌被抽到的概率。
extern Card card[kNumYellowCards + kNumPurpleCards + 1];
extern std::vector<Card> cards_abandoned; // 弃牌区的卡牌

// 比较两张卡牌是否相同
bool CompareCards(Card arg_card1, Card arg_card2);

// 显示一张卡牌
void DisplayCard(Card c);

// 显示一张卡牌的说明
void IllustrateCard(Card c);

#endif // HTCARDS_BASIC_H
