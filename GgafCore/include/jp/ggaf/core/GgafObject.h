#ifndef GGAFCORE_GGAFOBJECT_H_
#define GGAFCORE_GGAFOBJECT_H_
namespace GgafCore {

/** クラス種別 */
typedef uint32_t classkind;

/**
 * 基底クラス
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class GgafObject {
    static uint64_t _obj_seq;
    uint64_t _id;
public:

    /** [r]インスタンス種類 */
    classkind _obj_class;

public:
    GgafObject();
    uint64_t getId() {
        return _id;
    }
    /**
     * 識別名取得 .
     * @return 識別名
     */
    virtual char* toString();

    /**
     * オブジェクトが何のクラス由来かを調べる。
     * _obj_class メンバ変数に Obj_xxxx マクロ定数が設定されていることが前提。
     * @param prm_Obj_xxxx 調べるクラスのマクロ定数
     * @return
     */
    virtual bool instanceOf(classkind prm_Obj_xxxx) {
        if ((_obj_class & prm_Obj_xxxx) == prm_Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafObject();
};

}
#endif /*GGAFCORE_GGAFOBJECT_H_*/
