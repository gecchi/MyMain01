﻿#ifndef DEFAULTSPRITESETACTOR_H_
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

    CollisionChecker* _pCollisionChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id);

    virtual void onCreateModel() override {
    }

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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultSpriteSetActor();

};

}
#endif /*DEFAULTSPRITESETACTOR_H_*/
