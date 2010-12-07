#ifndef GGAFREPEATSEQ_H_
#define GGAFREPEATSEQ_H_
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
    static std::_MAP_<std::string, int> mapNowval;
    static std::_MAP_<std::string, int> mapMaxval;
    static std::_MAP_<std::string, int> mapMinval;

    /**
     * �����I�u�W�F�N�g���쐬 .
     * @param ID �R���鏇���I�u�W�F�N�gID�i�C��)
     * @param min �ŏ��l
     * @param max �ő�l
     */
    static void create(std::string ID, int min, int max);

    /**
     * ID�̏����I�u�W�F�N�g���쐬�ς݂����ׂ� .
     * @param ID �����I�u�W�F�N�gID
     * @return true:�����ς݁^false:������
     */
    static bool isExist(std::string ID);

    /**
     * �����I�u�W�F�N�g���玟�̒l���̔Ԃ��� .
     * @param ID �쐬���̏����I�u�W�F�N�gID
     * @return �O��l�́{�P���ꂽ�l�B
     *         �A���A��������͍ŏ��l��Ԃ��B
     *         �܂��A�ő�l�̎����̔Ԃ���ƍŏ��l��Ԃ��i�߂�j�B
     */
    static int nextVal(std::string ID);
};

}
#endif /*GGAFREPEATSEQ_H_*/
