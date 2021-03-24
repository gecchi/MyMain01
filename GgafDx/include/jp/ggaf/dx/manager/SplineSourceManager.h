#ifndef GGAF_DX_SPLINEPROGRAMMANAGER_H_
#define GGAF_DX_SPLINEPROGRAMMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {

/**
 * Spline 管理クラス .
 * 生成済み SplineSource オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceManager : public GgafCore::ResourceManager<SplineSource> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    SplineSourceManager(const char* prm_manager_name);

    /**
     * デポジトリを識別文字列から生成。
     * 本アプリのスプライン座標セットはココに集約しようと思っている。
     * @param prm_idstr 識別ID
     * @param prm_p 自由パラメータ（未使用）
     * @return SplineSourceオブジェクト
     */
    virtual SplineSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual GgafCore::ResourceConnection<SplineSource>* processCreateConnection(const char* prm_idstr, SplineSource* prm_pResource) override;

    virtual ~SplineSourceManager() {
    }
};

}
#endif /*GGAF_DX_SPLINEPROGRAMMANAGER_H_*/
