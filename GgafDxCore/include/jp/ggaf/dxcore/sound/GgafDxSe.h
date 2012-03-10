#ifndef GGAFDXSE_H_
#define GGAFDXSE_H_
namespace GgafDxCore {

/**
 * Sound Effect(Wave) クラス .
 */
class GgafDxSe : public GgafCore::GgafObject {
public:
    /** サウンドバッファ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** waveファイル名 */
    char* _wave_name;
    /** 元の周波数 */
    DWORD _dwDefaultFrequency;

    /**
     * コンストラクタ
     * @param prm_wave_name 識別ID (識別ID + ".wav"で読み込むファイル名になる)
     * @return
     */
    GgafDxSe(char* prm_wave_name);

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
     * @param prm_volume ボリューム(min:-9600 max:0)
     * @param prm_fPan    パン(left:-10000 right:10000)
     * @param prm_fRate_Frequency 元の周波数に乗ずる率
     */
    virtual void play(int prm_volume, float prm_fPan, float prm_fRate_Frequency);

    /**
     * ボリュームとパンを指定してSEを1回再生
     * @param prm_volume ボリューム(min:0 max:100)
     * @param prm_fPan    パン(left:-1.0 center:0 right:1.0)
     */
    virtual void play(int prm_volume, float prm_fPan) {
        play(prm_volume, prm_fPan, 1.0f);
    }

    /**
     * SEを1回再生 .
     */
    virtual void play() {
        play(GGAF_MAX_VOLUME, 0.0f);
    }

    /**
     * SEが再生中か調べる .
     * @return
     */
    bool isPlaying();

    /**
     * ボリュームを変更 .
     * play()実行後、SEが再生中に使用することを想定 .
     * @param prm_volume ボリューム(min:0 max:100)
     */
    void setVolume(int prm_volume);

    /**
     * パンを変更 .
     * play()実行後、SEが再生中に使用することを想定 .
     * @param prm_fPan パン(left:-1.0 center:0 right:1.0)
     */
    void setPan(float prm_fPan);

    /**
     * 周波数の率を変更 .
     * play()実行後、SEが再生中に使用することを想定 .
     * @param prm_fRate_Frequency 元の周波数に乗ずる率
     */
    void setFrequencyRate(float prm_fRate_Frequency);

    virtual ~GgafDxSe();
};

}
#endif /*GGAFDXSE_H_*/
