#ifndef GGAFDX9SE_H_
#define GGAFDX9SE_H_
namespace GgafDx9Core {

// 本プログラムは、<BR>
// 「越後屋Cyber」 http://www.e-cyber.org/ <BR>
// のメンバーのアンダー氏のサンプルプログラムを流用（一部変更）させていただいて、実装しています。<BR>
// 対象クラスは CWaveDecorder です。
// アンダー氏ありがとう！
//                                            2009/01/13 Masatoshi Tsuge<BR>


/**
 * Sound Effect(Wave) クラス .
 */
class GgafDx9Se : public GgafCore::GgafObject {
public:
    /** サウンドバッファ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** waveファイル名 */
    char* _wave_name;

    DWORD _dwDefaultFrequency;

    /**
     * コンストラクタ
     * @param prm_wave_name
     * @return
     */
    GgafDx9Se(char* prm_wave_name);

    /**
     * バッファへWaveデータを転送 .
     * @param WaveFile
     * @return (true:成功 / false:失敗)
     */
    int writeBuffer(CWaveDecorder& WaveFile);

    /**
     * SoundBufferの復帰 .
     * @return 結果 (true:成功 / false:失敗)
     */
    int restore(void);

    /**
     * ボリュームとパンをアクターの位置で計算してSEを再生
     * @param prm_pActor SE発生源アクター
     */
    virtual void play(GgafDx9GeometricActor* prm_pActor);

    /**
     * 一時的にボリュームとパンを指定してSEを再生
     * @param prm_iVolume
     * @param prm_iPan
     */
    virtual void play(int prm_iVolume, int prm_iPan);

    virtual void play() {
        play(DSBPAN_CENTER, DSBPAN_CENTER);
    }


    virtual ~GgafDx9Se();
};

}
#endif /*GGAFDX9SE_H_*/
