#include "stdafx.h"
using namespace std;

using namespace GgafCore;

int GgafRepeatSeq::nowval[10]= {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

int GgafRepeatSeq::getNext(int id) {
    GgafRepeatSeq::nowval[id]++;
    if (GgafRepeatSeq::nowval[id] > id) {
        GgafRepeatSeq::nowval[id] = 0;
    }
    return GgafRepeatSeq::nowval[id];
}
