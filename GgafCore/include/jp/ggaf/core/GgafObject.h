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
    static int _iSeq;

public:
    int _id;
    /** [r]インスタンス種類 */
    UINT32 _obj_class;

    GgafObject();

    /**
     * 識別名取得 .
     * @return 識別名
     */
//    virtual char* getName();

    virtual std::string toString();
    virtual ~GgafObject();
};

}
#endif /*GGAFOBJECT_H_*/
