#ifndef DEFAULTSPRITESETACTOR_H_
#define DEFAULTSPRITESETACTOR_H_
namespace GgafDx9LibStg {

/**
 * スプライトセットアクターの具象クラス.
 * GgafDx9Core::GgafDx9SpriteSetActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/07/15
 * @author Masatoshi Tsuge
 */
class DefaultSpriteSetActor : public GgafDx9Core::GgafDx9SpriteSetActor {

public:
    DWORD _frame_offset;

    StgChecker* _pStgChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id);

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

    virtual ~DefaultSpriteSetActor();

};

}
#endif /*DEFAULTSPRITESETACTOR_H_*/
