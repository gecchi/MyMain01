#ifndef GGAF_DX_BGM_H_
#define GGAF_DX_BGM_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <string>

namespace GgafDx {

/**
 * Bgm(Oggフォーマット)クラス .
 */
class Bgm : public GgafCore::Object {
    static std::string getOggFileName(std::string prm_file);

public:
    char* _bgm_key;
//    /** [r]BGM の BMP */
//    int _bpm;
//    /** [r]BGM の タイトル */
//    std::string _title;
    /** [r]BGM の oggファイル名(パス無し) */
    std::string _ogg_file_name;
    /** [r]PCMPlayer */
    IkdLib::PCMPlayer* _pPcmPlayer;
    IkdLib::OggVorbisFile* _pOggResource;
    IkdLib::OggDecoder* _pOggDecoder;
    /** [r]現在の音量値(0 ～ 1000) */
    int _volume;
    /** [r]現在のパン値(left:-1.0 ～ center:0 ～ right:1.0) */
    float _pan;

public:
    /**
     * コンストラクタ .
     * プロパティファイルから次のキーの値を取得します。
     * ① prm_bgm_key         ・・・ 値：BGMとなる oggファイル名
     * ② prm_bgm_key+"_BPM"  ・・・ 値：現在未使用(:TODO)
     * ③ prm_bgm_key+"_TITLE"・・・ 値：現在未使用(:TODO)
     * 次に、①のの値をのBGMとなる oggファイルを プロパティファイルの
     * DIR_BGM[0] の設定値配下から探してオープンし、再生準備を行います。
     * @param prm_bgm_key プロパティファイルのkey
     * @return
     */
    explicit Bgm(const char* prm_bgm_key);


    virtual char* getKeyName() {
        return _bgm_key;
    }

    virtual std::string getFileName() {
        return _ogg_file_name;
    }

    /**
     * BGM再生 .
     * @param prm_is_looping true:ループ再生
     */
    virtual void play(bool prm_is_looping = true);

    /**
     * 一時停止する .
     * 再生中に pause() すると、サウンドバッファが停止されるが、
     * サウンドバッファの頭出は行われ無い。<BR>
     * 一時停止中に pause() しても何も処理されない。<BR>
     * 停止中に pause() しても何も処理されない。<BR>
     */
    virtual void pause();

    /**
     * 一時停止を解除する .
     * 一時停止中に unpause() すると、サウンドバッファが再生される。
     * ループの設定は引き継がれる。<BR>
     * 再生中に unpause() しても何も処理されない。<BR>
     * 停止中に unpause() しても何も処理されない。<BR>
     */
    virtual void unpause();

    /**
     * BGMの停止 .
     * どの様な状態でも、サウンドバッファが停止し、サウンドバッファの頭出しが行われる。
     */
    virtual void stop();

    /**
     * BGMのボリューム設定 .
     * ただし、内部で実際に設定される音量は、BGMマスター音量率が乗じられた値となります。
     * @param volume 0～1000
     */
    void setVolume(int volume);

    /**
     * BGMのボリュームを取得 .
     * 取得される音量は、BGMマスター音量率が考慮される前の値。
     * つまり、本クラスのsetVolume(int) で設定した値がそのまま取得されます。
     * @return BGMのボリューム(0～1000)
     */
    virtual int getVolume() {
        return _volume;
    }

    /**
     * BGMのパン設定 .
     * @param pan 左 -1.0 ～ 0 ～ 1.0 右
     */
    void setPan(float pan);

    virtual int getPan() {
        return _pan;
    }

    /**
     * 再生スレッドを停止させ、サウンドバッファを解放する .
     */
    virtual void clear();

    /**
     * 再生中かどうかを返す
     * @return
     */
    virtual bool isPlaying();

    virtual bool isPause();

    virtual bool isStopping();

    virtual ~Bgm();
};

}
#endif /*GGAF_DX_BGM_H_*/
