#ifndef GGAFDX9CHECKER_H_
#define GGAFDX9CHECKER_H_
namespace GgafDx9Core {

/**
 * チェックに関する色々な機能を持ったクラス .
 * （旧GgafDx9GeometryChecker）
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9Checker : public GgafCore::GgafObject {

protected:
    /** 対象アクター */
    GgafDx9GeometricActor* _pActor;

public:

    /** 当たり判定領域 */
    GgafDx9Core::GgafDx9CollisionArea* _pCollisionArea;

    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDx9Checker(GgafDx9GeometricActor* prm_pActor);

    virtual void updateHitArea() = 0;

    //virtual void draw();

    GgafDx9GeometricActor* getTargetActor() {
        if (_pActor == NULL) {
            _TRACE_("GgafDx9Checker::getTargetActor NULLであるがよいのか！");
        }
        return _pActor;
    }

    virtual bool isHit(GgafDx9Checker* prm_pOtherChecker) = 0;

    virtual ~GgafDx9Checker();
};

}
#endif /*GGAFDX9CHECKER_H_*/

