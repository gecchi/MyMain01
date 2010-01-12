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

    static const int _DS_MINVOLUME_ = -9600;
    static const int _DS_PAN_LEFT_ = -10000;
    static const int _DS_PAN_RIGHT_ = 10000;

    static int _master_volume;

    //CC3DSoundSE* _pSoundSE;
public:
    /** サウンドバッファ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;
    /** ボリューム(min:-9600 max:0)、デフォルト=0 */
    int _iVolume;
    /** パン (left:-10000 right:10000)、デフォルト=0 */
    int _iPan;
    /** waveファイル名 */
    char* _wave_name;

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
     * 一時的にボリュームとパンを指定してSEを再生
     * @param prm_iVolume
     * @param prm_iPan
     */
    virtual void play(int prm_iVolume, int prm_iPan);


    /**
     * 一時的にボリュームを指定してSEを再生
     */
    void play(int prm_iVolume) {
        play(prm_iVolume, _iPan);
    }

    /**
     * SEを再生
     */
    void play() {
        play(_iVolume, _iPan);
    }

    /**
     * ボリューム設定
     * @param prm_iVolume ボリューム(min:-9600 max:0)
     */
    void setVolume(int prm_iVolume) {
        _iVolume = prm_iVolume;
    }

    /**
     * パン設定
     * @param prm_iPan パン(left:-10000 right:10000)
     */
    void setPan(int prm_iPan) {
        _iPan = prm_iPan;
    }

    /**
     * マスタボリューム設定(現在未実装).
     * TODO:マスターボリューム処理をする！
     * @param prm_master_volume
     */
    static void setMasterVolume(int prm_master_volume) {
        GgafDx9Se::_master_volume = prm_master_volume;
    }

    virtual ~GgafDx9Se();
};

}
#endif /*GGAFDX9SE_H_*/
