#ifndef BACKGROUNDCHIPBOARD_H_
#define BACKGROUNDCHIPBOARD_H_
namespace MyStg2nd {

class BackGroundChipBoard : public GgafDx9LibStg::DefaultBoardSetActor {

public:
    BackGroundChipBoard(const char* prm_name, const char* prm_model);

    virtual ~BackGroundChipBoard();
};

}
#endif /*BACKGROUNDCHIPBOARD_H_*/

