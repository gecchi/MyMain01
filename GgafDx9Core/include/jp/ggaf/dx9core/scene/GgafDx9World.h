#ifndef GGAFDX9WORLD_H_
#define GGAFDX9WORLD_H_
namespace GgafDx9Core {


#define MAX_DRAW_DEPTH_LEVEL 1000


class GgafDx9World : public GgafCore::GgafWorld {

public:

	/** カメラ */
	static GgafDx9CameraActor* _pCamera;

	/** アクター順序レンダリングのための遠さのレベルグループ */
    static GgafCore::GgafActor* _apActorDrawDepthLevel_first[];
	/** アクター順序レンダリングのための遠さのレベルグループ別最終アクター */
    static GgafCore::GgafActor* _apActorDrawDepthLevel_last[];


	GgafDx9World(std::string prm_name);


	/**
	 * フレーム毎の描画処理<BR>
	 */
	virtual void drawMain();

	/**
	 * 描画レベル（順序）を登録
	 * @param prm_iDrawDepthLevel レベル
	 * @param prm_pActor アクター
	 */
	static void setDrawDepthLevel(int prm_iDrawDepthLevel, GgafCore::GgafActor* prm_pActor);

	virtual ~GgafDx9World();
};


}
#endif /*GGAFDX9WORLD_H_*/
