#ifndef GGAFCORE_GGAFOBJECT_H_
#define GGAFCORE_GGAFOBJECT_H_
#include "GgafCommonHeader.h"

#ifndef _MSC_VER
    #include <atomic>
#endif
#include <string>

namespace GgafCore {

/** ノード種別 */
typedef uint64_t nodekind;

/**
 * 基底クラス
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class GgafObject {
public:
#ifdef _MSC_VER
    //x86系VCならばアトミック性がある・・64bitでも？？・・・。
    //まぁ_obj_seqが狂ってもDEBUGの時にちょっと不便なだけなので・・・；
    static uint64_t _obj_seq;
#else
    static std::atomic<uint64_t> _obj_seq;
#endif
    uint64_t _id;


    /** [r]インスタンス種類 */
    nodekind _obj_class;

public:
    GgafObject();
    inline uint64_t getId() {
        return _id;
    }

    /**
     * 識別名取得 .
     * @return 識別名
     */
    virtual std::string toString();

    /**
     * オブジェクトが何のクラス由来かを調べる。
     * _obj_class メンバ変数に Obj_xxxx マクロ定数が設定されていることが前提。
     * @param prm_Obj_xxxx 調べるクラスのマクロ定数
     * @return
     */
    inline virtual bool instanceOf(nodekind Obj_xxxx) const {
        if ((_obj_class & Obj_xxxx) == Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafObject();
};

}
#endif /*GGAFCORE_GGAFOBJECT_H_*/
