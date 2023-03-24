#ifndef RANKINGTABLE_H_
#define RANKINGTABLE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/util/Table.h"

namespace VioletVreath {

#define RANKINGTABLE_NAME_LEN 10
#define RANKINGTABLE_SCORELEN 10
#define RANKINGTABLE_RECORD_NUM 10
#define RANKINGTABLE_DATA_FILE "SCORE_RANKING.tbl"

/**
 * �n�C�X�R�A�����L���O�p�N�G�� .
 * @version 1.00
 * @since 2012/10/15
 * @author Masatoshi Tsuge
 */
class RankingTable : public GgafCore::Table {

public:
    RankingTable();
    /**
     * ������ .
     * �f�[�^�t�@�C��������ꍇ�͓ǂݍ��݁B
     * �f�[�^�t�@�C�����Ȃ��ꍇ�̓f�t�H���g�̃����L���O�N�G���̓����쐬�B
     */
    void init();

    /**
     * �����L���O�N�G���̖����Ƀf�[�^�ǉ����� .
     * @param prm_name �X�R�A�l�[��
     * @param prm_score �X�R�A
     */
    void addRow(std::string& prm_name, int prm_score);

    /**
     * �����L���O�N�G���̃\�[�g���s�� .
     */
    void sort();

    /**
     * �����L���O�̃X�R�A�𒲂ׂāA�����N�E�C�����邩�ǂ������ׂ� �B
     * @param prm_score �X�R�A
     * @return true:�����N�E�C��/false:�����N�O
     */
    bool isRankIn(int prm_score);

    /**
     * �����L���O�N�G�����f�[�^�t�@�C���ɕۑ�����B
     */
    void save();

    virtual ~RankingTable();
};

}
#endif /*RANKINGTABLE_H_*/
