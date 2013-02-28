#ifndef SCENEPROGRESS_H_
#define SCENEPROGRESS_H_
namespace GgafLib {

typedef std::map<progress, GgafLib::DefaultScene*> ProgSceneMap;

/**
 * 状態遷移進捗管理(シーン用)クラス .
 * 基底のGgafProgressクラスに、シーンにまつわる便利な機能を追加した
 * シーン専用の状態遷移進捗管理クラスです。
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class SceneProgress : public GgafCore::GgafProgress {

public:
    /** [r]進捗管理対象シーン */
    DefaultScene* _pScene;
    /** [r]進捗番号 対 サブシーン */
    ProgSceneMap _mapProg2Scene;

    progress _progress_next_promise;
    frame _count_next_promise;

public:
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
     * changeWithSceneFlipping(progress)
     * changeWithSceneCrossfading(progress, frame);
     * changeWithSceneOverlapping(progress, frame);
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
     * changeWithSceneFlipping(progress)
     * changeWithSceneCrossfading(progress, frame);
     * changeWithSceneOverlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress 先頭の進捗状態
     * @param prm_EndProgress   末尾の進捗状態
     * @param prm_pFirstSubScene 先頭の進捗状態(prm_FirstProgress)に対応するサブシーン
     */
    void relatSubScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstSubScene);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態にする .
     * 現在の進捗状態に紐付くサブシーンはそのまま（非活動にしません） .
     * ※本メソッドの効果を得るには relatSubScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     */
    void changeWithScene(progress prm_progress);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンに切り替え .
     * 現在の進捗状態に紐付くサブシーンは非活動状態にし、引数の進捗状態に紐付くサブシーンを活動状態にします。
     * ※本メソッドの効果を得るには relatSubScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     */
    void changeWithSceneFlipping(progress prm_progress);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態に切り替え、
     * 活動状態サブシーンは非活動状態にする。その際、フェードアウト・フェードイン効果を行う .
     * ※本メソッドの効果を得るには relatSubScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     * @param prm_cross_fade_frames フェードイン & フェードアウトを行う時間
     */
    void changeWithSceneCrossfading(progress prm_progress, frame prm_cross_fade_frames = 300);

    /**
     * 現進捗状態に紐付くサブシーンはフェードアウト→非活動状態にし、
     * その後直ぐに次の新しい進捗状態に紐付くサブシーンを、フェードイン→活動状態にする。 .
     * ※本メソッドの効果を得るには relatSubScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     * @param prm_fade_out フェードアウト時間
     * @param prm_fade_in フェードイン時間
     */
    void changeWithSceneFadeoutFadein(progress prm_progress, frame prm_fade_out=120, frame prm_fade_in = 120);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いたサブシーンを活動状態に切り替え、
     * 活動状態サブシーンは非活動状態にする。その際、指定フレーム間、同時進行（オーバーラッピング）させる .
     * ※本メソッドの効果を得るには relatSubScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     * @param prm_overlapping_frames 同時進行させるフレーム数
     */
    void changeWithSceneOverlapping(progress prm_progress, frame prm_overlapping_frames);

    /**
     * 現在の進捗状態に関連づいているシーンを取得 .
     * ※本メソッドの効果を得るには relatSubScene() を予め実行し、シーンを関連付ける必要があります。
     * @return
     */
    DefaultScene* getGazedScene();

    /**
     * 進捗状態に関連づいているシーンを取得 .
     * ※本メソッドの効果を得るには relatSubScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 進捗状態
     * @return
     */
    DefaultScene* getScene(progress prm_progress);

    virtual void changeDelay(progress prm_progress, frame prm_delay);
    virtual void update() override;

    /**
     * デストラクタ .
     */
    virtual ~SceneProgress();
};

}
#endif /*SCENEPROGRESS_H_*/
