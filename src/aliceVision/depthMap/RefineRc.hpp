// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/structures/StaticVector.hpp>
#include <aliceVision/depthMap/SemiGlobalMatchingRc.hpp>

class RefineRc : public SemiGlobalMatchingRc
{
public:
    RefineRc(int _rc, int _scale, int _step, SemiGlobalMatchingParams* _sp);
    ~RefineRc(void);

    bool refinercCUDA(bool checkIfExists = true);

    std::string outDir;
    bool _userTcOrPixSize;
    int _wsh;
    float _gammaC;
    float _gammaP;

private:
    int _nSamplesHalf;
    int _ndepthsToRefine;
    float _sigma;
    int _niters;

    DepthSimMap* getDepthPixSizeMapFromSGM();
    DepthSimMap* refineAndFuseDepthSimMapCUDA(DepthSimMap* depthPixSizeMapVis);
    DepthSimMap* optimizeDepthSimMapCUDA(DepthSimMap* depthPixSizeMapVis, DepthSimMap* depthSimMapPhoto);
};

void refineDepthMaps(multiviewParams* mp, mv_prematch_cams* pc, const StaticVector<int>& cams);
void refineDepthMaps(int CUDADeviceNo, multiviewParams* mp, mv_prematch_cams* pc, const StaticVector<int>& cams);
