#ifndef FORMATIONDELHEID_H_
#define FORMATIONDELHEID_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�f���w�C�h�p�t�H�[���[�V������� .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid : public GgafLib::DepositoryFormation {

public:
    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_FROMATION_MOVE1,
        PROG_FROMATION_MOVE2,
        PROG_FROMATION_MOVE3,
        PROG_FROMATION_MOVE4,
        PROG_FROMATION_MOVE5,
        PROG_LEAVE ,
        PROG_BANPEI,
    };


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
    GgafDxCore::GgafDxGeoElem geoLocate_;

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
    FormationDelheid(const char* prm_name) ;

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpDelheid(EnemyDelheid* pEnemyDelheid) = 0;

    /**
     * �ґ����S�Ď��@���̍U���şr�ł�����ꂽ�ꍇ�̏������� .
     * @param prm_pActor_last_destroyed  �Ō�ɔj�󂳂ꂽ�A�N�^�[
     */
    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;
    /**
     * �X�v���C�������擾�B
     * ���ʂŎ������ĉ������B
     * @return
     */
    virtual GgafLib::SplineManufacture* getSplManuf() = 0;

    virtual void onSayonaraAll() override;


    static void order1(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);

    static void order2(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);

    static void order3(GgafCore::GgafActor* prm_pDelheid, void* prm1, void* prm2);

    /**
     * �ݒu���W�ƌ������Z�b�g .
     */
    void locate(coord x, coord y, coord z,
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
