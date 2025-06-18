/* fighter.cpp
   Created - 2025/2/9
*/

#include "cards/fighter.h"

bool Fighter(
	int          arg_player,      // ���Ƶ�ʹ����
	int          arg_card,        // ���Ʊ�ţ������С����ϻ��������еı�ţ�
	int          arg_status,      // ����״̬�������С����ϻ���������
	int          arg_mode,        // ����ʹ��ģʽ������������Ǳ�ɮ�»���������
	HTBasicData& arg_global_data, // ȫ�����ݣ�������Ϸ״̬
	HTBasicFunc& arg_basic_func   // ������������
	) {
	if (arg_status != CARD_STATUS_IN_HAND) return false;

	// �������������Ϊɮ��ģʽ��������������С�� 1��������ɮ��ģʽ��������������С�� 2
	if (player[arg_player].num_cards_in_hand_ < 2 - (arg_mode == CARD_MONK_MODE)) {
		if (arg_player == 1) {
			printf("������Ʋ��㣡\n");
			Pause();
		}
		return false;
	}

	player[arg_player].num_action_points_--;

	if (arg_player != 1) {
		printf("��� %d ����� ", arg_player);

		if (arg_mode == CARD_ORDINARY_MODE) DisplayCard(player[arg_player].cards_in_hand_[arg_card]);
		else DisplayCard(cards_abandoned[arg_card]);

		printf("��\n");

		if (arg_mode == CARD_ORDINARY_MODE) {
			IllustrateCard(player[arg_player].cards_in_hand_[arg_card]);
		} else IllustrateCard(cards_abandoned[arg_card]);
		
		Pause();
	}

	// �������ɮ��ģʽ���趪�����ϵĸ񶷼�
	if (arg_mode == CARD_ORDINARY_MODE) {
		AbandonCard(arg_player, arg_card, arg_status, arg_global_data);
		arg_basic_func.pfn_gaming_interface_(arg_global_data);
		CheckNun(arg_player, arg_global_data);
	}

	// ��ȫ�����Ʒŵ����ϣ���ͳ�� Lv �ܺͣ�û�� Lv �Ŀ��ư� Lv.0 ���㣩���������
	int sum_level = 0;
	bool found_armory = false;
	while (player[arg_player].num_cards_in_hand_) {
		if (player[arg_player].cards_in_hand_[0].level_ != CARD_NO_LEVEL) {
			sum_level += player[1].cards_in_hand_[0].level_;
		}
		if (player[arg_player].cards_in_hand_[0].armory_ != CARD_ARMORY_NO_ARMORY) {
			found_armory = true;
		}
		PutOnField(arg_player, 0, CARD_ORDINARY_MODE, arg_global_data);
	}

	// ����
	if (sum_level % 2 == 0 && !found_armory) { // Lv ֮��Ϊż���Ҳ��������£���Ǯ
		// ��Ǯ
		player[arg_player].num_coins_++;
		arg_basic_func.pfn_gaming_interface_(arg_global_data);

		if (arg_player == 1) printf("��");
		else printf("��� %d ", arg_player);
		
		printf("�����ڳ��ϵ����� Lv ֮��Ϊż���Ҳ��������£�+1 ��ң�\n");
		Pause();

		// �жϻ�ʤ
		if (player[arg_player].num_coins_ == arg_global_data.win_coin_number_) {
			arg_global_data.win_player_ = arg_player;
			arg_global_data.game_status_ = 0;
			return true;
		}

		CheckMimic(arg_player, MIMIC_TRIGGER_GET_COIN, arg_global_data, arg_basic_func);
		CheckDancer(arg_player, arg_global_data, arg_basic_func);
	}
	return true;
}

int calc_using_pref_fighter(
	int          arg_player,
	HTBasicData& arg_global_data,
	HTBasicFunc& arg_basic_func
	) {
	int preference = 0;

	// ������ƣ�����������Ƶ� Lv ֮��Ϊż���Ҳ��������£���ƫ��ֵ�� 2
	bool found_armory = false;
	int sum_level = 0;
	for (int i = 0; i < player[arg_player].num_cards_in_hand_; i++) {
		if (player[arg_player].cards_in_hand_[i].armory_ != CARD_ARMORY_NO_ARMORY) {
			found_armory = true;
			break;
		}
		sum_level += player[arg_player].cards_in_hand_[i].level_;
	}
	if (!found_armory && sum_level % 2 == 0) preference += 2;
	
	return preference;
}
