#ifndef FORMATIONEUNOMIA002_H_
#define FORMATIONEUNOMIA002_H_
namespace MyStg2nd {

/**
 * 敵機エウノミア用フォーメーション002グループ .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia002 : public FormationEunomia {

public:

    FormationEunomia002(const char* prm_name);

    virtual void processBehavior() override;

    /**
     * 編隊が全て自機側の攻撃で殲滅させられた場合
     * @param prm_pActorLast 最後に破壊されたアクター
     */
    virtual void onDestroyedAll(GgafDxCore::GgafDxGeometricActor* prm_pActor_LastDestroyed) override;

    virtual ~FormationEunomia002();
};

}
#endif /*FORMATIONEUNOMIA002_H_*/
