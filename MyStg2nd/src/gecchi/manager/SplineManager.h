#ifndef SPLINEPROGRAMMANAGER_H_
#define SPLINEPROGRAMMANAGER_H_
namespace MyStg2nd {

/**
 * Spline 管理クラス .
 * 生成済み SplineSource オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManager : public GgafCore::GgafResourceManager<SplineSource> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    SplineManager(const char* prm_manager_name);

    /**
     * ストアーを識別文字列から生成。
     * 本アプリのスプライン座標セットはココに集約しようと思っている。
     * @param prm_idstr
     * @return SplineSourceオブジェクト
     */
    SplineSource* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<SplineSource>* processCreateConnection(char* prm_idstr, SplineSource* prm_pResource);

    virtual ~SplineManager() {
    }
};

}
#endif /*SPLINEPROGRAMMANAGER_H_*/
