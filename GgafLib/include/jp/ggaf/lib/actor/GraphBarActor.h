#ifndef GGAFLIB_GRAPHBARACTOR_H_
#define GGAFLIB_GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

namespace GgafLib {


/**
 * 数量バー（単純長方形） .
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

protected:
    /** [r]コンストラクタでPxQuantity をnewした場合 true */
    bool _is_new_Quantity;
    /** [r]モデルチップ横幅ピクセル */
    const float _chip_width;
    /** [r] 1.0 / _chip_width の値。計算用 */
    const float _rate_org_chip_width;
    /** [r]数量バー内容値 */
    Quantity<int, coord>* _pQty;
    /** [r]数量バー最大値 */
    int _min_val;
    /** [r]数量バー最小値 */
    int _max_val;

public:
    /**
     *
     * @param prm_name
     * @param prm_pQty config済みの PxQuantityオブジェクトの参照
     */
    GraphBarActor(const char* prm_name, const char* prm_model, Quantity<int, coord>* prm_pQty);

    GraphBarActor(const char* prm_name, const char* prm_model);

    /**
     * 内部のバーの値を保持する Quantity を置き換える .
     * @param prm_pQty
     */
    void linkQty(Quantity<int, coord>* prm_pQty) {
        if (_pQty) {
            if (_is_new_Quantity) {
                GGAF_DELETE(_pQty);
            }
        }
        _pQty = prm_pQty;
        _is_new_Quantity = false;
    }

    /**
     * 内部のバーの値を保持する Quantity の参照変数を変更 .
     * @param prm_pVariable
     */
    void linkVariable(int* prm_pVariable) {
        _pQty->link(prm_pVariable);
    }
    /**
     * バーの値に対するピクセルの目盛りを付ける。
     * @param prm_min_val バー最小値を設定（これ以下の値はセットできなくなる）
     * @param prm_max_val バー最大値を設定（これ以上の値はセットできなくなる）
     * @param prm_coord_width 最小値～最大値の画面上のピクセル幅を設定
     */
    inline void scale(int prm_min_val, int prm_max_val, coord prm_coord_width ) {
        _min_val = prm_min_val;
        _max_val = prm_max_val;
        _pQty->scale(prm_max_val - prm_min_val, prm_coord_width);
    }

    /**
     * バーの値を設定 .
     * linkしている場合、リンク元の値も変更される .
     * @param prm_val メーター値
     */
    inline void setVal(int prm_val) {
        if (_max_val < prm_val) {
            _pQty->setVal(_max_val);
        } else if (_min_val > prm_val) {
            _pQty->setVal(_min_val);
        } else {
            _pQty->setVal(prm_val);
        }
    }

    /**
     * バーの値を取得 .
     * @return バーの値
     */
    inline int getVal() {
        return _pQty->getVal();
    }

    /**
     * バーの現在値に対応するピクセル値を取得
     * @return ピクセル値
     */
    inline coord getCoordWidth() {
        return _pQty->getQty();
    }

    /**
     * バーの値を加算 .
     * linkしている場合、リンク元の値も変更されるので注意。
     * @param prm_val バーの加算値
     */
    inline void incVal(int prm_val) {
        setVal(_pQty->getVal() + prm_val);
    }

    /**
     * バーの値を減算 .
     * linkしている場合、リンク元の値も変更されるので注意。
     * @param prm_val バーの減算値
     */
    inline void decVal(int prm_val) {
        setVal(_pQty->getVal() - prm_val);
    }

    /**
     * バーの値に対応するピクセル値を計算して取得（設定はされない） .
     * @param prm_val 仮のバーの値
     * @return 仮のバーの値に対応するピクセル値
     */
    inline coord cnvVal2CoordWidth(int prm_val) {
        return _pQty->cnvVal2Qty(prm_val);
    }

    inline int cnvCoordWidth2Val(coord prm_coord_width) {
        return _pQty->cnvQty2Val(prm_coord_width);
    }

    inline void setValByCoordWidth(coord prm_coord_width) {
        setVal(cnvCoordWidth2Val(prm_coord_width));
    }

    void processDraw() override;

    virtual ~GraphBarActor();
};

}
#endif /*GGAFLIB_GRAPHBARACTOR_H_*/

