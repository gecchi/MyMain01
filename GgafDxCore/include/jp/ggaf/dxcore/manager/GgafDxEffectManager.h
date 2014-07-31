#ifndef GGAFDXCORE_GGAFDXEFFECTMANAGER_H_
#define GGAFDXCORE_GGAFDXEFFECTMANAGER_H_
#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"

namespace GgafDxCore {

/**
 * GgafDxEffectConnection 管理クラス .
 * 生成済み GgafDxEffectConnection オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxEffectManager : public GgafCore::GgafResourceManager<GgafDxEffect> {

public:
    static GgafDxEffect* _pEffect_active;

public:
    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDxEffectManager(const char* prm_manager_name);

    /**
     * エフェクト識別IDにより、エフェクトブジェクトを生成する .
     * <pre>
     * ＜prm_idstrの形式＞メモ
     * prm_idstrは、
     * 『エフェクトタイプ  + "/" + fxファイル名(拡張子 .fx を除いたもの)』
     * という文字列になっている。エフェクトタイプは以下の通り
     * 'D': GgafDxMeshEffect オブジェクト
     * 'd': GgafDxMeshEffect オブジェクト
     * 'X': GgafDxMeshEffect オブジェクト
     * 'x': GgafDxMeshSetEffect オブジェクト
     * 'A': GgafDxD3DXAniMeshEffect オブジェクト
     * 'M': GgafDxMorphMeshEffect オブジェクト
     * 'S': GgafDxSpriteEffect オブジェクト
     * 's': GgafDxSpriteSetEffect オブジェクト
     * 'B': GgafDxBoardEffect オブジェクト
     * 'b': GgafDxBoardSetEffect オブジェクト
     *
     * 例："x/LaserChipEffect" の場合。
     * "LaserChipEffect.fx"を読み込む GgafDxMeshSetEffectインスタンス を返す。
     * </pre>
     * @param prm_idstr エフェクト識別ID
     * @param prm_p 自由パラメータ、現在未使用
     * @return エフェクトオブジェクト
     */
    GgafDxEffect* processCreateResource(char* prm_idstr, void* prm_pConnector) override;

    GgafCore::GgafResourceConnection<GgafDxEffect>* processCreateConnection(char* prm_idstr, GgafDxEffect* prm_pResource) override;

    void setParamPerFrameAll();

    void restoreAll();

    void onDeviceLostAll();

    virtual ~GgafDxEffectManager() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXEFFECTMANAGER_H_*/
