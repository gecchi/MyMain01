#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/util/RankingTable.h"

/** ���݂̃����N�l (G_MIN_RANK �` G_MAX_RANK) */
#define G_RANK (VioletVreath::GameGlobal::rank_)
#define G_MIN_RANK (VioletVreath::GameGlobal::min_rank_)
#define G_MAX_RANK (VioletVreath::GameGlobal::max_rank_)
/** �����N���\���p�����N���[�g */
#define G_RANK_R (1000.0)
/** ��ʕ\���p�����N�l */
#define G_RANK_DISP ((int)(G_RANK*G_RANK_R))

/** �����N�A�b�v���x���l�BStageWorld::processBehavior()��G_RANK�ɒǏ] */
#define G_RANKUP_LEVEL (VioletVreath::GameGlobal::rank_up_level_)
/** �X�R�A */
#define G_SCORE (VioletVreath::GameGlobal::score_)
/** �X�R�A */
#define G_ZANKI (VioletVreath::GameGlobal::zanki_)
/** �����L���O�X�R�A */
#define G_RANKING_TABLE (VioletVreath::GameGlobal::tblRanking_)


#define G_MAX_RANKUP_LEVEL (1230)

/**
 * �����N�p�֐�(�����������) .
 * �����̃����N�l(RANK_VAL)���A
 * G_RANK���A0.0 �` 1.0 �ɐ��ڂ���ɔ����� RANK_0_VAL�`RANK_1_VAL �ɐ��ڂ���l���擾�B
 * �����N�l(RANK_VAL)�� 0.0 ��������Ă����������B
 * �����N�l(RANK_VAL)�� 1.0 �������Ă����������B
 */
#define RF(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( RCNV_0_1_to( (RANK_VAL), (RANK_0_VAL), (RANK_1_VAL) ) )

/**
 * �����N�p�֐�(��������L��) .
 * �����̃����N�l(RANK_VAL)���AG_RANK���A0.0 �` 1.0 �ɐ��ڂ���ɔ����� RANK_0_VAL�`RANK_1_VAL �ɐ��ڂ���l���擾�B
 * �����N�l(RANK_VAL)�� 0.0 �������ꍇ�́ARANK_0_VAL�ɌŒ�B
 * �����N�l(RANK_VAL)�� 1.0 ������ꍇ�́ARANK_1_VAL�ɌŒ�B
 */
#define RF_ULL(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( ((RANK_VAL) < 0) ? (RANK_0_VAL) : ( ((RANK_VAL) > 1) ? (RANK_1_VAL) : (RCNV_0_1_to((RANK_VAL),(RANK_0_VAL),(RANK_1_VAL))) ) )

/**
 * �����N�p�֐�(�����̂ݗL��) .
 * �����̃����N�l(RANK_VAL)���AG_RANK���A0.0 �` 1.0 �ɐ��ڂ���ɔ����� RANK_0_VAL�`RANK_1_VAL �ɐ��ڂ���l���擾�B
 * �����N�l(RANK_VAL)�� 0.0 �������ꍇ�́ARANK_0_VAL�ɌŒ�B
 * �����N�l(RANK_VAL)�� 1.0 �������Ă����������B
 */
#define RF_LL(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( ((RANK_VAL) < 0) ? (RANK_0_VAL) : (RCNV_0_1_to((RANK_VAL),(RANK_0_VAL),(RANK_1_VAL))) )

/**
 * �����N�p�֐�(����̂ݗL��) .
 * �����̃����N�l(RANK_VAL)���AG_RANK���A0.0 �` 1.0 �ɐ��ڂ���ɔ����� RANK_0_VAL�`RANK_1_VAL �ɐ��ڂ���l���擾�B
 * �����N�l(RANK_VAL)�� 0.0 ��������Ă����������B
 * �����N�l(RANK_VAL)�� 1.0 ������ꍇ�́ARANK_1_VAL�ɌŒ�B
 */
#define RF_UL(RANK_VAL, RANK_0_VAL, RANK_1_VAL)  ( ((RANK_VAL) > 1) ? (RANK_1_VAL) : (RCNV_0_1_to((RANK_VAL),(RANK_0_VAL),(RANK_1_VAL))) )


namespace VioletVreath {

class GameGlobal {
public:
    static bool is_init_;
    /** ���X�R�A */
    static int score_;
    /** �������N�l�i�f�t�H���g�́A0.0 �` 1.0�B 1.0��MAX�����N�Ƃ���) */
    static double rank_;
    /** �����N�����l */
    static double min_rank_;
    /** �����N����l */
    static double max_rank_;
    /** ���c�@ */
    static int zanki_;
    /** �������N���x���l */
    static int rank_up_level_;
    /** �����L���O�e�[�u�� */
    static RankingTable tblRanking_;
    /** �f�� */
    static int prime_n_[];

    /**
     * G_RANK���Q�Ƃ��AG_RANKUP_LEVEL�����Z���܂��B
     * @return true:G_RANKUP_LEVEL�����Z���� /false:G_RANKUP_LEVEL�͕ω��Ȃ�
     */
    static bool updateRankUpLebel();
};

}
#endif /*GAMEGLOBAL_H_*/

