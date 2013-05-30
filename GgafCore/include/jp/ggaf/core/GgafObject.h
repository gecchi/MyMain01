#ifndef GGAFOBJECT_H_
#define GGAFOBJECT_H_
namespace GgafCore {

/**
 * 基底クラス
 * @version 1.00
 * @since 2007/12/24
 * @author Masatoshi Tsuge
 */
class GgafObject {
    static int _obj_seq;

public:
    int _id;
    /** [r]インスタンス種類 */
    uint32_t _obj_class;

public:
    GgafObject();

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
    virtual bool instanceOf(uint32_t prm_Obj_xxxx) {
        if ((_obj_class & prm_Obj_xxxx) == prm_Obj_xxxx) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
