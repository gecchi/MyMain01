#ifndef SPLINEPROGRAMMANAGER_H_
#define SPLINEPROGRAMMANAGER_H_
namespace MyStg2nd {

/**
 * Spline 管理クラス .
 * 生成済み GgafDx9SplineProgram オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineProgramManager : public GgafCore::GgafResourceManager<GgafDx9Core::GgafDx9SplineProgram> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    SplineProgramManager(const char* prm_manager_name);

    /**
     * ディスパッチャーを識別文字列から生成。
     * 本アプリのスプライン座標セットはココに集約しようと思っている。
     * @param prm_idstr
     * @return GgafDx9SplineProgramオブジェクト
     */
    GgafDx9Core::GgafDx9SplineProgram* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9Core::GgafDx9SplineProgram>* processCreateConnection(char* prm_idstr, GgafDx9Core::GgafDx9SplineProgram* prm_pResource);

    virtual ~SplineProgramManager() {
    }
};

}
#endif /*SPLINEPROGRAMMANAGER_H_*/
