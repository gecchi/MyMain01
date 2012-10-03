#ifndef GGAFQUERY_H_
#define GGAFQUERY_H_

/** GgafQuery�̂P���R�[�h�̌^ */
typedef std::map<std::string, std::string> GgafRecord;
#define GGAFQUERY_SEPA "\t"

namespace GgafCore {

/**
 * SELECT�N�G����͂����I�u�W�F�N�g�������N���X.  <BR>
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
    void sortBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
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
    void sortDescBy(std::string prm_col[], int prm_col_num, int prm_begin_index, int prm_end_index,
                    bool prm_blank_is_max);
public:
    /** �N�G���̗�ԍ��ƒl�̃y�A��������Map��List�ł� */
    std::vector<GgafRecord*> _lstTtable;

    /**
     * ���e����̃N�G�����쐬 .
     */
    GgafQuery();

    /**
     * TSV�Ńt�@�C����ǂݍ���ŁA�N�G�����쐬 .
     * @param prm_file_name
     */
    void importFromFile(std::string prm_file_name);

    /**
     * TSV�Ńt�@�C���ɕۑ� .
     * �w�b�_�[�͂P�s��(index=0)�̃��R�[�h���M�p����܂��B
     * @param prm_file_name �ۑ��t�@�C����
     */
    void exportToFile(std::string prm_file_name);
    size_t getCount();

    bool hasRecord();

    std::string getVal(std::string prm_col, int prm_index);

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

    void sortBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);
    void sortBy(const char*, bool prm_blank_is_max);
    void sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);

    void sortDescBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);

    /**
     * TAB�ŕ��� .
     * �󕶎��v�f�͔�΂���Ȃ��B
     * <pre>
     * �y��z
     * std::vector<std::string> data = split("\taaa\tbbb\t\t\tcccc\tddd\teeee\t\t", "\t");
     * �����ʁ�
     * data[0] = (�󕶎�)
     * data[1] = aaa
     * data[2] = bbb
     * data[3] = (�󕶎�)
     * data[4] = (�󕶎�)
     * data[5] = cccc
     * data[6] = ddd
     * data[7] = eeee
     * data[8] = (�󕶎�)
     * data[9] = (�󕶎�)
     * </pre>
     * @param str
     * @return
     */
    static inline std::vector<std::string> split(std::string str) {
        std::vector<std::string> r;
        int cutAt;
        while ((cutAt = str.find_first_of(GGAFQUERY_SEPA)) != str.npos) {
            r.push_back(str.substr(0, cutAt));
            str = str.substr(cutAt + 1);
        }
        r.push_back(str);
        return r;
    }

    void dump();
    virtual ~GgafQuery();
};

}
#endif /*GGAFQUERY_H_*/
