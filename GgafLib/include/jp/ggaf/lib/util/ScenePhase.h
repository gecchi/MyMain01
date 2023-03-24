#ifndef GGAF_LIB_SCENEPHASE_H_
#define GGAF_LIB_SCENEPHASE_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/core/Phase.h"

#include <map>
namespace GgafLib {

typedef std::map<int, GgafLib::DefaultScene*> PhaseSceneMap;

/**
 * フェーズ管理(シーン用)クラス .
 * 基底のGgafCore::Phaseクラスに、シーンにまつわる便利な機能を追加した
 * シーン専用のフェーズ管理クラスです。
 * シーンの切り替えに連動して、フェードアウト、フェードイン等が出来ます。
 * @version 1.00
 * @since 2011/07/15
 * @author Masatoshi Tsuge
 */
class ScenePhase : public GgafCore::Phase {

private:
    /** [r]フェーズ管理対象シーン */
    DefaultScene* _pScene;
    /** [r]内部フレームカウンタが _count_next_promise となった場合に切り替わる約束のフェーズ番号 */
    int _phase_no_next_promise;
    /** [r]約束のフレームカウント */
    frame _count_next_promise;
public:
    /** [r]フェーズ番号 対 子シーン */
    PhaseSceneMap _mapPhase2Scene;

public:
    /**
     * コンストラクタ .
     * @param prm_pScene       フェーズを管理したい対象シーン
     */
    ScenePhase(DefaultScene* prm_pScene);

    /**
     * フェーズと子シーンを関連付け連動させる.
     * このメソッドにより、関連付けを行うと、以下のメソッドが使用可能（効果あり）となります。<BR>
     * <code>
     * changeWithSceneFlipping(int)
     * changeWithSceneCrossfading(int, frame);
     * changeWithSceneOverlapping(int, frame);
     * </code>
     * @param prm_FirstPhase 先頭のフェーズ
     * @param prm_EndPhase 末尾のフェーズ
     * @param prm_FirstChildSceneName 先頭のフェーズ(prm_FirstPhase)に対応する子シーンの名称
     */
    void relateChildScene(int prm_FirstPhase, int prm_EndPhase, const char* prm_FirstChildSceneName);

    /**
     * フェーズと子シーンを関連付け連動させる.
     * このメソッドにより、関連付けを行うと、以下のメソッドが使用可能（効果あり）となります。<BR>
     * <code>
     * changeWithSceneFlipping(int)
     * changeWithSceneCrossfading(int, frame);
     * changeWithSceneOverlapping(int, frame);
     * </code>
     * @param prm_FirstPhase 先頭のフェーズ
     * @param prm_EndPhase   末尾のフェーズ
     * @param prm_pFirstChildScene 先頭のフェーズ(prm_FirstPhase)に対応する子シーン
     */
    void relateChildScene(int prm_FirstPhase, int prm_EndPhase, DefaultScene* prm_pFirstChildScene);

    /**
     * 新しいフェーズを切り替えると同時に、関連付いた子シーンを活動状態にする .
     * 現在のフェーズに紐付く子シーンはそのまま（非活動にしません） .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_phase_no 新しいフェーズ
     */
    void changeWithSceneFadein(int prm_phase_no, frame prm_fade_in = 120);

    /**
     * 新しいフェーズを切り替えると同時に、関連付いた子シーンに切り替え .
     * 現在のフェーズに紐付く子シーンは非活動状態にし、引数のフェーズに紐付く子シーンを活動状態にします。
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_phase_no 新しいフェーズ
     */
    void changeWithSceneFlipping(int prm_phase_no);

    /**
     * 新しいフェーズを切り替えると同時に、関連付いた子シーンを活動状態に切り替え .
     * 活動状態子シーンは非活動状態にする際、指定フレーム間同時進行（オーバーラッピング）しながらフェードアウト・フェードイン効果を行う .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_phase_no 新しいフェーズ
     * @param prm_cross_fade_frames フェードイン & フェードアウトを行う時間
     */
    void changeWithSceneCrossfading(int prm_phase_no, frame prm_cross_fade_frames = 300);

    /**
     * 現フェーズに紐付く子シーンはフェードアウト→非活動状態にし、
     * その後直ぐに次の新しいフェーズに紐付く子シーンを、フェードイン→活動状態にする。 .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_phase_no 新しいフェーズ
     * @param prm_fade_out フェードアウト時間
     * @param prm_fade_in フェードイン時間
     */
    void changeWithSceneFadeoutFadein(int prm_phase_no, frame prm_fade_out=120, frame prm_fade_in = 120);

    /**
     * 新しいフェーズを切り替えると同時に、関連付いた子シーンを活動状態に切り替え、
     * 活動状態子シーンは非活動状態にする。その際、指定フレーム間、同時進行（オーバーラッピング）させる .
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_phase_no 新しいフェーズ
     * @param prm_overlapping_frames 同時進行させるフレーム数
     */
    void changeWithSceneOverlapping(int prm_phase_no, frame prm_overlapping_frames);

    /**
     * 現在のアクティブなフェーズに関連づいているシーンを取得 .
     * 取得できない場合は nullptr
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @return
     */
    DefaultScene* getGazedScene();

    /**
     * 引数のフェーズに関連づいているシーンを取得 .
     * 取得できない場合は nullptr
     * ※本メソッドの効果を得るには relateChildScene() を予め実行し、シーンを関連付ける必要があります。
     * @param prm_phase_no フェーズ
     * @return
     */
    DefaultScene* getRelationScene(int prm_phase_no);

    /**
     * フェーズ番号を変更し、changeDelay は無かったことにする .
     * 但し、直後には反映されず update() 時に反映される。
     * GGAF_PHASE_NOTHING(-1) は設定不可。
     * reset(int) と使い分けること。
     * @param prm_phase_no フェーズ番号(0～)
     */
    virtual void change(int prm_phase_no) override;

    /**
     * フェーズ番号を無し GGAF_PHASE_NOTHING(-1) に変更し、changeDelay は無かったことにする .
     * 但し、直後には反映されず update() 時に反映される。
     */
    virtual void changeNothing() override;

    /**
     * フェーズ番号を+1し、changeDelay は無かったことにする .
     * 但し、直後には反映されず update() 時に反映される。
     * change(_phase_no+1) と同じ意味である。
     */
    virtual void changeNext() override;

    /**
     * フェーズ番号の変更予約(約束)をする。 .
     * @param prm_phase_no 予約フェーズ番号(0～)
     * @param prm_delay 遅延フレーム
     */
    virtual void changeDelay(int prm_phase_no, frame prm_delay);

    /**
     * フェーズを次の状態に更新 .
     * 時間カウンターの増加処理等で、この処理をコールしてください。
     */
    virtual void update() override;

    /**
     * デストラクタ .
     */
    virtual ~ScenePhase();
};

}
#endif /*GGAF_LIB_SCENEPHASE_H_*/
