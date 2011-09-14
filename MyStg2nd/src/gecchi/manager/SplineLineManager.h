#ifndef SPLINELINEMANAGER_H_
#define SPLINELINEMANAGER_H_
namespace MyStg2nd {

/**
 * Spline 管理クラス .
 * 生成済み SplineLine オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineLineManager : public GgafCore::GgafResourceManager<GgafDx9LibStg::SplineLine> {

public:

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    SplineLineManager(const char* prm_manager_name);

    GgafDx9LibStg::SplineLine* processCreateResource(char* prm_idstr, void* prm_p);

    GgafCore::GgafResourceConnection<GgafDx9LibStg::SplineLine>* processCreateConnection(char* prm_idstr, GgafDx9LibStg::SplineLine* prm_pResource);


    virtual ~SplineLineManager() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/
