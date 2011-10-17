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
    static const char* NANASHI;
    static int _iSeq;

public:
    int _id;
    /** [r]ノード識別名(50文字まで) */
    char* _name;
    /** [r]インスタンス種類 */
    UINT32 _obj_class;

    GgafObject(const char* prm_name = GgafObject::NANASHI);

    /**
     * 名前取得 .
     * @return 名前
     */
    virtual char* getName() {
        return _name;
    }

    virtual std::string toString();
    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
