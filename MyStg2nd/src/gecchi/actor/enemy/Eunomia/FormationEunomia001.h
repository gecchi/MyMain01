#ifndef FORMATIONEUNOMIA001_H_
#define FORMATIONEUNOMIA001_H_
namespace MyStg2nd {

/**
 * 敵機エウノミア用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001 : public FormationEunomia {

public:

    FormationEunomia001(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合
     * @param prm_pActorLast 最後に破壊されたアクター
     */
    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_LastDestroyed) override;

    virtual ~FormationEunomia001();
};

}
#endif /*FORMATIONEUNOMIA001_H_*/
