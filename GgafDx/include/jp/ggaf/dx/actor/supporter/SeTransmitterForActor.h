#ifndef GGAF_DX_SETRANSMITTERFORACTOR_H_
#define GGAF_DX_SETRANSMITTERFORACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/sound/SeTransmitter.h"

namespace GgafDx {

/**
 * アクター用サウンドエフェクト出力支援クラス .
 * 簡易3D効果音機能の追加。
 * SeTransmitter から分離
 * @version 1.00
 * @since 2012/03/22
 * @author Masatoshi Tsuge
 */
class SeTransmitterForActor : public SeTransmitter {

private:
    /**
     * 再生中SEのパンとボリュームを更新する。
     */
    void updatePanVolume3D();


public:
    /** [r/w]各SE（配列）の、擬似3D再生かどうかの情報を保持 */
    std::vector<int> _vec_is_playing_3d;
    //0:3D再生していない
    //1:3D再生しているが、音がまだなっていない（遠距離演出の遅延中、サウンドバッファにデータがない）
    //2:3D再生してるし、音が鳴っている。
    frame _playing_3d_freames;
    /** [r]SE発生元アクター */
    GeometricActor* const _pActor;

    /** [r]前回計算時のカメラからアクターの距離 */
    double _px_d_cam_acter_prev;

    static frame _se_delay_max_depth;

public:
    /**
     * コンストラクタ .
     */
    explicit SeTransmitterForActor(GeometricActor* prm_pActor);

    /**
     * SEの設定を行う .
     * SEの再生時間は GGAF_END_DELAY+(最大距離遅延) フレーム以内でなければいけない。
     * チャンネル数は、引数の prm_se_key+"_CH" というプロパティ値が参照される。
     * 存在しない場合、再生チャンネル番号は0固定(∴チャンネル数は1)
     * 設定済みIDに、上書き再設定可能。
     * @param se_no SE登録番号 ( 0 ～ SE数-1 )
     * @param prm_se_key SE定義名（プロパティファイルのキー）
     */
    void set(int prm_se_no, const char* prm_se_key);

    /**
     * SEの設定を行う .
     * 但し、SEの再生時間は GGAF_END_DELAY+(最大距離遅延) フレーム以内でなければいけない。
     * 上書き再設定可能。
     * @param se_no SE登録番号 ( 0 ～ SE数-1 )
     * @param prm_se_key SE定義名（プロパティファイルのキー）
     * @param prm_cannel 再生チャンネル番号
     */
    void set(int prm_se_no, const char* prm_se_key, int prm_cannel) override;

    /**
     * 即座にSEを再生する(擬似３D無し)。
     * @param prm_se_no SE登録番号 ( 0 ～ SE数-1 )
     */
    void play(int prm_se_no, bool prm_can_looping = false) override;

    /**
     * SEの擬似３D再生 .
     * オブジェクトの座標とカメラの座標から、左右のパン。<BR>
     * 距離に応じてのボリューム減少と、遅延再生を行う。<BR>
     * さらに behave() を毎フレーム呼び出しておくと、効果音発声中の移動も擬似３D効果を得る。<BR>
     * @param prm_se_no SE登録番号 ( 0 ～ SE数-1 )
     */
    void play3D(int prm_se_no, bool prm_can_looping = false);

    /**
     * 擬似３D効果再生の毎フレームの処理 .
     * play3D() を使用していないのであれば、呼び出す必要はない。<BR>
     * play3D() を使用し、さらに効果音再生中にアクターが移動し、その移動に伴う３D効果を得たい場合、<BR>
     * 本メソッドを毎フレーム呼び出す必要がある。つまり、再生時間が長い効果音は呼び出したほうが効果的。<BR>
     * SE再生が、再生開始時座標での擬似３D効果のみで良ければ、呼び出す必要はない。<BR>
     * 処理は重めと思うので、大量オブジェクトで呼び出さないように注意が必要<BR>
     * 内部処理は updatePanVolume3D() を呼び出しを数フレーム毎に行っている。<BR>
     */
    void behave();

    /**
     * デストラクタ
     */
    virtual ~SeTransmitterForActor();
};

}
#endif /*GGAF_DX_SETRANSMITTERFORACTOR_H_*/
