#ifndef GGAFCORE_GGAFENUMINDEX_H_
#define GGAFCORE_GGAFENUMINDEX_H_
#include "jp/ggaf/core/GgafObject.h"
#include <map>

#include "jp/ggaf/core/exception/GgafCriticalException.h"

namespace GgafCore {

/**
 * 列挙値と順序リスト .
 * enum の列挙値(0,1,2,3・・・)を利用するプログラムで、
 * enum宣言後に動的に要素を減らしたい、といった場合に使用する設計。
 * @version 1.00
 * @since 2014/03/04
 * @author Masatoshi Tsuge
 */
class GgafEnumIndex : public GgafObject {
public:
    /** 列挙の値：順序(0～) */
    std::map<int, int> _n;

    /**
     *
     * @param prm_num 最大の列挙の値
     * @param prm_enum_start_index １番目の列挙の値
     */
    GgafEnumIndex(int prm_enum_start, int prm_enum_end) {
        for(int i = 0; i <= prm_enum_end-prm_enum_start; i++) {
            _n[(prm_enum_start+i)] = i;
        }
    }

    /**
     * 列挙の値から、順序(0～)を得る .
     * @param prm_key 列挙の値
     * @return 順序(0～)
     */
    inline int n(int prm_key) {
#ifdef MY_DEBUG
        if (_n.find(prm_key) != _n.end()) {
            //OK
        } else {
            throwGgafCriticalException("GgafEnumIndex#n() 列挙値 prm_key="<<prm_key<<" はremoveされたか存在しません");
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
        for(std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
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
        for(int i = prm_from; i <= prm_to; i++) {
            _n.erase(i);
        }
        //value を詰めて振り直し
        int i = 0;
        for(std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
            it->second = i;
            i++;
        }
    }


    void dump() {
        for(std::map<int, int>::iterator it = _n.begin(); it != _n.end(); ++it) {
            std::cout << it->first << "->" << it->second << std::endl;
        }
    }

    ~GgafEnumIndex() {
    }
};

}
#endif /*GGAFCORE_GGAFENUMINDEX_H_*/
