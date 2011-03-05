#ifndef GGAFDX9SE_H_
#define GGAFDX9SE_H_
namespace GgafDx9Core {



// 本プログラムは、<BR>
// 「越後屋Cyber」 http://www.e-cyber.org/ <BR>
// のメンバーのアンダー氏のサンプルプログラムのクラスを使用し実装しています。<BR>
// アンダー氏ありがとう！
//
// 対象： CWaveDecorder クラス
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
     * ボリュームとパンと周波数の率を指定してSEを１回再生
     * @param prm_iVolume ボリューム(min:-9600 max:0)
     * @param prm_fPan    パン(left:-10000 right:10000)
     * @param prm_fRate_Frequency 元の周波数に乗ずる率
     */
    virtual void play(int prm_iVolume, float prm_fPan, float prm_fRate_Frequency);

    /**
     * ボリュームとパンを指定してSEを1回再生
     * @param prm_iVolume ボリューム(min:0 max:100)
     * @param prm_fPan    パン(left:-1.0 center:0 right:1.0)
     */
    virtual void play(int prm_iVolume, float prm_fPan) {
        play(prm_iVolume, prm_fPan, 1.0f);
    }

    virtual void play() {
        play(GGAF_MAX_VOLUME, 0.0f);
    }

    bool isPlaying();


    void setVolume(int prm_iVolume);

    void setPan(float prm_fPan);

    void setFrequencyRate(float prm_fRate_Frequency);

    virtual ~GgafDx9Se();
};

}
#endif /*GGAFDX9SE_H_*/
