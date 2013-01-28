#ifndef GGAFDXSE_H_
#define GGAFDXSE_H_
namespace GgafDxCore {

/**
 * Sound Effect(Wave) クラス .
 */
class GgafDxSe : public GgafCore::GgafObject {

    static std::string getWaveFileName(std::string prm_file);
public:
    /** サウンドバッファ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** waveファイル名 */
    std::string _wave_file_name;
    /** 元の周波数 */
    DWORD _default_frequency;
    /** [r]最後に発生したアクター */
    GgafDxGeometricActor* _pActor_LastPlayed;

public:
    /**
     * コンストラクタ
     * @param prm_wave_name 識別ID (プロパティファイルのキー)
     * @return
     */
    GgafDxSe(char* prm_wave_key);

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
     * @param prm_volume ボリューム(min:0 max:100)
     * @param prm_pan パン(left:-1.0 center:0 right:1.0)
     * @param prm_frequency 元の周波数に乗ずる率
     */
    virtual void play(int prm_volume, float prm_pan, float prm_frequency);

    /**
     * ボリュームとパンを指定してSEを1回再生
     * @param prm_volume ボリューム(min:0 max:100)
     * @param prm_pan    パン(left:-1.0 center:0 right:1.0)
     */
    virtual void play(int prm_volume, float prm_pan) {
        play(prm_volume, prm_pan, 1.0f);
    }

    /**
     * SEを1回再生 .
     */
    virtual void play();

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
     * @param prm_pan パン(left:-1.0 center:0 right:1.0)
     */
    void setPan(float prm_pan);

    /**
     * 周波数の率を変更 .
     * play()実行後、SEが再生中に使用することを想定 .
     * @param prm_frequency 元の周波数に乗ずる率
     */
    void setFrequencyRate(float prm_frequency);

    virtual ~GgafDxSe();
};

}
#endif /*GGAFDXSE_H_*/
