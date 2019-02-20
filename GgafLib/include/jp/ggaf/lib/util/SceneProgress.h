#ifndef GGAF_LIB_SCENEPROGRESS_H_
#define GGAF_LIB_SCENEPROGRESS_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/Progress.h"

#include <map>
namespace GgafLib {

typedef std::map<progress, GgafLib::DefaultScene*> ProgSceneMap;

/**
 * 状態遷移進捗管理(シーン用)クラス .
 * 基底のGgafCore::Progressクラスに、シーンにまつわる便利な機能を追加した
 * シーン専用の状態遷移進捗管理クラスです。
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class SceneProgress : public GgafCore::Progress {

public:
    /** [r]進捗管理対象シーン */
    DefaultScene* _pScene;
    /** [r]進捗番号 対 子シーン */
    ProgSceneMap _mapProg2Scene;

    progress _progress_next_promise;
    frame _count_next_promise;

public:
    /**
     * コンストラクタ .
     * @param prm_pScene       進捗を管理したい対象シーン
     */
    SceneProgress(DefaultScene* prm_pScene);

    /**
     * 進捗状態と子シーンを関連付け連動させる.
     * このメソッドにより、関連付けを行うと、以下のメソッドが使用可能（効果あり）となります。<BR>
     * <code>
     * changeWithSceneFlipping(progress)
     * changeWithSceneCrossfading(progress, frame);
     * changeWithSceneOverlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress 先頭の進捗状態
     * @param prm_EndProgress 末尾の進捗状態
     * @param prm_FirstChildSceneName 先頭の進捗状態(prm_FirstProgress)に対応する子シーンの名称
     */
    void relateChildScene(progress prm_FirstProgress, progress prm_EndProgress, const char* prm_FirstChildSceneName);


    /**
     * 進捗状態と子シーンを関連付け連動させる.
     * このメソッドにより、関連付けを行うと、以下のメソッドが使用可能（効果あり）となります。<BR>
     * <code>
     * changeWithSceneFlipping(progress)
     * changeWithSceneCrossfading(progress, frame);
     * changeWithSceneOverlapping(progress, frame);
     * </code>
     * @param prm_FirstProgress 先頭の進捗状態
     * @param prm_EndProgress   末尾の進捗状態
     * @param prm_pFirstChildScene 先頭の進捗状態(prm_FirstProgress)に対応する子シーン
     */
    void relateChildScene(progress prm_FirstProgress, progress prm_EndProgress, DefaultScene* prm_pFirstChildScene);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いた子シーンを活動状態にする .
     * 現在の進捗状態に紐付く子シーンはそのまま（非活動にしません） .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     */
    void changeWithSceneFadein(progress prm_progress, frame prm_fade_in = 120);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いた子シーンに切り替え .
     * 現在の進捗状態に紐付く子シーンは非活動状態にし、引数の進捗状態に紐付く子シーンを活動状態にします。
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     */
    void changeWithSceneFlipping(progress prm_progress);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いた子シーンを活動状態に切り替え .
     * 活動状態子シーンは非活動状態にする際、指定フレーム間同時進行（オーバーラッピング）しながらフェードアウト・フェードイン効果を行う .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     * @param prm_cross_fade_frames フェードイン & フェードアウトを行う時間
     */
    void changeWithSceneCrossfading(progress prm_progress, frame prm_cross_fade_frames = 300);

    /**
     * 現進捗状態に紐付く子シーンはフェードアウト→非活動状態にし、
     * その後直ぐに次の新しい進捗状態に紐付く子シーンを、フェードイン→活動状態にする。 .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     * @param prm_fade_out フェードアウト時間
     * @param prm_fade_in フェードイン時間
     */
    void changeWithSceneFadeoutFadein(progress prm_progress, frame prm_fade_out=120, frame prm_fade_in = 120);

    /**
     * 新しい進捗状態を切り替えると同時に、関連付いた子シーンを活動状態に切り替え、
     * 活動状態子シーンは非活動状態にする。その際、指定フレーム間、同時進行（オーバーラッピング）させる .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 新しい進捗状態
     * @param prm_overlapping_frames 同時進行させるフレーム数
     */
    void changeWithSceneOverlapping(progress prm_progress, frame prm_overlapping_frames);

    /**
     * 現在のアクティブな進捗状態に関連づいているシーンを取得 .
     * 取得できない場合は nullptr
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @return
     */
    DefaultScene* getGazedScene();

    /**
     * 引数の進捗状態に関連づいているシーンを取得 .
     * 取得できない場合は nullptr
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_progress 進捗状態
     * @return
     */
    DefaultScene* getScene(progress prm_progress);

    /**
     * 進捗番号を変更し、changeDelay は無かったことにする .
     * 但し、直後には反映されず update() 時に反映される。
     * PROGRESS_NOTHING(-1) は設定不可。
     * reset(progress) と使い分けること。
     * @param prm_progress 進捗番号(0〜)
     */
    virtual void change(progress prm_progress) override;

    /**
     * 進捗番号を無し PROGRESS_NOTHING(-1) に変更し、changeDelay は無かったことにする .
     * 但し、直後には反映されず update() 時に反映される。
     */
    virtual void changeNothing() override;

    /**
     * 進捗番号を+1し、changeDelay は無かったことにする .
     * 但し、直後には反映されず update() 時に反映される。
     * change(_progress+1) と同じ意味である。
     */
    virtual void changeNext() override;

    /**
     * 進捗番号の変更予約をする。 .
     * @param prm_progress 予約進捗番号(0〜)
     * @param prm_delay 遅延フレーム
     */
    virtual void changeDelay(progress prm_progress, frame prm_delay);
    virtual void update() override;

    /**
     * デストラクタ .
     */
    virtual ~SceneProgress();
};

}
#endif /*GGAF_LIB_SCENEPROGRESS_H_*/
