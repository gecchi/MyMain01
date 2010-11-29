#ifndef DEFINITESPLINEMANAGER_H_
#define DEFINITESPLINEMANAGER_H_
namespace MyStg2nd {

/**
 * Spline 管理クラス .
 * 生成済み GgafDx9Spline3D オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class Spline3DManager : public GgafCore::GgafResourceManager<GgafDx9Core::GgafDx9Spline3D> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    Spline3DManager(const char* prm_manager_name);

    /**
     * ディスパッチャーを識別文字列から生成。
     * 本アプリのスプライン座標セットはココに集約しようと思っている。
     * @param prm_idstr
     * @return GgafDx9Spline3Dオブジェクト
     */
    GgafDx9Core::GgafDx9Spline3D* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D>* processCreateConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pResource);

    virtual ~Spline3DManager() {
    }
};

}
#endif /*GGAFDX9BGMMANAGER_H_*/
