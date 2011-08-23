#ifndef GGAFACTORDEPOSITORYSTORE_H_
#define GGAFACTORDEPOSITORYSTORE_H_
namespace GgafCore {

/**
 * �A�N�^�[�f�|�W�g���̃f�|�W�g���N���X .
 * GgafActorDepository �́A�T�u�̓o�^�A�N�^�[(GgafActor)���ɂ����ȃ����o�[�� dispatch() ����̂ɑ΂��A
 * GgafActorDepositoryStore �́A�T�u�̓o�^�f�|�W�g��(GgafActorDepository) �� �o�^�A�N�^�[(GgafActor)���A
 * �S���ɂ��Ă���f�|�W�g����D��I��dispatch() ����B
 * @version 1.00
 * @since 2011/06/15
 * @author Masatoshi Tsuge
 */
class GgafActorDepositoryStore : public GgafActorDepository {

private :


public:
    GgafActorDepositoryStore(const char* prm_name);

    /**
     * �f�|�W�g����o�^���܂�.
     * GgafActorDepository::addSubLast() ���Ăяo�O�Ƀ`�F�b�N���s���܂��B
     * ���̂��߁A�o�^�A�N�^�[�ς݃f�|�W�g����o�^���ĉ������B
     * @param prm_pSub �o�^�f�|�W�g��
     */
    virtual void addSubLast(GgafActor* prm_pSub) override;

    /**
     * �T�u�̓o�^�f�|�W�g���̏�ԍX�V .
     * �񊈓��ɂł���T�u�f�|�W�g��������Δ񊈓��ɂ���B
     * �񊈓��ɂł�������́A�T�u�f�|�W�g���̓o�^�����o�[�S�Ă��񊈓��ł��邱�ƁB
     */
    virtual void processFinal() override;

    virtual ~GgafActorDepositoryStore() {
    }
};

}
#endif /*GGAFACTORDEPOSITORYSTORE_H_*/
