#ifndef GGAFDXCHECKER_H_
#define GGAFDXCHECKER_H_
namespace GgafDxCore {

/**
 * チェックに関する色々な機能を持ったクラス .
 * （旧GgafDxGeometryChecker）
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxChecker : public GgafCore::GgafObject {

protected:
    /** 対象アクター */
    GgafDxGeometricActor* _pActor;

public:

    /** 当たり判定領域 */
    GgafDxCore::GgafDxCollisionArea* _pCollisionArea;
//    /** 吹っ飛びX成分 */
//    int _blown_sgn_vX;
//    /** 吹っ飛びY成分 */
//    int _blown_sgn_vY;
//    /** 吹っ飛びZ成分 */
//    int _blown_sgn_vZ;
    /** 吹っ飛び計算を行うか */
//    int _is_blown;
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDxChecker(GgafDxGeometricActor* prm_pActor);

    virtual void updateHitArea() = 0;

    GgafDxGeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_("GgafDxChecker::getTargetActor nullptrであるがよいのか！");
        }
        return _pActor;
    }

    virtual bool isHit(GgafDxChecker* prm_pOtherChecker) = 0;

    virtual ~GgafDxChecker();
};

}
#endif /*GGAFDXCHECKER_H_*/

