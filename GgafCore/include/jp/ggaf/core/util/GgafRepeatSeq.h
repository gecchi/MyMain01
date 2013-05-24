#ifndef GGAFREPEATSEQ_H_
#define GGAFREPEATSEQ_H_
#include <map>
#include <string>

namespace GgafCore {

/**
 * �����N���X .
 * �f�[�^�x�[�X�̃V�[�N�G���X�i�����I�u�W�F�N�g�j�̂悤�ɁA�̔Ԃ��܂��B
 * @version 1.00
 * @since 2007/12/11
 * @author Masatoshi Tsuge
 */
class GgafRepeatSeq {
public:
    static std::map<std::string, int> mapNowval;
    static std::map<std::string, int> mapMaxval;
    static std::map<std::string, int> mapMinval;

public:
    /**
     * �����I�u�W�F�N�g���쐬 .
     * @param ID �R���鏇���I�u�W�F�N�gID�i�C��)
     * @param min �ŏ��l
     * @param max �ő�l
     */
    static void create(std::string ID, int min, int max);

    static void set(std::string& ID, int val);
    static void set(const char* ID, int val);
    static void setMax(std::string& ID);
    static void setMax(const char* ID);
    static void setMin(std::string& ID);
    static void setMin(const char* ID);
    /**
     * ID�̏����I�u�W�F�N�g���쐬�ς݂����ׂ� .
     * @param ID �����I�u�W�F�N�gID
     * @return true:�����ς݁^false:������
     */
    static bool isExist(std::string& ID);
    static bool isExist(const char* ID);
    /**
     * �����I�u�W�F�N�g���玟�̒l���̔Ԃ��� .
     * @param ID �쐬���̏����I�u�W�F�N�gID
     * @return �O��l�́{�P���ꂽ�l�B
     *         �A���A��������͍ŏ��l��Ԃ��B
     *         �܂��A�ő�l�̎����̔Ԃ���ƍŏ��l��Ԃ��i�߂�j�B
     */
    static int nextVal(std::string& ID);
    static int nextVal(const char* ID);
};

}
#endif /*GGAFREPEATSEQ_H_*/
