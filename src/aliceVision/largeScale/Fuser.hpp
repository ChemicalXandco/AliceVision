// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/structures/Point3d.hpp>
#include <aliceVision/structures/StaticVector.hpp>
#include <aliceVision/structures/Universe.hpp>
#include <aliceVision/structures/Voxel.hpp>
#include <aliceVision/common/PreMatchCams.hpp>
#include <aliceVision/depthMap/cuda/PlaneSweepingCuda.hpp>

class Fuser
{
public:
    const multiviewParams* mp;
    mv_prematch_cams* pc;

    Fuser(const multiviewParams* _mp, mv_prematch_cams* _pc);
    ~Fuser(void);

    // minNumOfModals number of other cams including this cam ... minNumOfModals /in 2,3,... default 3
    // pixSizeBall = default 2
    void filterGroups(const StaticVector<int>& cams, int pixSizeBall, int pixSizeBallWSP, int nNearestCams);
    bool filterGroupsRC(int rc, int pixSizeBall, int pixSizeBallWSP, int nNearestCams);
    void filterDepthMaps(const StaticVector<int>& cams, int minNumOfModals, int minNumOfModalsWSP2SSP);
    bool filterDepthMapsRC(int rc, int minNumOfModals, int minNumOfModalsWSP2SSP);

    void divideSpace(Point3d* hexah, float& minPixSize);
    void filterSmallConnComponents(float alpha, int minSegSize, int scale);

    /// @brief Compute average pixel size in the given hexahedron
    float computeAveragePixelSizeInHexahedron(Point3d* hexah, int step, int scale);
    unsigned long computeNumberOfAllPoints(int scale);

    Voxel estimateDimensions(Point3d* vox, Point3d* newSpace, int scale, int maxOcTreeDim);

private:
    bool updateInSurr(int pixSizeBall, int pixSizeBallWSP, Point3d& p, int rc, int tc, StaticVector<int>* numOfPtsMap,
                      StaticVector<float>* depthMap, StaticVector<float>* simMap, int scale);

    Universe* segmentDepthMap(float alpha, int rc, StaticVector<float>* depthMap,int* segMap, int scale);
};

std::string generateTempPtsSimsFiles(std::string tmpDir, multiviewParams* mp, bool addRandomNoise = false,
                                     float percNoisePts = 0.0, int noisPixSizeDistHalfThr = 0);
void deleteTempPtsSimsFiles(multiviewParams* mp, std::string depthMapsPtsSimsTmpDir);
