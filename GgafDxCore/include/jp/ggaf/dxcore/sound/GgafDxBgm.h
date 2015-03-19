#ifndef GGAFDXCORE_GGAFDXBGM_H_
#define GGAFDXCORE_GGAFDXBGM_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <string>

namespace GgafDxCore {

/**
 * Bgm(Oggフォーマット)クラス .
 */
class GgafDxBgm : public GgafCore::GgafObject {
    static std::string getOggFileName(std::string prm_file);

public:
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

public:
    /**
     * コンストラクタ .
     * プロパティファイルから次のキーの値を取得します。
     * ① prm_bgm_key+"_OGG"      ・・・ 値：BGMとなる oggファイル名
     * ② prm_bgm_key+"_BPM"      ・・・ 値：現在未使用
     * ③ prm_bgm_key+"_TITLE"    ・・・ 値：現在未使用
     * 次に、①のの値をのBGMとなる oggファイルを プロパティファイルの
     * DIR_OGG[0] の設定値配下から探してオープンし、再生準備を行います。
     * @param prm_bgm_key プロパティファイルのkey
     *                    _OGG, _BPM, _TITLE のプレフィックスを指定
     * @return
     */
    explicit GgafDxBgm(const char* prm_bgm_key);

    /**
     * BGM再生 .
     * ボリュームについて、内部でマスタボリュームの考慮が処理される。
     * アプリケーション側は、本来の音量を気にせず通常再生したい場合は、
     * ボリュームを100で設定する事。
     * @param prm_volume 0～100
     * @param prm_pan 左 -1.0 ～ 0 ～ 1.0 右
     * @param prm_is_looping true:ループ再生
     */
    virtual void play(int prm_volume, float prm_pan, bool prm_is_looping);

    /**
     * BGM再生 .
     * ボリュームについて、内部でマスタボリュームの考慮が処理される。
     * アプリケーション側は、本来の音量を気にせず通常再生したい場合は、
     * ボリュームを100で設定する事。
     * @param prm_is_looping true:ループ再生
     */
    virtual void play(bool prm_is_looping);

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
     * 内部でマスタボリュームの考慮が処理される。
     * アプリケーション側は、本来の音量を気にせず通常再生したい場合は、
     * ボリュームを100で設定する事。
     * @param volume 0～100
     */
    virtual void setVolume(int volume);

    /**
     * BGMのパン設定 .
     * @param pan 左 -1.0 ～ 0 ～ 1.0 右
     */
    virtual void setPan(float pan);

    /**
     * 再生スレッドを停止させ、サウンドバッファを解放する .
     */
    virtual void clear();

    /**
     * 再生中かどうかを返す
     * @return
     */
    virtual bool isPlaying();

    virtual ~GgafDxBgm();
};

}
#endif /*GGAFDXCORE_GGAFDXBGM_H_*/
