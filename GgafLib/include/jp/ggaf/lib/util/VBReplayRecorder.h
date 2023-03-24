#ifndef GGAF_LIB_VBREPLAYRECORDER_H_
#define GGAF_LIB_VBREPLAYRECORDER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"

#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include <fstream>

namespace GgafLib {

/**
 * リプレイデータクラス .
 * 仮想ボタンステータス(VirtualButton の _state)の、
 * 書き込み読み取り、ファイル書き出し取り込み機能を提供。
 * @version 1.00
 * @since 2010/04/20
 * @author Masatoshi Tsuge
 */
class VBReplayRecorder : public GgafCore::Object {

public:
    /**
     * リプレイデータ要素 .
     */
    class VBRecordNote {
    public:
        /** [r]次のリプレイデータ要素 */
        VBRecordNote* _pNext;
        /** [r]仮想ボタンステータス */
        vb_sta _state;
        /** [r]ステータス継続フレーム数 */
        frame _frame_of_keeping;
    public:
        /**
         * コンストラクタ .
         */
        VBRecordNote() : _pNext(nullptr),_state(0),_frame_of_keeping(0) {
        }

        /**
         * コンストラクタ .
         * @param state 仮想ボタンステータス
         * @param frame_of_keeping ステータス継続フレーム数
         */
        VBRecordNote(vb_sta state, frame frame_of_keeping) : _pNext(nullptr),_state(state),_frame_of_keeping(frame_of_keeping) {
        }

        ~VBRecordNote() {
        }
    };

    /** [r]リプレイデータ要素リストの先頭要素 */
    VBRecordNote* _pFirstVBNote;
    /** [r]リプレイデータ要素カーソルポインタ */
    VBRecordNote* _pRecNote;
    VBRecordNote* _pRecNote_read_prev;
    /** [r]同一ステータス継続フレームカウンタ */
    frame _frame_of_the_same_vb_sta_reading;

    std::ofstream _ofs_realtime;

    bool _write_realtime;

public:
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
    vb_sta read();

    /**
     * 読み込むレコードが存在するかどうか
     * @return true:存在する／false:存在しない
     */
    bool hasNextRecord() {
        return _pRecNote ? true : false;
    }
    /**
     * リアルタイム記述モードをオンにする(主にデバッグ用) .
     * write(vb_sta) 実行の度に、リアルタイムでファイルに情報を記述していきます。
     * @param prm_filename リアルタイムに書きだすファイル名
     * @return
     */
    bool setRealtimeOutputFile(const char* prm_filename);
    /**
     * 仮想ボタンステータスを書き込み、内部状態を、次の状態へ遷移 .
     * @param state
     */
    void write(vb_sta state);

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
#endif /*GGAF_LIB_FONTSPRITESTRING_H_*/
