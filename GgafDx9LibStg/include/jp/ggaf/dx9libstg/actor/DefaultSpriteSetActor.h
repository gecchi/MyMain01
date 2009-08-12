#ifndef DEFAULTSPRITESETACTOR_H_
#define DEFAULTSPRITESETACTOR_H_
namespace GgafDx9LibStg {

/**
 * スプライトセットアクターの具象クラス.
 * GgafDx9Core::GgafDx9SpriteSetActor を空実装した具象アクターです。
 */
class DefaultSpriteSetActor : public GgafDx9Core::GgafDx9SpriteSetActor {

public:
    DWORD _frame_offset;

    StgChecker* _pStgChecker;
    /** 座標移動支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processPreDraw() {
        GgafDx9Core::GgafDx9SpriteSetActor::processPreDraw();
    }

    virtual void processDraw() {
        GgafDx9Core::GgafDx9SpriteSetActor::processDraw();
    }

    virtual void processAfterDraw();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultSpriteSetActor();

};

}
#endif /*DEFAULTSPRITESETACTOR_H_*/
