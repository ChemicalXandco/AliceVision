// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "mv_delaunay_helpers.hpp"
#include "mv_delaunay_types.hpp"

#include <aliceVision/common/MultiViewParams.hpp>


StaticVector<StaticVector<int>*>* getPtsCamsFromInfoFile(const std::string& fileNameInfo)
{
    FILE* f = fopen(fileNameInfo.c_str(), "rb");
    int npts = 0;
    fread(&npts, sizeof(int), 1, f);

    StaticVector<StaticVector<int>*>* out = new StaticVector<StaticVector<int>*>(npts);

    for(int i = 0; i < npts; i++)
    {
        GC_vertexInfo info;
        info.freadinfo(f);
        StaticVector<int>* cams = new StaticVector<int>(info.getNbCameras());
        for(int c = 0; c < info.getNbCameras(); c++)
        {
            cams->push_back(info.cams[c]);
        }

        out->push_back(cams);
    }

    fclose(f);

    return out;
}

StaticVector<int>* getUsedCamsFromInfoFile(const std::string& fileNameInfo, multiviewParams* mp)
{
    FILE* f = fopen(fileNameInfo.c_str(), "rb");
    int npts = 0;
    fread(&npts, sizeof(int), 1, f);

    StaticVector<int>* out = new StaticVector<int>(mp->ncams);

    for(int i = 0; i < npts; i++)
    {
        GC_vertexInfo info;
        info.freadinfo(f);
        for(int c = 0; c < info.getNbCameras(); c++)
        {
            out->push_back_distinct(info.cams[c]);
        }
    }

    fclose(f);

    return out;
}
