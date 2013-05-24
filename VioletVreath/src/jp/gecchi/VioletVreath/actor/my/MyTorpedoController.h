#ifndef MYTORPEDOCONTROLLER_H_
#define MYTORPEDOCONTROLLER_H_
#include "jp/ggaf/core/actor/ex/GgafDummyActor.h"

namespace VioletVreath {

/**
 * �����R���g���[���[ .
 * �P�I�v�V�����ɂ��P�̋����R���g���[���[��ێ����Ă��܂��B
 * @version 1.00
 * @since 2010/09/15
 * @author Masatoshi Tsuge
 */
class MyTorpedoController : public GgafCore::GgafDummyActor {

public:
    /** [r]�P�I�v�V����������̍ő勛�����ˉ\�� */
    static int max_torpedo_num_;
    /** [r]�P�I�v�V����������̌��݋������ˉ\�� */
    static int torpedo_num_;

    /** [r]�e�A�N�^�[�ƂȂ�I�v�V���� */
    GgafDxCore::GgafDxGeometricActor* pOrg_;
    MyLockonController* pLockonCtrler_;
    /** [r]�ێ����鋛���z��i�v�f���� max_torpedo_num_ �j */
    MyTorpedo** papTorpedo_;
    /** [r]�ێ����鋛�������f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_TorpedoBlast_;
    /** �������ˋ����� */
    int firing_num_;
    /** ���݋������˒����ǂ��� true:���Âꂩ�̋�����������/false:�S�Ă̋������񊈓���� */
    bool in_firing_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pOrg �e�ƂȂ�I�v�V����
     * @return
     */
    MyTorpedoController(const char* prm_name, GgafDxCore::GgafDxGeometricActor* prm_pOrg, MyLockonController* prm_pLockonCtrler);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    /**
     * ��������Ĕ��˂���B
     * �A���A���Âꂩ�̋������������̏ꍇ�́A�������Ȃ��B
     * �S�Ă̋������񊈓���ԂŁA�{���\�b�h�����s����Ƌ�������Ĕ��˂���B
     */
    bool fire();

    virtual ~MyTorpedoController();


};

}
#endif /*MYTORPEDOCONTROLLER_H_*/

