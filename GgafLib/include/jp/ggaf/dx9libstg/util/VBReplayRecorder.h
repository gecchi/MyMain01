#ifndef VBREPLAYRECORDER_H_
#define VBREPLAYRECORDER_H_
namespace GgafDx9LibStg {

/**
 * リプレイデータクラス .
 * 仮想ボタンステータス(VirtualButton の _state)の、
 * 書き込み読み取り、ファイル書き出し取り込み機能を提供。
 * @version 1.00
 * @since 2010/04/20
 * @author Masatoshi Tsuge
 */
class VBReplayRecorder : public GgafCore::GgafObject {
public:

    /**
     * リプレイデータ要素 .
     */
    class VBRecordNote {
    public:
        /** [r]次のリプレイデータ要素 */
        VBRecordNote* _pNext;
        /** [r]仮想ボタンステータス */
        vbsta _state;
        /** [r]ステータス継続フレーム数 */
        frame _frame_of_keeping;

        /**
         * コンストラクタ .
         */
        VBRecordNote() : _pNext(NULL),_state(0),_frame_of_keeping(0) {
        }

        /**
         * コンストラクタ .
         * @param state 仮想ボタンステータス
         * @param frame_of_keeping ステータス継続フレーム数
         */
        VBRecordNote(vbsta state, frame frame_of_keeping) : _pNext(NULL),_state(state),_frame_of_keeping(frame_of_keeping) {
        }

        virtual ~VBRecordNote() {
        }
    };

    /** [r]リプレイデータ要素リストの先頭要素 */
    VBRecordNote* _pFirstVBNote;
    /** [r]リプレイデータ要素カーソルポインタ */
    VBRecordNote* _pRecNote;
    VBRecordNote* _pRecNote_RreadPrev;
    /** [r]同一ステータス継続フレームカウンタ */
    frame _frame_of_the_same_vbsta_reading;

    /**
     * コンストラクタ .
     */
    VBReplayRecorder();

    /**
     * 内部カーソルを先頭に持ってくる .
     */
    void first();

    /**
     * 仮想ボタンステータス読み込み、内部状態を、次の状態へ遷移 .
     * @return 仮想ボタンステータス
     */
    vbsta read();

    /**
     * 仮想ボタンステータスを書き込み、内部状態を、次の状態へ遷移 .
     * @param state
     */
    void write(vbsta state);

    /**
     * ファイルにリプレイデータを書きだす。
     * @param prm_filename 書きだすファイル名
     */
    void outputFile(const char* prm_filename);

    /**
     * ファイルからリプレイデータを読み込む。
     * @param prm_filename 読み込むファイル名
     * @return true:成功/false:失敗
     */
    bool importFile(const char* prm_filename);

    virtual ~VBReplayRecorder();
};

}
#endif /*FONTSPRITESTRING_H_*/
