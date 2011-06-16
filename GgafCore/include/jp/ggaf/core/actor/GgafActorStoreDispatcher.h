#ifndef GGAFACTORSTOREDISPATCHER_H_
#define GGAFACTORSTOREDISPATCHER_H_
namespace GgafCore {

/**
 * �A�N�^�[�X�g�A�[�̃X�g�A�[�N���X .
 * GgafActorStore �́A�T�u�̓o�^�A�N�^�[(GgafActor)���ɂ����ȃ����o�[�� dispatch() ����̂ɑ΂��A
 * GgafActorStoreDispatcher �́A�T�u�̓o�^�X�g�A�[(GgafActorStore) �� �o�^�A�N�^�[(GgafActor)���A
 * �S���ɂ��Ă���X�g�A�[��D��I��dispatch() ����B
 * @version 1.00
 * @since 2011/06/15
 * @author Masatoshi Tsuge
 */
class GgafActorStoreDispatcher : public GgafActorStore {

private :


public:
    GgafActorStoreDispatcher(const char* prm_name);

    /**
     * �X�g�A�[��o�^���܂�.
     * GgafActorStore::addSubLast() ���Ăяo�O�Ƀ`�F�b�N���s���܂��B
     * ���̂��߁A�o�^�A�N�^�[�ς݃X�g�A�[��o�^���ĉ������B
     * @param prm_pSub �o�^�X�g�A�[
     */
    virtual void addSubLast(GgafActor* prm_pSub) override;

    /**
     * �T�u�̓o�^�X�g�A�[�̏�ԍX�V .
     * �񊈓��ɂł���T�u�X�g�A�[������Δ񊈓��ɂ���B
     * �񊈓��ɂł�������́A�T�u�X�g�A�[�̓o�^�����o�[�S�Ă��񊈓��ł��邱�ƁB
     */
    virtual void processFinal() override;

    virtual ~GgafActorStoreDispatcher() {
    }
};

}
#endif /*GGAFACTORSTOREDISPATCHER_H_*/
