#ifndef STGUTIL_H_
#define STGUTIL_H_
namespace GgafDx9LibStg {

class StgUtil: public GgafDx9Core::GgafDx9Util {
public:

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);

    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere*  pOppSphere);

    /**
     * Rz変化による nWay弾を撃つ .
     * @param prm_pFrom 発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget 目標
     * @param prm_way Way数
     * @param prm_angClearance Wayの間隔
     * @param prm_velo 初期速度
     * @param prm_acce 加速度
     */
    static void shotWay001(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo, acce prm_acce);
    /**
     * Rz変化による nWay弾を複数セット同時に撃つ .
     * @param prm_pFrom        発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget      目標
     * @param prm_way          Way数
     * @param prm_angClearance Wayの間隔
     * @param prm_velo_top     初弾WAYの初期速度
     * @param prm_acce_top     初弾WAYの加速度
     * @param prm_num          撃つWAY弾のセット数
     * @param prm_attenuated   次のWAY弾の初期速度加速度の減衰率
     */
    static void shotWay001v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angClearance,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);


    /**
     * Ry は目標への向き＋ANGLE90で、Rz変化による nWay放射弾を打つ .
     * @param prm_pFrom 発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget 目標
     * @param prm_way 放射Way数
     * @param prm_angBegin 放射開始アングル
     * @param prm_velo 初期速度
     * @param prm_acce 加速度
     */
    static void shotWay002(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo, acce prm_acce);

    /**
     * shotWay002弾を複数セット同時に撃つ .
     * @param prm_pFrom 発射元
     * @param prm_pDispatcher_Shot 発射するショットのディスパッチャー
     * @param prm_pTarget 目標
     * @param prm_way 放射Way数
     * @param prm_angBegin 放射開始アングル
     * @param prm_velo_top 初弾放射WAYの初期速度
     * @param prm_acce_top 初弾放射WAYの加速度
     * @param prm_num      撃つ放射WAY弾のセット数
     * @param prm_attenuated 次のWAY弾の初期速度加速度の減衰率
     */
    static void shotWay002v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angBegin,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);

};

}
#endif /*STGUTIL_H_*/
