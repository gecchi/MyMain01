#ifndef MENUBOARD_H_
#define MENUBOARD_H_

namespace MyStg2nd {

/**
 * 本アプリの標準メニューボード .
 * @version 1.00
 * @since 2011/12/26
 * @author Masatoshi Tsuge
 */
class MenuBoard : public GgafLib::DefaultBoardSetMenu {

public:
    coord _slide_from_offset_X;
    coord _slide_from_offset_Y;
    coord _target_X;
    coord _target_Y;

    MenuBoard(const char* prm_name, const char* prm_model);

    void setTargetLocate(coord prm_target_X, coord prm_target_Y,
                         coord prm_slide_from_offset_X, coord prm_slide_from_offset_Y);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    bool condMoveCursorExNext() override;
    bool condMoveCursorExPrev() override;
    bool condMoveCursorCancel() override;
    bool condDecision() override;

    void moveCursor() override;

    void initialize() override;

    void onRisen() override;

    void processBehavior() override;

    void processJudgement() override;

    void onSunk() override;

    virtual ~MenuBoard();
};

}
#endif /*MENUBOARD_H_*/

