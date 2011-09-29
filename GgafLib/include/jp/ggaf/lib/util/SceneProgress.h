#ifndef SCENEPROGRESS_H_
#define SCENEPROGRESS_H_
namespace GgafLib {

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
     * changeWithScene_Flipping(progress)
     * changeWithScene_Crossfading(progress, frame);
     * changeWithScene_Overlapping(progress, frame);
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
     * changeWithScene_Flipping(progress)
     * changeWithScene_Crossfading(progress, frame);
     * changeWithScene_Overlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress 先頭の進捗状態
     * @param prm_EndProgress 末尾の進捗状態
     * @param prm_FirstSubSceneName 先頭の進捗状態(prm_FirstProgress)に対応するサブシーン
     */
    void relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態にする .
     * @param prm_progress
     */
    void changeWithScene(progress prm_progress);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態に切り替え、
     * 活動状態サブシーンは非活動状態にする .
     * @param prm_progress 新しい進捗状態
     */
    void changeWithScene_Flipping(progress prm_progress);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態に切り替え、
     * 活動状態サブシーンは非活動状態にする。その際、フェードアウト・フェードイン効果を行う .
     * @param prm_progress 新しい進捗状態
     * @param prm_fade_frames フェードイン・フェードアウトを行う時間
     */
    void changeWithScene_Crossfading(progress prm_progress, frame prm_fade_frames = 300);

    //未実装
    void changeWithScene_FadeoutFadin(progress prm_progress, frame prm_fade_frames = 300);
    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態に切り替え、
     * 活動状態サブシーンは非活動状態にする。その際、指定フレーム間、同時進行（オーバーラッピング）させる .
     * @param prm_progress 新しい進捗状態
     * @param prm_frames 同時進行させるフレーム数
     */
    void changeWithScene_Overlapping(progress prm_progress, frame prm_frames);

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
