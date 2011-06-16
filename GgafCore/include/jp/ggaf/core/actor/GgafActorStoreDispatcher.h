#ifndef GGAFACTORSTOREDISPATCHER_H_
#define GGAFACTORSTOREDISPATCHER_H_
namespace GgafCore {

/**
 * �A�N�^�[�f�B�X�p�b�`���[�̃f�B�X�p�b�`���[�N���X .
 * GgafActorStore �́A�T�u�̓o�^�A�N�^�[(GgafActor)���ɂ����ȃ����o�[�� dispatch() ����̂ɑ΂��A
 * GgafActorStoreDispatcher �́A�T�u�̓o�^�f�B�X�p�b�`���[(GgafActorStore) �� �o�^�A�N�^�[(GgafActor)���A
 * �S���ɂ��Ă���f�B�X�p�b�`���[��D��I��dispatch() ����B
 * @version 1.00
 * @since 2011/06/15
 * @author Masatoshi Tsuge
 */
class GgafActorStoreDispatcher : public GgafActorStore {

private :


public:
    GgafActorStoreDispatcher(const char* prm_name);

    /**
     * �f�B�X�p�b�`���[��o�^���܂�.
     * GgafActorStore::addSubLast() ���Ăяo�O�Ƀ`�F�b�N���s���܂��B
     * ���̂��߁A�o�^�A�N�^�[�ς݃f�B�X�p�b�`���[��o�^���ĉ������B
     * @param prm_pSub �o�^�f�B�X�p�b�`���[
     */
    virtual void addSubLast(GgafActor* prm_pSub) override;

    /**
     * �T�u�̓o�^�f�B�X�p�b�`���[�̏�ԍX�V .
     * �񊈓��ɂł���T�u�f�B�X�p�b�`���[������Δ񊈓��ɂ���B
     * �񊈓��ɂł�������́A�T�u�f�B�X�p�b�`���[�̓o�^�����o�[�S�Ă��񊈓��ł��邱�ƁB
     */
    virtual void processFinal() override;

    virtual ~GgafActorStoreDispatcher() {
    }
};

}
#endif /*GGAFACTORSTOREDISPATCHER_H_*/
