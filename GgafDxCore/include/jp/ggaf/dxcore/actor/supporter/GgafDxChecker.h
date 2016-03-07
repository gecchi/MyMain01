#ifndef GGAFDXCORE_GGAFDXCHECKER_H_
#define GGAFDXCORE_GGAFDXCHECKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

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
    GgafDxGeometricActor* const _pActor;
    /** 当たり判定領域 */
    GgafDxCollisionArea* _pCollisionArea;

public:
    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    explicit GgafDxChecker(GgafDxGeometricActor* prm_pActor);

    virtual void updateHitArea() = 0;

    /**
     * 当たり判定領域を作成する（＝当たり判定領域要素の配列を作成する） .
     * 内部で領域の配列を生成します。
     * 最初に必ず実行してください。
     * @param prm_colli_part_num 当たり判定領域の当たり判定領域要素数(1～n)
     */
    virtual void createCollisionArea(int prm_colli_part_num);

    /**
     * ヒットシしているかどうか
     * @param prm_pOtherChecker 相手のチェッカー
     * @return
     */
    virtual bool isHit(const GgafDxChecker* const prm_pOtherChecker) = 0;

    virtual GgafDxGeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_(FUNC_NAME<<" nullptrであるがよいのか！");
        }
        return _pActor;
    }

    inline GgafDxCollisionArea* getArea() {
        return _pCollisionArea;
    }

    /**
     * 当たり判定領域の要素を有効にする。
     * デフォルトは有効状態になっています。
     * @param prm_index 有効にする当たり判定領域の要素番号
     */
    virtual void enable(int prm_index);

    /**
     * 当たり判定領域の要素を無効にする。
     * @param prm_index 無効にする当たり判定領域の要素番号
     */
    virtual void disable(int prm_index);

    /**
     * 当たり判定領域の要素が有効か調べる。
     * @param prm_index 調べたい当たり判定領域の要素番号
     * @return true:有効 / false:無効
     */
    virtual bool isEnable(int prm_index);

    virtual ~GgafDxChecker();
};

}
#endif /*GGAFDXCORE_GGAFDXCHECKER_H_*/

