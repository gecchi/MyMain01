#ifndef SCENEPROGRESS_H_
#define SCENEPROGRESS_H_
namespace GgafDx9LibStg {

/**
 * 進捗管理(シーン用)クラス .
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class SceneProgress : public GgafCore::GgafProgress {
public:
    /** 進捗管理対象シーン */
    DefaultScene* _pScene;
    /** 進捗番号 対 サブシーン */
    std::map<progress, DefaultScene*> _mapProg2Scene;

    /**
     * コンストラクタ .
     * @param prm_pScene       進捗を管理したい対象シーン
     * @param prm_num_progress 最大進捗番号数(10を設定すると 0番～10番の11個の進捗状態が使用可能となる)
     */
    SceneProgress(DefaultScene* prm_pScene, int prm_num_progress);
    /**
     * 進捗状態とサブシーンを関連付け連動させる.
     * このメソッドにより、関連付けを行うと、以下のメソッドが使用可能（効果あり）となります。<BR>
     * <code>
     * changeWithFlipping(progress)
     * changeWithCrossfading(progress, frame);
     * changeWithOverlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress 先頭の進捗状態
     * @param prm_EndProgress 末尾の進捗状態
     * @param prm_FirstSubSceneName 先頭の進捗状態(prm_FirstProgress)に対応するサブシーンの名称
     */
    void relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstSubSceneName);
    /**
     * 進捗状態とサブシーンを関連付け連動させる.
     * このメソッドにより、関連付けを行うと、以下のメソッドが使用可能（効果あり）となります。<BR>
     * <code>
     * changeWithFlipping(progress)
     * changeWithCrossfading(progress, frame);
     * changeWithOverlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress 先頭の進捗状態
     * @param prm_EndProgress 末尾の進捗状態
     * @param prm_FirstSubSceneName 先頭の進捗状態(prm_FirstProgress)に対応するサブシーン
     */
    void relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene);
    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態に切り替える .
     * 現在の活動状態サブシーンは、非活動状態となる。
     * @param prm_progress 新しい進捗状態
     */
    void changeWithFlipping(progress prm_progress);
    /**
     * 進捗状態を切り替えた後、関連付いたサブシーンをフェードアウト・フェードインを行う .
     * @param prm_progress 新しい進捗状態
     * @param prm_fade_frames フェードイン・フェードアウトを行う時間
     */
    void changeWithCrossfading(progress prm_progress, frame prm_fade_frames = 60);
    /**
     * 進捗状態を切り替えた後、サブシーンはしばらくの間同時進行（オーバーラッピング）させる .
     * @param prm_progress 新しい進捗状態
     * @param prm_frames
     */
    void changeWithOverlapping(progress prm_progress, frame prm_frames);
    /**
     * 現在の進捗状態に関連づいているシーンを取得 .
     * @return
     */
    DefaultScene* getGazeScene();
    /**
     * デストラクタ .
     */
    virtual ~SceneProgress();
};

}
#endif /*SCENEPROGRESS_H_*/
