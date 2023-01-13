#ifndef ENEMYRATISLAVIA_H_
#define ENEMYRATISLAVIA_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvChikeiActor.hpp"
#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"

namespace VioletVreath {


DECLARE_EVENT_VAL(RATISLAVIA_EXPLOSION);

/**
 * ���e�B�X�����B�A .
 * �ŏ��ɍ�����n�`�i���g�[���X�j
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
class EnemyRatislavia : public VvChikeiActor<GgafLib::CubeMapMeshActor> {

public:
    /** �g�[���X�̔��a1(�ւ̔��a) */
    coord r1_;
    /** �g�[���X�̔��a2(�����̔��a) */
    coord r2_;
    int colli_part_num_;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_model
     * @param prm_r1 �g�[���X�̔��a1(�ւ̔��a)
     * @param prm_r2 �g�[���X�̔��a2(�����̔��a)
     * @return
     */
    EnemyRatislavia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    virtual int isOutOfView() override;

    virtual bool isOutOfSpacetime() const override;

    virtual ~EnemyRatislavia();

protected:
    /**
     * ���e�B�X�����B�A�̓����蔻��̈���쐬���ݒ肷�� .
     * @param prm_nSphere �����蔻�苅�̐�
     */
    void createCollisionAreaArea(int prm_nSphere);

    /**
     * ���e�B�X�����B�A�̕\�ʂɎq�{�[����ǉ�
     * @param prm_pGeoActor �ǉ�����A�N�^�[
     * @param prm_ang1 �ւ̊p�x�ʒu
     * @param prm_ang2 �֎���̊p�x�ʒu
     */
    void appendGroupChildAsFkOnSurface(GgafDx::GeometricActor* prm_pGeoActor, angle prm_ang1, angle prm_ang2);

};

}
#endif /*ENEMYRATISLAVIA_H_*/

