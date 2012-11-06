#ifndef QUERYRANKING_H_
#define QUERYRANKING_H_
namespace VioletVreath {

#define QUERYRANKING_NAME_LEN 10
#define QUERYRANKING_SCORE_LEN 10
#define QUERYRANKING_RECORD_NUM 10
#define QUERYRANKING_DATA_FILE "SCORE_RANKING.qry"

/**
 * �n�C�X�R�A�����L���O�p�N�G�� .
 * @version 1.00
 * @since 2012/10/15
 * @author Masatoshi Tsuge
 */
class QueryRanking : public GgafCore::GgafQuery {

public:
    QueryRanking();
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

    virtual ~QueryRanking();
};

}
#endif /*QUERYRANKING_H_*/
