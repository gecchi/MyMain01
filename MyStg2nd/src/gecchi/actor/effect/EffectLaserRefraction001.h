#ifndef EFFECTLASERREFRACTION001_H_
#define EFFECTLASERREFRACTION001_H_
namespace MyStg2nd {

/**
 * レーザー屈折エフェクト .
 * @version 1.00
 * @since 2010/07/26
 * @author Masatoshi Tsuge
 */
class EffectLaserRefraction001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    EffectLaserRefraction001(const char* prm_name);

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

    virtual ~EffectLaserRefraction001();
};

}
#endif /*EFFECTLASERREFRACTION001_H_*/

