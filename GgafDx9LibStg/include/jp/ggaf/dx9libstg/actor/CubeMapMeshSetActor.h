#ifndef CUBEMAPMESHSETACTOR_H_
#define CUBEMAPMESHSETACTOR_H_
namespace GgafDx9LibStg {

/**
 * 環境マップメッシュセットアクター.の具象クラス.
 * GgafDx9Core::GgafDx9CubeMapMeshSetActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetActor : public GgafDx9Core::GgafDx9CubeMapMeshSetActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9Scaler* _pScaler;

    frame _offset_frames;

    CollisionChecker* _pCollisionChecker;

    CubeMapMeshSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~CubeMapMeshSetActor();
};

}
#endif /*CUBEMAPMESHSETACTOR_H_*/
