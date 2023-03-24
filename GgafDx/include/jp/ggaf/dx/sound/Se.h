#ifndef GGAF_DX_SE_H_
#define GGAF_DX_SE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <sstream>
#include <windows.h>
//#ifdef __GNUG__
//    #define __null
//    #define NULL    0
//    #define __in
//    #define __out
//#endif
//#include <dsound.h>  //←sal.h を include する
//#ifdef __GNUG__
//    #undef __null
//    #undef __in
//    #undef __out
//#endif

struct IDirectSoundBuffer;

namespace GgafDx {

/**
 * Sound Effect(Wave) クラス .
 */
class Se : public GgafCore::Object {

    static std::string getWaveFileName(std::string prm_file);
    /**
     * バッファへWaveデータを転送 .
     * @param WaveFile
     * @return (true:成功 / false:失敗)
     */
    int writeBuffer(CWaveDecorder& WaveFile);
public:
    /** [r]サウンドバッファ */
    IDirectSoundBuffer* _pIDirectSoundBuffer;

    char* _wave_key;

    /** [r]waveファイル名 */
    std::string _wave_file_name;
    /** [r]元の周波数 */
    DWORD _default_frequency;
    /** [r]SEを最後に発生したアクター */
    GeometricActor* _pActor_last_played;
    /** [r]現在の音量値(0 ～ 1000) */
    int _volume;
    /** [r]現在のパン値(left:-1.0 ～ center:0 ～ right:1.0) */
    float _pan;
    /** [r]現在の周波数の率 */
    float _frequency_rate;

public:
    /**
     * コンストラクタ
     * @param prm_wave_name 識別ID (プロパティファイルのキー)
     * @return
     */
    explicit Se(const char* prm_wave_key);

    /**
     * SoundBufferの復帰 .
     * @return 結果 (true:成功 / false:失敗)
     */
    virtual int restore(void);

    /**
     * SEを再生 .
     * @param prm_is_looping true:ループ再生
     */
    virtual void play(bool prm_is_looping = false);

    virtual void stop();

    /**
     * SEが再生中か調べる .
     * @return
     */
    virtual bool isPlaying();

    /**
     * SEボリュームを変更 .
     * ただし、内部で実際に設定される音量は、BGMマスター音量率が乗じられた値となります。
     * @param prm_volume ボリューム(0 ～ 1000)
     */
    void setVolume(int prm_volume);

    /**
     * SEボリュームを取得 .
     * 取得される音量は、SEマスター音量率が考慮される前の値。
     * つまり、本クラスのsetVolume(int) で設定した値がそのまま取得されます。
     * @return SEのボリューム(0～1000)
     */
    virtual int getVolume() {
        return _volume;
    }

    /**
     * パンを変更 .
     * play()実行後、SEが再生中に使用することを想定 .
     * @param prm_pan パン(left:-1.0 ～ center:0 ～ right:1.0)
     */
    void setPan(float prm_pan);

    virtual int getPan() {
        return _pan;
    }
//    void setLooping(bool prm_can_looping) {
//        _can_looping = prm_can_looping;
//    }

    /**
     * 周波数の率を変更 .
     * play()実行後、SEが再生中に使用することを想定 .
     * @param prm_frequency_rate 元の周波数に乗ずる率
     */
    void setFrequencyRate(float prm_frequency_rate);
    float getFrequencyRate() {
        return _frequency_rate;
    }
    virtual ~Se();
};

}
#endif /*GGAF_DX_SE_H_*/
