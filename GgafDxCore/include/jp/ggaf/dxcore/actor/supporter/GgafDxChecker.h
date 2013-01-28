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

public:
    /** 対象アクター */
    GgafDxGeometricActor* _pActor;
    /** 当たり判定領域 */
    GgafDxCore::GgafDxCollisionArea* _pCollisionArea;

public:
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    GgafDxChecker(GgafDxGeometricActor* prm_pActor);

    virtual void updateHitArea() = 0;

    /**
     * 当たり判定領域を作成する（＝当たり判定領域要素の配列を作成する） .
     * 内部で領域の配列を生成します。
     * 最初に必ず実行してください。
     * @param prm_colli_part_num 当たり判定領域の当たり判定領域要素数(1～n)
     */
    virtual void makeCollision(int prm_colli_part_num);

    /**
     * ヒットシしているかどうか
     * @param prm_pOtherChecker 相手のチェッカー
     * @return
     */
    virtual bool isHit(GgafDxChecker* prm_pOtherChecker) = 0;

    virtual GgafDxGeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_("GgafDxChecker::getTargetActor nullptrであるがよいのか！");
        }
        return _pActor;
    }

    /**
     * 当たり判定領域の要素を有効にする。
     * デフォルトは有効状態になっています。
     * @param prm_index 有効にする当たり判定領域の要素番号
     */
    virtual void enable(int prm_index) {
        _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = true;
    }

    /**
     * 当たり判定領域の要素を無効にする。
     * @param prm_index 無効にする当たり判定領域の要素番号
     */
    virtual void disable(int prm_index) {
        _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = false;
    }

    /**
     * 当たり判定領域の要素が有効か調べる。
     * @param prm_index 調べたい当たり判定領域の要素番号
     * @return true:有効 / false:無効
     */
    virtual bool isEnable(int prm_index) {
        return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
    }

    virtual ~GgafDxChecker();
};

}
#endif /*GGAFDXCHECKER_H_*/

