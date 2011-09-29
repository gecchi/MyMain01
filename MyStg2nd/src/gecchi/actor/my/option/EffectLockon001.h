#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {

enum {
    LOCKON001_PROG_FIRST_LOCK = 1,
    LOCKON001_PROG_LOCK          ,
    LOCKON001_PROG_RELEASE       ,
};

/**
 * ロックオン
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001 : public GgafLib::DefaultSpriteSetActor {

public:
    GgafDxCore::GgafDxGeometricActor* _pTarget;

    EffectLockon001(const char* prm_name, const char* prm_model_id);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDxGeometricActor* prm_pTarget) = 0;

    virtual ~EffectLockon001();


//DEBUGモードアプリ終了時のツリー表示時、
//_pTargetが不正になる場合があるため、必要なときにコメントを外して仕様することとする。
//
//    /**
//     * ターゲットも表示するダンプ(デバッグ用) .
//     */
//    void dump();
//
//    /**
//     * ターゲットも表示するダンプ(デバッグ用) .
//     */
//    void dump(std::string prm_parent);

};

}
#endif /*EFFECTLOCKON001_H_*/

