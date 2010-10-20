#ifndef COLLISIONCHECKERLASERCHIP_H_
#define COLLISIONCHECKERLASERCHIP_H_
namespace GgafDx9LibStg {

/**
 * レーザーチップ衝突チェッカークラス.
 * @version 1.00
 * @since 2010/10/20
 * @author Masatoshi Tsuge
 */
class CollisionCheckerLaserChip : public CollisionChecker {

public:

    CollisionCheckerLaserChip(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);
    /**
     * 自身の判定領域と他の当たり判定領域と接触しているか調べる
     * @param prm_pOtherChecker 他の当たり判定領域
     * @return true:当たっている / false:当たっていない
     */
    virtual bool isHit(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker) override;

    virtual ~CollisionCheckerLaserChip();
};

}
#endif /*COLLISIONCHECKERLASERCHIP_H_*/

