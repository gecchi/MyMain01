#ifndef SPLINE3DMANAGER_H_
#define SPLINE3DMANAGER_H_
namespace MyStg2nd {

/**
 * Spline 管理クラス .
 * 生成済み Spline3D オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class Spline3DManager : public GgafCore::GgafResourceManager<GgafDx9Core::Spline3D> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    Spline3DManager(const char* prm_manager_name);

    GgafDx9Core::Spline3D* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9Core::Spline3D>* processCreateConnection(char* prm_idstr, GgafDx9Core::Spline3D* prm_pResource);


    virtual ~Spline3DManager() {
    }
};

}
#endif /*SPLINE3DMANAGER_H_*/
