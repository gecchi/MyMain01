#ifndef GGAFQUERY_H_
#define GGAFQUERY_H_

/** GgafQuery�̂P���R�[�h�̌^ */
typedef std::map<const char*, std::string> GgafRecord;

namespace GgafCore {

/**
 * SQL��SELECT�̌��ʁi�N�G���j���i�[���A�I�u�W�F�N�g�Ƃ��Ĉ������Ƃ�ړI�Ƃ����N���X.  <BR>
 * @version 1.00
 * @since 2012/10/02
 * @author Masatoshi Tsuge
 */
class GgafQuery : public GgafCore::GgafObject {

private:
    /**
     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h�������\�[�g�����וς��܂�. <BR>
     * �N�C�b�N�\�[�g�g�p�B<BR>
     * @param prm_col �����\�[�g���鏇�Ԃ̗񖼔z��
     * @param prm_col_num �񖼔z��v�f��
     * @param prm_begin_index �J�nINDEX
     * @param prm_end_index �I��INDEX
     * @param prm_blank_is_max true:�󕶎�("")���ő�l�Ƃ��܂��^false:�󕶎�("")���ŏ��l�Ƃ��܂��B
     */
    void sortBy(const char* prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                bool prm_blank_is_max);

    /**
     * �����̗�̔z�񏇂̗v�f�l�ŁA�������R�[�h���~���\�[�g�����וς��܂�. <BR>
     * �N�C�b�N�\�[�g�g�p�B<BR>
     * @param prm_col �~���\�[�g���鏇�Ԃ̗񖼔z��
     * @param prm_col_num �񖼔z��v�f��
     * @param prm_begin_index �J�nINDEX
     * @param prm_end_index �I��INDEX
     * @param prm_blank_is_max true:�󕶎�("")���ő�l�Ƃ��܂��^false:�󕶎�("")���ŏ��l�Ƃ��܂��B
     */
    void sortDescBy(const char* prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                    bool prm_blank_is_max);
public:
    /** �N�G���̗�ԍ��ƒl�̃y�A��������Map��List�ł� */
    std::vector<GgafRecord*> _lstTtable;

    GgafQuery();

    size_t getCount();

    bool hasRecord();

    std::string get(const char* prm_col, int prm_index);

    GgafRecord* getRecord(int prm_index);
    /**
     * ���R�[�h���폜���܂��B .
     * @param prm_index ���R�[�hindex�i0�`)
     * @throws GwafInternalException �����̃��R�[�hindex���͈͊O
     */
    void removeRow(int prm_index);
    void removeRows(int prm_start_index, int prm_end_index);

    void addRow(GgafRecord* prm_pRow);
    /**
     * A��B�̃��R�[�h�̏ꏊ(INDEX)�����ւ��܂�. <BR>
     * @param prm_index_A ����ւ��Ώۃ��R�[�hINDEX A
     * @param prm_index_B ����ւ��Ώۃ��R�[�hINDEX B
     */
    void swapIndex(int prm_index_A, int prm_index_B);



    void sortBy(const char* prm_col[], int prm_col_num, bool prm_blank_is_max);

    void sortBy(const char* prm_col, bool prm_blank_is_max = false);

    void sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max = false);

    void sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max = false);


    void sortDescBy(const char* prm_col[], int prm_col_num, bool prm_blank_is_max);

    void sortDescBy(const char* prm_col, bool prm_blank_is_max = false);
    void sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max = false);
    void sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max = false);

    void dump();
    virtual ~GgafQuery();
};

}
#endif /*GGAFQUERY_H_*/
