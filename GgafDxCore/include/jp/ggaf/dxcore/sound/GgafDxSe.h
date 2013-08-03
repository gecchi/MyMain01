#ifndef GGAFDXSE_H_
#define GGAFDXSE_H_
#include "jp/ggaf/core/GgafObject.h"

#include <sstream>
//↑#include <dsound.h> より先に無いと、out__ やらが sal.h により汚染されるため
#ifdef __GNUG__
    //dsound.h 内で、__null 定数を使用したコードあるため
    #define __null
#endif
#include <dsound.h>
#ifdef __GNUG__
    #undef __null
#endif

namespace GgafDxCore {

/**
 * Sound Effect(Wave) クラス .
 */
class GgafDxSe : public GgafCore::GgafObject {

    static std::string getWaveFileName(std::string prm_file);

public:
    /** [r]サウンドバッファ */
    LPDIRECTSOUNDBUFFER _pIDirectSoundBuffer;

    char* _wave_key;

    /** [r]waveファイル名 */
    std::string _wave_file_name;
    /** [r]元の周波数 */
    DWORD _default_frequency;
    /** [r]SEを最後に発生したアクター */
    GgafDxGeometricActor* _pActor_LastPlayed;

    bool _can_looping;
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
     * ボリュームとパンと周波数の率を指定してSEを１回再生 .
     * ボリュームについて、内部でマスタボリュームの考慮が処理されるので、
     * アプリケーション側は、本来の音量を気にせず通常再生したい場合は、
     * ボリュームを100で設定する事。
     * @param prm_volume ボリューム(0 ～ 100)
     * @param prm_pan パン(left:-1.0 ～ center:0 ～ right:1.0)
     * @param prm_frequency 元の周波数に乗ずる率
     */
    virtual void play(int prm_volume, float prm_pan, float prm_frequency);

    /**
     * ボリュームとパンを指定してSEを1回再生
     * ボリュームについて、内部でマスタボリュームの考慮が処理されるので、
     * アプリケーション側は、本来の音量を気にせず通常再生したい場合は、
     * ボリュームを100で設定する事。
     * @param prm_volume ボリューム(0 ～ 100)
     * @param prm_pan    パン(left:-1.0 ～ center:0 ～ right:1.0)
     */
    virtual void play(int prm_volume, float prm_pan) {
        play(prm_volume, prm_pan, 1.0f);
    }

    /**
     * SEを1回再生 .
     */
    virtual void play();

    virtual void stop();

    /**
     * SEが再生中か調べる .
     * @return
     */
    bool isPlaying();

    /**
     * ボリュームを変更 .
     * play()実行後、SEが再生中に音量を変化させるなどに使用することを想定 .
     * 内部でマスタボリュームの考慮が処理される。
     * @param prm_volume ボリューム(0 ～ 100)
     */
    void setVolume(int prm_volume);

    /**
     * パンを変更 .
     * play()実行後、SEが再生中に使用することを想定 .
     * @param prm_pan パン(left:-1.0 ～ center:0 ～ right:1.0)
     */
    void setPan(float prm_pan);


    void setLooping(bool prm_can_looping) {
        _can_looping = prm_can_looping;
    }

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
