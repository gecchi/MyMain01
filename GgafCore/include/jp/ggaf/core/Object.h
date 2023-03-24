#ifndef GGAF_CORE_OBJECT_H_
#define GGAF_CORE_OBJECT_H_
#include "jp/ggaf/GgafCommonHeader.h"

#ifndef _MSC_VER
    #include <atomic>
#endif
#include <string>

namespace GgafCore {

/**
 * 基底クラス
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class Object {
public:
#ifdef _MSC_VER
    //x86系VCならばアトミック性があるかも・・64bitでも？？・・・。
    /** インスタンスIDのシークエンス */
    static uint64_t _obj_seq;
#else
    /** インスタンスIDのシークエンス */
    static std::atomic<uint64_t> _obj_seq;
#endif
    /** [r]インスタンスID(シークエンス) */
    uint64_t _id;
    /** [r]インスタンス種類 */
    uint64_t _obj_class;

public:
    Object();

    /**
     * インスタンスIDを取得 .
     * @return インスタンスID
     */
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
    inline virtual bool instanceOf(uint64_t Obj_xxxx) const {
        if ((_obj_class & Obj_xxxx) == Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~Object();
};

}
#endif /*GGAF_CORE_OBJECT_H_*/
