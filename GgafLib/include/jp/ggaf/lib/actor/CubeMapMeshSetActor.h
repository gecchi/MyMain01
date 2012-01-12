#ifndef CUBEMAPMESHSETACTOR_H_
#define CUBEMAPMESHSETACTOR_H_
namespace GgafLib {

/**
 * 環境マップメッシュセットアクター.の具象クラス.
 * GgafDxCore::GgafDxCubeMapMeshSetActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetActor : public GgafDxCore::GgafDxCubeMapMeshSetActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pCollisionChecker;

    CubeMapMeshSetActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

//    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
//    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~CubeMapMeshSetActor();
};

}
#endif /*CUBEMAPMESHSETACTOR_H_*/
