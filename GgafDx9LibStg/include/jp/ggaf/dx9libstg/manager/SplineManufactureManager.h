#ifndef SPLINEMANUFACTUREMANAGER_H_
#define SPLINEMANUFACTUREMANAGER_H_
namespace GgafDx9LibStg {

/**
 * Spline 管理クラス .
 * 生成済み SplineManufacture オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureManager : public GgafCore::GgafResourceManager<SplineManufacture> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    SplineManufactureManager(const char* prm_manager_name);

    /**
     * ストアーを識別文字列から生成。
     * 本アプリのスプライン座標セットはココに集約しようと思っている。
     * @param prm_idstr
     * @return SplineManufactureオブジェクト
     */
    SplineManufacture* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<SplineManufacture>* processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource);

    virtual ~SplineManufactureManager() {
    }
};

}
#endif /*SPLINEMANUFACTUREMANAGER_H_*/
