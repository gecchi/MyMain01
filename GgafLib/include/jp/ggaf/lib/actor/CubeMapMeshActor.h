#ifndef DEFAULTCUBEMAPMESHACTOR_H_
#define DEFAULTCUBEMAPMESHACTOR_H_
namespace GgafLib {

/**
 * ���}�b�v���b�V���A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxMeshActor �������������ۃA�N�^�[�ł��B
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class CubeMapMeshActor : public GgafDxCore::GgafDxCubeMapMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* _pScaler;

    frame _offset_frames;

    CollisionChecker* _pCollisionChecker;

    CubeMapMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

//    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
//    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~CubeMapMeshActor();
};

}
#endif /*DEFAULTCUBEMAPMESHACTOR_H_*/