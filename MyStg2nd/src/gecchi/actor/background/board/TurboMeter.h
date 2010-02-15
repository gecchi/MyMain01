#ifndef TRUBOMETER_H_
#define TRUBOMETER_H_
namespace MyStg2nd {

class TruboMeter : public GgafDx9LibStg::DefaultBoardSetActor {

public:
    TruboMeter(const char* prm_name, const char* prm_model);

    virtual ~TruboMeter();
};

}
#endif /*BACKGROUNDCHIPBOARD_H_*/

