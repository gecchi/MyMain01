﻿#ifndef EFFECTEXPLOSION002_H_
#define EFFECTEXPLOSION002_H_
namespace MyStg2nd {

/**
 * 爆発エフェクトその２ .
 * 輪っかが広がる
 * @version 1.00
 * @since 2010/03/19
 * @author Masatoshi Tsuge
 */
class EffectExplosion002 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    EffectExplosion002(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void onInactive() override;

    int isOffscreen() override {
        //画面外判定無し
        return 0;
    }

    bool isOutOfGameSpace() override {
        //ゲーム座標範囲外判定無し
        return false;
    }

    virtual ~EffectExplosion002();
};

}
#endif /*EFFECTEXPLOSION002_H_*/

