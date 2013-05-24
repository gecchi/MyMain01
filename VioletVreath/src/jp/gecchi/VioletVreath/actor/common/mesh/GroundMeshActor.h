#ifndef GROUNDMESHACTOR_H_
#define GROUNDMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace VioletVreath {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxMeshActor �������������ۃA�N�^�[�ł��B
 * �i���ݖ��g�p�j
 */
class GroundMeshActor : public GgafDxCore::GgafDxMeshActor {

public:
    GgafDxCore::GgafDxScaler* _pScaler;

    frame offset_frames_;

    GgafLib::CollisionChecker3D* _pColliChecker;

public:
    GroundMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);
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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~GroundMeshActor();
};

}
#endif /*GROUNDMESHACTOR_H_*/
