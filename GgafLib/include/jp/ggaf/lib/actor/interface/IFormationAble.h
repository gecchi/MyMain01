#ifndef IFORMATIONABLE_H_
#define IFORMATIONABLE_H_

namespace GgafLib {



/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * 継承クラスはprocessJudgement()使用時注意すること。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class IFormationAble {
public:

    GgafLib::FormationActor* _pFormation;

    IFormationAble();

    void informDestroyedFollower();
//    virtual void onDestroyedFormation(GgafDxCore::GgafDxDrawableActor* prm_pActor_LastDestroyed) = 0;
    virtual ~IFormationAble();
};

}
#endif /*IFORMATIONABLE_H_*/
