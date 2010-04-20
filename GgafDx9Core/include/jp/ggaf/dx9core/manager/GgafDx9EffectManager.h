#ifndef GGAFDX9EFFECTMANAGER_H_
#define GGAFDX9EFFECTMANAGER_H_
namespace GgafDx9Core {

/**
 * GgafDx9EffectConnection 管理クラス .
 * 生成済み GgafDx9EffectConnection オブジェクトを登録しておき、使いまわします。
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDx9EffectManager : public GgafCore::GgafResourceManager<GgafDx9Effect> {

public:

    static GgafDx9Effect* _pEffect_Active;

    /**
     * コンストラクタ
     * @param prm_manager_name マネージャ名称(リテラル必須)
     */
    GgafDx9EffectManager(const char* prm_manager_name);

    /**
     * エフェクト識別IDにより、エフェクトブジェクトを生成する .
     * <pre>
     * ＜prm_idstrの形式＞メモ
     * prm_idstrは、
     * 『エフェクトタイプ  + "/" + fxファイル名(拡張子 .fx を除いたもの)』
     * という文字列になっている。エフェクトタイプは以下の通り
     * 'D': GgafDx9MeshEffect オブジェクト
     * 'd': GgafDx9MeshEffect オブジェクト
     * 'X': GgafDx9MeshEffect オブジェクト
     * 'x': GgafDx9MeshSetEffect オブジェクト
     * 'A': GgafDx9D3DXAniMeshEffect オブジェクト
     * 'M': GgafDx9MorphMeshEffect オブジェクト
     * 'S': GgafDx9SpriteEffect オブジェクト
     * 's': GgafDx9SpriteSetEffect オブジェクト
     * 'B': GgafDx9BoardEffect オブジェクト
     * 'b': GgafDx9BoardSetEffect オブジェクト
     *
     * 例："x/LaserChipEffect" の場合。
     * "LaserChipEffect.fx"を読み込む GgafDx9MeshSetEffectインスタンス を返す。
     * </pre>
     * @param prm_idstr エフェクト識別ID
     * @return エフェクトオブジェクト
     */
    GgafDx9Effect* processCreateResource(char* prm_idstr);

    /**
     * オーバーライド
     */
    GgafCore::GgafResourceConnection<GgafDx9Effect>* processCreateConnection(char* prm_idstr, GgafDx9Effect* prm_pResource);


    void restoreAll();

    void onDeviceLostAll();

    virtual ~GgafDx9EffectManager() {
    }
};

}
#endif /*GGAFDX9EFFECTMANAGER_H_*/
