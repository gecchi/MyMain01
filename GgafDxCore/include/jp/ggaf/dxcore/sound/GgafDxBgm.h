#ifndef GGAFDXBGM_H_
#define GGAFDXBGM_H_
namespace GgafDxCore {

/**
 * Bgm(Oggフォーマット)クラス .
 */
class GgafDxBgm : public GgafCore::GgafObject {
public:
    /** [r]BGM の BMP */
    int _bpm;
    /** [r]BGM の タイトル */
    std::string _title;
    /** [r]BGM の oggファイル名 */
    std::string _ogg_file_name;
    /** [r]PCMPlayer */
    IkdLib::PCMPlayer* _pPcmPlayer;
    IkdLib::OggVorbisFile* _pOggResource;
    IkdLib::OggDecoder* _pOggDecoder;

    /**
     * コンストラクタ .
     * プロパティファイルから次のキーの値を取得します。
     * ① prm_bgm_key+"_OGG"      ・・・ 値：BGMとなる oggファイル名
     * ② prm_bgm_key+"_BPM"      ・・・ 値：現在未使用
     * ③ prm_bgm_key+"_TITLE"    ・・・ 値：現在未使用
     * 次に、①のの値をのBGMとなる oggファイルを プロパティファイルの
     * DIR_OGG の設定値配下から探してオープンし、再生準備を行います。
     * @param prm_bgm_key プロパティファイルのkey
     *                    _OGG, _BPM, _TITLE のプレフィックスを指定
     * @return
     */
    GgafDxBgm(char* prm_bgm_key);

    /**
     * BGM再生 .
     * @param prm_volume 0～100
     * @param prm_pan 左 -1.0 ～ 0 ～ 1.0 右
     * @param prm_is_looping true:ループ再生
     */
    void play(int prm_volume, float prm_pan, bool prm_is_looping);
    /**
     * BGM再生 .
     * @param prm_is_looping true:ループ再生
     */
    void play(bool prm_is_looping) {
        play(GGAF_MAX_VOLUME, 0.0f, prm_is_looping);
    }
    void pause();
    void unpause();
    void stop();
    /**
     * BGMのボリューム設定 .
     * @param volume 0～100
     */
    void setVolume(int volume);
    /**
     * BGMのパン設定 .
     * @param pan 左 -1.0 ～ 0 ～ 1.0 右
     */
    void setPan(float pan);
    void clear();
    bool isActive();

    virtual ~GgafDxBgm();
};

}
#endif /*GGAFDXBGM_H_*/
