#ifndef GGAF_CORE_ENUMINDEX_H_
#define GGAF_CORE_ENUMINDEX_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <map>
#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * 列挙値と順序リスト .
 * enum の列挙値(0,1,2,3・・・)を利用するプログラムで、
 * enum宣言後に動的に要素を減らしたい、といった場合に使用する設計。<BR>
 * ＜使用例＞
 * <pre><code>
 *
 *     enum {
 *         ITEM_KEY_CONFIG = 0 ,
 *         ITEM_SOUND_CONFIG,
 *         ITEM_SCREEN_CONFIG,
 *         ITEM_BACK,
 *     };
 *
 *     EnumIndex itm(ITEM_KEY_CONFIG, ITEM_BACK);
 *     int n, e;
 *     n = itm.n(ITEM_KEY_CONFIG);      //n = 0
 *     n = itm.n(ITEM_SOUND_CONFIG);    //n = 1
 *     n = itm.n(ITEM_SCREEN_CONFIG);   //n = 2
 *     n = itm.n(ITEM_BACK);            //n = 3
 *
 *     e = itm.e(0);                    //e = ITEM_KEY_CONFIG    = 0
 *     e = itm.e(1);                    //e = ITEM_SOUND_CONFIG  = 1
 *     e = itm.e(2);                    //e = ITEM_SCREEN_CONFIG = 2
 *     e = itm.e(3);                    //e = ITEM_BACK          = 3
 *
 *     itm.remove(ITEM_SOUND_CONFIG);   //ITEM_SOUND_CONFIGを削除
 *
 *     n = itm.n(ITEM_KEY_CONFIG);      //n = 0
 *     n = itm.n(ITEM_SOUND_CONFIG);    //エラー（デバッグビルド時)
 *     n = itm.n(ITEM_SCREEN_CONFIG);   //n = 1
 *     n = itm.n(ITEM_BACK);            //n = 2
 *
 *     e = itm.e(0);                    //e = ITEM_KEY_CONFIG    = 0
 *     e = itm.e(1);                    //e = ITEM_SCREEN_CONFIG = 2
 *     e = itm.e(2);                    //e = ITEM_BACK          = 3
 *     e = itm.e(3);                    //e = -1; (範囲外は-1)
 *
 * </code></pre>
 * @version 1.00
 * @since 2014/03/04
 * @author Masatoshi Tsuge
 */
class EnumIndex : public Object {
public:
    /** 列挙の値：順序(0～) */
    std::map<int, int> _n;
    int _enum_start;
    int _enum_end;

    /**
     * コンストラクタ .
     * @param prm_num 最大の列挙の値
     * @param prm_enum_start_index １番目の列挙の値
     */
    EnumIndex(int prm_enum_start, int prm_enum_end) {
        _enum_start = prm_enum_start;
        _enum_end = prm_enum_end;
        for (int i = 0; i <= prm_enum_end-prm_enum_start; i++) {
            _n[(prm_enum_start+i)] = i;
        }
    }

    /**
     * 列挙値と順序リストの対応をリセットする。
     */
    inline void reset() {
        for (int i = 0; i <= _enum_end-_enum_start; i++) {
            _n[(_enum_start+i)] = i;
        }
    }

    /**
     * 列挙の値から、順序(0～)を得る .
     * @param prm_key 列挙の値
     * @return 順序(0～)
     */
    inline int n(int prm_key) {
#ifdef MY_DEBUG
        if (_n.find(prm_key) == _n.end()) {
            throwCriticalException("EnumIndex#n() 列挙値 prm_key="<<prm_key<<" はremoveされたか存在しません");
        }
#endif
        return _n[prm_key];
    }

    /**
     * 順序(0～)から元の列挙の値を得る。
     * 範囲外の順序を指定した場合、-1を返す
     * @param prm_index 順序(0～)
     * @return 元の列挙の値 or 順序範囲外の場合は -1
     */
    inline int e(int prm_index) {
        if ((int)_n.size() <= prm_index) {
            return -1;
        }
        std::map<int, int>::iterator it = _n.begin();
        for (int i = 0; i < prm_index; i++) {
            ++it;
        }
        return it->first;
    }

    /**
     * 列挙要素を削除し、順序を振り直す .
     * @param prm_key 削除する列挙要素の値
     */
    void remove(int prm_key) {
        _n.erase(prm_key);
        //value を詰めて振り直し
        int i = 0;
        for (std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
            it->second = i;
            i++;
        }
    }
    /**
     * 列挙要素を削除(範囲)し、順序を振り直す .
     * @param prm_from  削除する列挙要素の開始値
     * @param prm_to    削除する列挙要素の終了値
     */
    void remove(int prm_from, int prm_to) {
        for (int i = prm_from; i <= prm_to; i++) {
            _n.erase(i);
        }
        //value を詰めて振り直し
        int i = 0;
        for (std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
            it->second = i;
            i++;
        }
    }


    void dump() {
        for (std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
            std::cout << it->first << "->" << it->second << std::endl;
        }
    }

    ~EnumIndex() {
    }
};

}
#endif /*GGAF_CORE_ENUMINDEX_H_*/
