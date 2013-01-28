#ifndef GGAFACTORDEPOSITORYSTORE_H_
#define GGAFACTORDEPOSITORYSTORE_H_
namespace GgafCore {

/**
 * �A�N�^�[�f�|�W�g���̕ۊǏ��N���X .
 * GgafActorDepository �́A�T�u�̓o�^�A�N�^�[(GgafActor)���ɂ����ȃ����o�[�� dispatch() ����̂ɑ΂��A
 * GgafActorDepositoryStore �́A�T�u�̓o�^�f�|�W�g��(GgafActorDepository) �� �o�^�A�N�^�[(GgafActor)���A
 * �S���ɂɂ��Ă���f�|�W�g����D��I�� dispatch() ���܂��B
 * �܂�Adispatch() �œ�����I�u�W�F�N�g�� �f�|�W�g��(GgafActorDepository)�ɂȂ�܂��B
 * �ȒP�Ɍ����ƃf�|�W�g���̃f�|�W�g���ł��B<BR>
 * �y���Ӂz<BR>
 * processFinal() �ŁA�T�u�f�|�W�g���̓o�^�����o�[�S�Ă��񊈓��Ȃ�΁A���̃T�u�f�|�W�g����񊈓��ɂ���B<BR>
 * �Ƃ�����������������B<BR>
 * �{�I�u�W�F�N�g�ŁAdispatch() ���A�T�u�f�|�W�g���𓾂��u�Ԃ́A�T�u�f�|�W�g���̃����o�[�S���񊈓��ł���B<BR>
 * ���̂܂܉������Ȃ��ƁA���̃t���[���� processFinal() �ŁA�T�u�f�|�W�g���̃����o�[���S�Ĕ񊈓��ɖ߂��Ă��܂��A
 * dispatch() �����Ӗ����Ȃ��Ȃ��Ă��܂��B<BR>
 * �{�I�u�W�F�N�g�ŁAdispatch() �����Ȃ�΁A����ꂽ�f�|�W�g�����璼���ɍŒ���dispatch() ��������΂����Ȃ��B<BR>
 * @version 1.00
 * @since 2011/06/15
 * @author Masatoshi Tsuge
 */
class GgafActorDepositoryStore : public GgafActorDepository {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pStat
     */
    GgafActorDepositoryStore(const char* prm_name, GgafStatus* prm_pStat = nullptr);

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
