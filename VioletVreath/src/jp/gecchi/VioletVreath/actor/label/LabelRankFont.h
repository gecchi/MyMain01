#ifndef RANKFONT_H_
#define RANKFONT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/FixedFontBoardActor.h"

namespace VioletVreath {

/**
 * �����N�\�� .
 * @version 1.00
 * @since 2011/06/04
 * @author Masatoshi Tsuge
 */
class LabelRankFont : public GgafLib::FixedFontBoardActor {
    static char RANK_1stDeg[][6];
    static char RANK_10thDeg[][5];
    static char RANK_100thDeg[][7];
    static char RANK_1000thDeg[][9];
    static char RANK_10000thDeg[][46];
    static char RANK_INF[];

public:
    enum {
        SE_RANK_UP  ,
    };
    /** [r]�O�t���[����G_RANK_DISP */
    int tmp_rank_;

    GgafDxCore::GgafDxAlphaFader* pAlphaFader_;

public:

    LabelRankFont(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    /**
     * �����N���l���當����ϊ�
     * @param prm_rank �����N���l(1�`100000)
     * @param out ���ʕ����� (char[64]�ȏ�)
     * @return
     */
    void cnvRankStr(int prm_rank, char* out);

    virtual ~LabelRankFont();

};

}
#endif /*RANKFONT_H_*/
