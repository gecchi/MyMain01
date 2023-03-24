#ifndef GGAF_DX_CURVEPROGRAMMANAGER_H_
#define GGAF_DX_CURVEPROGRAMMANAGER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {

/**
 * Curve 管理クラス .
 * 生成済み CurveSource オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveSourceManager : public GgafCore::ResourceManager<CurveSource> {

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    CurveSourceManager(const char* prm_manager_name);

    /**
     * デポジトリを識別文字列から生成。
     * 本アプリのスプライン座標セットはココに集約しようと思っている。
     * @param prm_idstr 識別ID
     * @param prm_p 自由パラメータ（未使用）
     * @return CurveSourceオブジェクト
     */
    virtual CurveSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual GgafCore::ResourceConnection<CurveSource>* processCreateConnection(const char* prm_idstr, CurveSource* prm_pResource) override;

    virtual ~CurveSourceManager() {
    }
};

}
#endif /*GGAF_DX_CURVEPROGRAMMANAGER_H_*/
