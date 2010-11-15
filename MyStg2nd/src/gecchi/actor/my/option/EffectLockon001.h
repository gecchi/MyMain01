#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
namespace MyStg2nd {
#define EffectLockon001_SCENE_PROG_FIRST_LOCK     1
#define EffectLockon001_SCENE_PROG_LOCK     2
#define EffectLockon001_SCENE_PROG_RELEASE  3


/**
 * ロックオン
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001 : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    GgafDx9Core::GgafDx9GeometricActor* _pTarget;

    EffectLockon001(const char* prm_name, const char* prm_model_id);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDx9GeometricActor* prm_pTarget) = 0;

    virtual ~EffectLockon001();

    /**
     * デバッグ用：ツリー構造を表示<BR>
     */
    virtual void dump();

    /**
     * デバッグ用：dump()から使用される<BR>
     */
    virtual void dump(std::string prm_parent);

};

}
#endif /*EFFECTLOCKON001_H_*/

