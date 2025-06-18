/* htgame.h
   Created - 2025/2/6
*/

#ifndef HTGAME_H
#define HTGAME_H

#include "htsys.h"
#include "htframe.h"
#include "htplayer.h"
#include "htcards_basic.h"
#include "cards/guard.h"
#include "cards/holy_knight.h"

// 显示游戏中界面，包括各玩家的手牌、场牌和金币数
// 此函数是默认版本，可自定义另一个函数以替代，实际调用时使用函数指针
void DefaultGamingInterface(HTBasicData& arg_global_data);

// 将指定玩家场上的一张指定卡牌收回到该玩家手中
void ReturnCardOnField(int arg_player, int arg_card);

// 将一张牌放在指定玩家场上，这张牌可以来自手牌，也可以来自弃牌区（此时指定卡牌被僧侣或火龙打出）
// arg_player 是指定玩家编号。当指定卡牌来自手牌时，arg_card 是该卡牌在指定玩家手中的编号；当指定卡
// 牌来自弃牌区时，arg_card 是该卡牌在弃牌区的编号。arg_mode 是卡牌使用模式（一般模式、被僧侣打出、
// 被火龙打出）
void PutOnField(int arg_player, int arg_card, int arg_mode, HTBasicData& arg_global_data);

// 丢弃指定卡牌，该卡牌可以来自手牌或场上
// 当 arg_status 为 CARD_STATUS_IN_HAND 时，指定卡牌来自手牌
// 当 arg_status 为 CARD_STATUS_ON_FIELD 时，指定卡牌来自场上
void AbandonCard(int arg_player, int arg_card, int arg_card_status, HTBasicData& arg_global_data);

// 指定玩家从牌库摸一张牌
void GetOneCardFromLib(int arg_player);

// 将弃牌区的指定一张牌加入指定玩家手牌，arg_card 为指定卡牌在弃牌区的编号
void AddAbandonedCardToHand(int arg_player, int arg_card, HTBasicData& arg_global_data);

// 使用防牌
// 参数解释：
// arg_attacker 攻击者玩家编号
// arg_target   目标玩家编号
// arg_card     攻击卡牌编号（如果在手上则为手牌中的编号，如果在弃牌区则为弃牌中的编号）
// arg_mode     攻击卡牌模式（主动打出还是被僧侣或火龙打出）
bool Defend(
   int          arg_attacker,
   int          arg_target,
   int          arg_card,
   int          arg_mode,
   HTBasicData& arg_global_data,
   HTBasicFunc& arg_basic_func
);

#endif // HTGAME_H
