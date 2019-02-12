#ifndef GGAF_LIB_PIEGRAPHSPRITEACTOR_H_
#define GGAF_LIB_PIEGRAPHSPRITEACTOR_H_
#include "jp/ggaf/lib/actor/DefaultRegularPolygonSpriteActor.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

namespace GgafLib {


/**
 * 数量円グラフ .
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class PieGraphSpriteActor : public DefaultRegularPolygonSpriteActor {

protected:
    /** [r]コンストラクタでPxQuantity をnewした場合 true */
    bool _is_new_Quantity;

public:
    /** [r]数量円グラフ内容値<実際の数量, 扇ファンの数> */
    Quantity<int, int>* _pFanQty;
    /** [r]数量円グラフ最大値 */
    int _min_val;
    /** [r]数量円グラフ最小値 */
    int _max_val;

public:
    /**
     *
     * @param prm_name
     * @param prm_pFanQty config済みの PxQuantityオブジェクトの参照
     */
    PieGraphSpriteActor(const char* prm_name, const char* prm_model, Quantity<int, int>* prm_pFanQty);

    PieGraphSpriteActor(const char* prm_name, const char* prm_model);

    /**
     * 内部の円グラフの値を保持する Quantity を置き換える .
     * @param prm_pFanQty
     */
    void linkQty(Quantity<int, int>* prm_pFanQty);

    /**
     * 内部の円グラフの値を保持する Quantity の参照変数を変更 .
     * @param prm_pVariable
     */
    void linkVariable(int* prm_pVariable);

    /**
     * 円グラフの値に対するピクセルの目盛りを付ける。
     * @param prm_min_val 円グラフ内部実値の最小値を設定（これ以下の値はセットできなくなる）
     * @param prm_max_val 円グラフ内部実値の最大値を設定（これ以上の値はセットできなくなる）
     * @param prm_min_fan_num prm_min_valに対応するFANの数
     * @param prm_max_fan_num prm_max_valに対応するFANの数
     */
    inline void scale(int prm_min_val, int prm_max_val, int prm_min_fan_num, int prm_max_fan_num) {
        _min_val = prm_min_val;
        _max_val = prm_max_val;
        _pFanQty->scale(prm_min_val, prm_max_val, prm_min_fan_num, prm_max_fan_num);
    }

    /**
     * 円グラフの値を設定 .
     * linkしている場合、リンク元の変数の値も変更されるので注意 .
     * @param prm_val 円グラフの値
     */
    inline void setVal(int prm_val) {
        if (_max_val < prm_val) {
            _pFanQty->setVal(_max_val);
        } else if (_min_val > prm_val) {
            _pFanQty->setVal(_min_val);
        } else {
            _pFanQty->setVal(prm_val);
        }
    }

    /**
     * 円グラフの値を取得 .
     * @return 円グラフの値
     */
    inline int getVal() {
        return _pFanQty->getVal();
    }

    /**
     * 円グラフの現在値に対応するFANの枚数を取得
     * @return FANの枚数
     */
    inline int getFanNum() {
        return _pFanQty->getQty();
    }

    /**
     * 円グラフの値を加算 .
     * linkしている場合、リンク元の値も変更されるので注意。
     * @param prm_val 円グラフの加算値
     */
    inline void incVal(int prm_val) {
        setVal(_pFanQty->getVal() + prm_val);
    }

    /**
     * 円グラフの値を減算 .
     * linkしている場合、リンク元の値も変更されるので注意。
     * @param prm_val 円グラフの減算値
     */
    inline void decVal(int prm_val) {
        setVal(_pFanQty->getVal() - prm_val);
    }

    void processDraw() override;

    virtual ~PieGraphSpriteActor();
};

}
#endif /*GGAF_LIB_PIEGRAPHSPRITEACTOR_H_*/

