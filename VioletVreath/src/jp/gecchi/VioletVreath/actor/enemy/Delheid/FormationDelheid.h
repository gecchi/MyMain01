#ifndef FORMATIONDELHEID_H_
#define FORMATIONDELHEID_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�f���w�C�h�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid : public VvFormationActor<GgafLib::DepositoryFormation> {

public:
    /** �f���w�C�h�؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_pDelheidDepo_;
    /** �f���w�C�h�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_pShotDepo_;
    /** �n�_�E�I�_�̍��W�v�Z�̂��߂̃_�~�[ */
    EnemyDelheid* pDummy_;

    /** �n�_�̃A���T�i */
    EnemyAlisana* pAlisana_start;
    /** �I�_�̃A���T�i */
    EnemyAlisana* pAlisana_goal;
    /** [r]�ݒu���W�ƌ��� */
    GgafDx::GeoElem geoLocate_;

    /** �ґ���(RANK�ϓ�) */
    int RV_Num_;
    /** �ґ������o�[�̏o���Ԋu�t���[��(RANK�ϓ�) */
    frame RV_LaunchInterval;
    /** �ґ������o�[�̏����ړ����x(RANK�ϓ�) */
    velo RV_MvVelo_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     */
    FormationDelheid(const char* prm_name, void* prm_pFunc_StatusReset = nullptr);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onSummonDelheid(EnemyDelheid* pEnemyDelheid) = 0;

    virtual void processBehavior() override;
    /**
     * �X�v���C�������擾�B
     * ���ʂŎ������ĉ������B
     * @return
     */
    virtual GgafDx::CurveManufacture* getSplManuf() = 0;

    virtual void onSayonaraAll() override;


    static void order1(GgafDx::GeometricActor* prm_pDelheid, void* prm1, void* prm2, void* prm3);

    static void order2(GgafDx::GeometricActor* prm_pDelheid, void* prm1, void* prm2, void* prm3);

    static void order3(GgafDx::GeometricActor* prm_pDelheid, void* prm1, void* prm2, void* prm3);

    /**
     * �ݒu���W�ƌ������Z�b�g .
     */
    void setPosition(coord x, coord y, coord z,
                     angle rx, angle rz, angle ry) {
        geoLocate_.x = x;
        geoLocate_.y = y;
        geoLocate_.z = z;
        geoLocate_.rx = rx;
        geoLocate_.rz = rz;
        geoLocate_.ry = ry;
    }

    virtual ~FormationDelheid();
};

}
#endif /*FORMATIONDELHEID_H_*/
