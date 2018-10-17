#ifndef GGAFCORE_GGAFACTORDEPOSITORYSTORE_H_
#define GGAFCORE_GGAFACTORDEPOSITORYSTORE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

namespace GgafCore {

/**
 * �A�N�^�[�f�|�W�g���̕ۊǏ��N���X .
 * GgafActorDepository �́A�q�̓o�^�A�N�^�[(GgafActor)���ɂ����ȃ����o�[�� dispatch() ����̂ɑ΂��A
 * GgafActorDepositoryStore �́A�q�̓o�^�f�|�W�g��(GgafActorDepository) �� �o�^�A�N�^�[(GgafActor)���A
 * �S���ɂɂ��Ă���f�|�W�g����D��I�� dispatch() ���܂��B
 * �܂�Adispatch() �œ�����I�u�W�F�N�g�� �f�|�W�g��(GgafActorDepository)�ɂȂ�܂��B
 * �v�̓f�|�W�g���̃f�|�W�g���ł��B<BR>
 * �y���Ӂz<BR>
 * processFinal() �ŁA�q�f�|�W�g���̓o�^�����o�[�S�Ă��񊈓��Ȃ�΁A���̎q�f�|�W�g����񊈓��ɂ���B<BR>
 * �Ƃ�����������������B<BR>
 * ����Ė{�I�u�W�F�N�g��dispatch() �����s���A�q�̃f�|�W�g���𓾂��u�Ԃ́A���̃f�|�W�g���̃����o�[�S���񊈓��ł���B�i���R�Ƃ����Γ��R�j<BR>
 * ���̂܂܉������Ȃ��ƁA���̃t���[���� processFinal() �ŁA�q�f�|�W�g���̃����o�[�������I���Ƃ݂Ȃ���A�S�Ĕ񊈓��ɖ߂��Ă��܂��A
 * dispatch() �����Ӗ����Ȃ��Ȃ��Ă��܂��B<BR>
 * �{�I�u�W�F�N�g�ŁAdispatch() �����Ȃ�΁A����ꂽ�f�|�W�g�����璼���ɍŒ���active�ɂ���K�v������B�i�܂肻�̓������|�W�g������dispatch()����j�B<BR>
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
     * GgafActorDepository::appendChild() ���Ăяo�O�Ƀ`�F�b�N���s���܂��B
     * ���̂��߁A�o�^�A�N�^�[�ς݃f�|�W�g����o�^���ĉ������B
     * @param prm_pChild �o�^�f�|�W�g��
     */
    virtual void put(GgafActor* prm_pChild) override;

    /**
     * �q�̓o�^�f�|�W�g���̏�ԍX�V .
     * �񊈓��ɂł���q�f�|�W�g��������Δ񊈓��ɂ���B
     * �񊈓��ɂł�������́A�q�f�|�W�g���̓o�^�����o�[�S�Ă��񊈓��ł��邱�ƁB
     */
    virtual void processFinal() override;

    virtual ~GgafActorDepositoryStore() {
    }
};

}
#endif /*GGAFCORE_GGAFACTORDEPOSITORYSTORE_H_*/
