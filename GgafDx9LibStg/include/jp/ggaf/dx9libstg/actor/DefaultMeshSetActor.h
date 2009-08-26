#ifndef DEFAULTMESHSETACTORH_
#define DEFAULTMESHSETACTORH_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 */
class DefaultMeshSetActor : public GgafDx9Core::GgafDx9MeshSetActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    DWORD _frame_offset;

    StgChecker* _pStgChecker;

    DefaultMeshSetActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual void drawHitArea();

    virtual ~DefaultMeshSetActor();
};

}
#endif /*DEFAULTMESHSETACTORH_*/
