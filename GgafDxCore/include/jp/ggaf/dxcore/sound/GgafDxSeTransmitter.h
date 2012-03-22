#ifndef GGAFDXSEREFLECTOR_H_
#define GGAFDXSEREFLECTOR_H_
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

private:

public:
    /** [r]SE�����ڑ��̔z�� */
    GgafDxSeConnection** _papSeCon;
    /** [r]SE�̐� */
    int _se_num;

    /**
     * �R���X�g���N�^ .
     */
    GgafDxSeTransmitter();

    /**
     * SE�g�p����錾���A���������s�� .
     * �{�I�u�W�F�N�g�̋@�\�𗘗p����ɂ́A�K�{�B
     * @param prm_se_num SE���i��ސ��j
     */
    virtual void useSe(int prm_se_num);

    /**
     * SE�̐ݒ���s�� .
     * �A���ASE�̍Đ����Ԃ� GGAF_SAYONARA_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * @param prm_id SE��ID ( 0 �` SE��-1 )
     * @param prm_se_name SE��`�� prm_se_name+".wave"
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    virtual void set(int prm_id, const char* prm_se_name, int prm_cannel = 1);

    /**
     * �Đ� .
     * @param prm_id  SE��ID ( 0 �` SE��-1 )
     */
    virtual void play(int prm_id);

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
#endif /*GGAFDXSEREFLECTOR_H_*/
