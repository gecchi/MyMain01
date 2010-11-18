#ifndef GGAFPROGRESS_H_
#define GGAFPROGRESS_H_
namespace GgafCore {


/**
 * �i���Ǘ��N���X .
 * @version 1.00
 * @since 2010/11/18
 * @author Masatoshi Tsuge
 */
class GgafProgress : public GgafObject {

public:

    /** [r]���ݐi��ID(1�`99) */
    int _progress;
    /** [r]�P�t���[���O�i��ID(1�`99) */
    int _progress_prev;
    /** [r]���t���[�����Z���ɔ��f�\��̐i��ID(1�`99) */
    int _progress_nextframe;
    /** [r]�i��ID�C�x���g���t���[���X�g�b�N */
    frame* _paFrame_ProgressChange;
    frame* _pFrame_behaving;

    /**
     * �R���X�g���N�^ .
     */
    GgafProgress(frame* prm_pFrame_behaving, int prm_num);


    /**
     * ���݂̐i��ID�擾 .
     * @return �i��ID(1�`99)
     */
    virtual int get();

    /**
     * �i��ID���N���������̃t���[���擾 .
     * @param prm_progress �i��ID(1�`99)
     * @return �����̒��߂̐i��ID���N�������Ƃ��̃t���[��
     */
    virtual frame getFrameAtChanged(int prm_progress);

    virtual frame getActivePartFrameIn();

    /**
     * �i��ID��ݒ� .
     * �A���A����t���[�����ł͔��f���ꂸ�AnextFrame() ���ɔ��f�����B
     * @param prm_progress �i��ID(1�`99)
     */
    virtual void change(int prm_progress);

    /**
     * �i��ID��+1���� .
     * 1�`99 �͈̔͂ƂȂ�悤�ɒ��ӂ��邱�ƁB
     * �A���A����t���[�����ł͔��f���ꂸ�AnextFrame() ���ɔ��f�����B
     */

    virtual void changeNext();

    /**
     * �����̐i��ID�ɐ؂�ւ�������ǂ������ׂ�B.
     * �؂�ւ���� nextFrame() ����1�t���[������true�ɂȂ�܂��B
     * @param prm_progress �؂�ւ�������ǂ������ׂ����i��ID
     * @return true:�����̐i��ID�ɐ؂�ւ�����^false:����ȊO
     */
    virtual bool onActive(int prm_progress);

    virtual bool onInactive(int prm_progress);

    /**
     * �i��ID���ω��������i�O��Ɠ������ǂ����j���ׂ� .
     * @return 0 ���� �i��ID
     *         0    �F�ω����Ă��Ȃ�
     *         0�ȊO�F�ω����L��ŁA���̐V�����i��ID
     */
    virtual int getOnActive();

    virtual int getOnInactive();


    virtual void update();

    virtual ~GgafProgress();
};

}
#endif /*GGAFCURTAIN_H_*/
