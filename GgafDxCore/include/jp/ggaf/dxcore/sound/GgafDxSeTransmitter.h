#ifndef GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#define GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �T�E���h�G�t�F�N�g�o�͎x���N���X .
 * ������ GgafDxSeManager ���p�B
 * �Đ��`�����l���̋@�\�������B
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitter : public GgafCore::GgafObject {

public:
    /** [r]SE�����ڑ��̔z�� */
    GgafDxSeConnection** _papSeConnection;
    /** [r]SE�̐� */
    int _se_num;

public:
    /**
     * �R���X�g���N�^ .
     */
    GgafDxSeTransmitter();

    /**
     * SE�g�p����錾���A���������s�� .
     * �{�I�u�W�F�N�g�̋@�\�𗘗p����ɂ́A�K�{�B
     * @param prm_se_num SE���i��ސ��j
     */
    virtual void declareSeNum(int prm_se_num);

    /**
     * SE�̐ݒ���s�� .
     * �A���ASE�̍Đ����Ԃ� GGAF_END_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �㏑���Đݒ�\�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     * @param prm_se_key SE��`��(�v���p�e�B�t�@�C���̃L�[)
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    virtual void set(int prm_id, const char* prm_se_key, int prm_cannel);

    /**
     * �Đ� .
     * @param prm_id  SE��ID ( 0 �` SE��-1 )
     */
    virtual void play(int prm_id);

    /**
     * �Đ���~ .
     * @param prm_id  SE��ID ( 0 �` SE��-1 )
     */
    virtual void stop(int prm_id);

    virtual void setLooping(int prm_id, bool prm_can_looping);

    /**
     * GgafDxSe ���擾�B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     */
    virtual GgafDxSe* get(int prm_id);

    /**
     * �f�X�g���N�^
     */
    virtual ~GgafDxSeTransmitter();
};

}
#endif /*GGAFDXCORE_GGAFDXSEREFLECTOR_H_*/
