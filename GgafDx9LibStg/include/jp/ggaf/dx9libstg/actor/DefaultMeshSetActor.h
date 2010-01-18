#ifndef DEFAULTMESHSETACTOR_H_
#define DEFAULTMESHSETACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/06/16
 * @author Masatoshi Tsuge
 */
class DefaultMeshSetActor : public GgafDx9Core::GgafDx9MeshSetActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    DWORD _frame_offset;

    StgChecker* _pStgChecker;

    DefaultMeshSetActor(const char* prm_name, const char* prm_model);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultMeshSetActor();
};

}
#endif /*DEFAULTMESHSETACTOR_H_*/
