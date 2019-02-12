#ifndef GGAF_CORE_TABLE_H_
#define GGAF_CORE_TABLE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>
#include <vector>
#include <map>

/** Table�t�@�C���̃Z�p���[�^ */
#define GGAFTABLE_SEPA "\t"

namespace GgafCore {

/** Table�̂P���R�[�h�̌^ */
typedef std::map<std::string, std::string> Record;

/**
 * DB�̃N�G�����ʂ̂悤�ȃI�u�W�F�N�g�������N���X.
 * �����f�[�^��S�� std::string �ŕێ����Ă���B
 * @version 1.00
 * @since 2012/10/02
 * @author Masatoshi Tsuge
 */
class Table : public Object {

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

    /** �N�G���̗�ԍ��ƒl�̃y�A��������Map��List�ł� */
    std::vector<Record*> _lstTtable;

public:
    /**
     * ���e����̃N�G�����쐬 .
     */
    Table();

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

    /**
     * ���R�[�h������Ԃ� .
     * @return ���R�[�h����
     */
    size_t getCount() const;

    bool hasRecord() const ;

    /**
     * �f�[�^���擾 .
     * @param prm_col   ��
     * @param prm_index ���R�[�hindex(0�`)
     * @return �f�[�^�l
     */
    std::string getVal(std::string& prm_col, int prm_index);

    /**
     * �f�[�^���擾 .
     * @param prm_col   ��
     * @param prm_index ���R�[�hindex(0�`)
     * @return �f�[�^�l
     */
    std::string getVal(const char* prm_col, int prm_index);

    /**
     * �f�[�^���㏑���ݒ肵�܂� .
     * @param prm_col    ��
     * @param prm_index  ���R�[�hindex(0�`)
     * @param prm_val    �㏑������ݒ�l
     */
    void setVal(std::string& prm_col, int prm_index, std::string& prm_val);
    /**
     * �f�[�^���㏑���ݒ肵�܂� .
     * @param prm_col    ��
     * @param prm_index  ���R�[�hindex(0�`)
     * @param prm_val    �㏑������ݒ�l
     */
    void setVal(const char* prm_col, int prm_index, std::string& prm_val);
    /**
     * �f�[�^���㏑���ݒ肵�܂� .
     * @param prm_col    ��
     * @param prm_index  ���R�[�hindex(0�`)
     * @param prm_val    �㏑������ݒ�l
     */
    void setVal(std::string& prm_col, int prm_index, const char* prm_val);
    /**
     * �f�[�^���㏑���ݒ肵�܂� .
     * @param prm_col    ��
     * @param prm_index  ���R�[�hindex(0�`)
     * @param prm_val    �㏑������ݒ�l
     */
    void setVal(const char* prm_col, int prm_index, const char* prm_val);

    /**
     * ���R�[�h���擾���܂��B .
     * @param prm_index ���R�[�hindex(0�`)
     * @return
     */
    Record* getRecord(int prm_index);

    /**
     * ���R�[�h���폜���܂��B .
     * @param prm_index ���R�[�hindex(0�`)
     */
    void removeRow(int prm_index);

    /**
     * �w��index�ȍ~�̃��R�[�h���폜���܂��B .
     * @param prm_start_index ���R�[�hindex(0�`)
     */
    void removeRows(int prm_start_index);

    /**
     * �w��͈�index�̃��R�[�h���폜���܂��B .
     * @param prm_start_index �폜�J�nindex(0 �`)
     * @param prm_end_index   �폜�I��index(0 �` getCount()-1)
     */
    void removeRows(int prm_start_index, int prm_end_index);

    /**
     * ���R�[�h�𖖔��s�ɒǉ����܂� .
     * Record �I�u�W�F�N�g�̃|�C���^��n���ĉ������B<BR>
     * �{�N�G���I�u�W�F�N�g�J�����ɁA�SRecord�̉�����s����d�l�ł��B
     * �Ăь��� Record �I�u�W�F�N�g�� delete �͕s�v�B(�ނ���A�o���܂���B�s��Ȃ��ŉ�����)
     * @param prm_pRow �q�[�v�ɍ쐬�������R�[�h�I�u�W�F�N�g�i�̃|�C���^�j
     */
    void addRow(Record* prm_pRow);

    /**
     * ���R�[�h�𖖔��s�ɋ󃌃R�[�h��ǉ����܂�
     */
    void addNewRow();

    /**
     * A��B�̃��R�[�h�̏ꏊ(INDEX)�����ւ��܂�. <BR>
     * @param prm_index_A ����ւ��Ώۃ��R�[�hINDEX A
     * @param prm_index_B ����ւ��Ώۃ��R�[�hINDEX B
     */
    void swapIndex(int prm_index_A, int prm_index_B);

    /**
     * �����̗�ŏ����\�[�g���܂� .
     * @param prm_col ��
     * @param prm_blank_is_max �󕶎�("")���\�[�g���̍ő�Ƃ��邩�ۂ��B
     */
    void sortBy(const char* prm_col, bool prm_blank_is_max);
    /**
     * �����̗�ŏ����\�[�g���܂� .
     * @param prm_col1  ��P�\�[�g��
     * @param prm_col2  ��Q�\�[�g��
     * @param prm_blank_is_max �󕶎�("")���\�[�g���̍ő�Ƃ��邩�ۂ��B
     */
    void sortBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);
    void sortBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);

    void sortDescBy(const char* prm_col, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, bool prm_blank_is_max);
    void sortDescBy(const char* prm_col1, const char* prm_col2, const char* prm_col3, bool prm_blank_is_max);
    void sortDescBy(std::string prm_col[], int prm_col_num, bool prm_blank_is_max);

    /**
     * �󕶎����l������TAB�����ŕ��� .
     * <pre>
     * �y��z
     * std::vector<std::string> data = split("\taaa\tbbb\t\t\tcccc\tddd\teeee\t\t", "\t");
     * �����ʁ�
     * data[0] = (�󕶎�)
     * data[1] = "aaa"
     * data[2] = "bbb"
     * data[3] = (�󕶎�)
     * data[4] = (�󕶎�)
     * data[5] = "cccc"
     * data[6] = "ddd"
     * data[7] = "eeee"
     * data[8] = (�󕶎�)
     * data[9] = (�󕶎�)
     * </pre>
     * @param str
     * @return ������̃x�N�^���X�g
     */
    static inline std::vector<std::string> split(std::string str) {
        std::vector<std::string> r;
        size_t cutAt;
        while ((cutAt = str.find_first_of(GGAFTABLE_SEPA)) != str.npos) {
            r.push_back(str.substr(0, cutAt));
            str = str.substr(cutAt + 1);
        }
        r.push_back(str);
        return r;
    }

    void dump();
    virtual ~Table();
};

}
#endif /*GGAF_CORE_TABLE_H_*/
