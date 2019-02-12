#ifndef GROUNDMESHACTOR_H_
#define GROUNDMESHACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace VioletVreath {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDx::MeshActor �������������ۃA�N�^�[�ł��B
 * �i���ݖ��g�p�j
 */
class GroundMeshActor : public GgafDx::MeshActor {

public:
    frame offset_frames_;

    GgafLib::CollisionChecker* _pColliChecker;

public:
    GroundMeshActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat);
    virtual void onCreateModel() override {
    }
    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

//    /**
//     * �t���[�����[�N�I�[�o�[���C�h
//     */
//    virtual void processPreDraw() override;
    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~GroundMeshActor();
};

}
#endif /*GROUNDMESHACTOR_H_*/
