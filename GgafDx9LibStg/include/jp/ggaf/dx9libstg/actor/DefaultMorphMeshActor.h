#ifndef DEFAULTMORPHMESHACTOR_H_
#define DEFAULTMORPHMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 */
class DefaultMorphMeshActor : public GgafDx9Core::GgafDx9MorphMeshActor {

public:
    DWORD _frame_offset;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;
    GgafDx9Core::GgafDx9GeometryMorpher* _pMorpher;
    StgChecker* _pStgChecker;

    DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id);

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

    virtual ~DefaultMorphMeshActor();
};

}
#endif /*DEFAULTMORPHMESHACTOR_H_*/
