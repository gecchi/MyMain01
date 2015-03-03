#ifndef GAMEGLOBAL_H_
#define GAMEGLOBAL_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/util/RankingTable.h"

#define G_MIN_RANK (0.0)
#define G_MAX_RANK (1.0)
/** �����N (0.0 �` 1.0) */
#define G_RANK (VioletVreath::GameGlobal::rank_)
/** �����N���\���p�����N���[�g */
#define G_RANK_R (1000.0)
/** �\���p�����N�l */
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
 * G_MIN_RANK �` G_MAX_RANK �ɐ��ڂ���ɔ����� MIN_VAL�`MAX_VAL �ɐ��ڂ���l���擾�B
 */
#define RF(RANK_VAL, MIN_VAL, MAX_VAL)  ( RCNV( (G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL) ) )

/**
 * �����N�p�֐�(��������L��) .
 * �����̃����N�l(RANK_VAL)���AG_MIN_RANK �` G_MAX_RANK �ɐ��ڂ���ɔ����� MIN_VAL�`MAX_VAL �ɐ��ڂ���l���擾�B
 * �A���A��`��(RANK_VAL)�FG_MIN_RANK <= RANK_VAL <= G_MIN_RANK  �ɑ΂��āA
 *         �l��(N)       �F   MIN_VAL <=    N     <= MAX_VAL     ��Ԃ��B
 * �����N�l(RANK_VAL)��G_MIN_RANK�������ꍇ�́AMIN_VAL�ɌŒ�B
 * �����N�l(RANK_VAL)��G_MAX_RANK������ꍇ�́AMAX_VAL�ɌŒ�B
 */
#define RF_ULL(RANK_VAL, MIN_VAL, MAX_VAL)  ( ((RANK_VAL) < (G_MIN_RANK)) ? (MIN_VAL) : ( ((RANK_VAL) > (G_MAX_RANK)) ? (MAX_VAL) : (RCNV((G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL))) ) )

/**
 * �����N�p�֐�(�����̂ݗL��) .
 * �����̃����N�l(RANK_VAL)���AG_MIN_RANK �` G_MAX_RANK �ɐ��ڂ���ɔ����� MIN_VAL�`MAX_VAL �ɐ��ڂ���l���擾�B
 * �A���A��`��(RANK_VAL)�FG_MIN_RANK <= RANK_VAL  �ɑ΂��āA
 *         �l��(N)       �F   MIN_VAL <=    N      ��Ԃ��B
 * �����N�l(RANK_VAL)��G_MIN_RANK�������ꍇ�́AMIN_VAL�ɌŒ�B
 */
#define RF_LL(RANK_VAL, MIN_VAL, MAX_VAL)  ( ((RANK_VAL) < (G_MIN_RANK)) ? (MIN_VAL) : (RCNV((G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL))) )

/**
 * �����N�p�֐�(����̂ݗL��) .
 * �����̃����N�l(RANK_VAL)���AG_MIN_RANK �` G_MAX_RANK �ɐ��ڂ���ɔ����� MIN_VAL�`MAX_VAL �ɐ��ڂ���l���擾�B
 * �A���A��`��(RANK_VAL)�FRANK_VAL <= G_MIN_RANK  �ɑ΂��āA
 *         �l��(N)       �F   N     <= MAX_VAL     ��Ԃ��B
 * �����N�l(RANK_VAL)��G_MAX_RANK������ꍇ�́AMAX_VAL�ɌŒ�B
 */
#define RF_UL(RANK_VAL, MIN_VAL, MAX_VAL)  ( ((RANK_VAL) > (G_MAX_RANK)) ? (MAX_VAL) : (RCNV((G_MIN_RANK), (G_MAX_RANK), (RANK_VAL), (MIN_VAL), (MAX_VAL))) )


namespace VioletVreath {

class GameGlobal {
public:
    static bool is_init_;
    /** ���X�R�A */
    static int score_;
    /** �������N�l�i0.0 �` 1.0�B 1.0��MAX�����N�Ƃ���) */
    static double rank_;
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

