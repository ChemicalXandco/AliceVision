// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/structures/OrientedPoint.hpp>
#include <aliceVision/structures/Point2d.hpp>
#include <aliceVision/structures/Point3d.hpp>
#include <aliceVision/structures/StaticVector.hpp>
#include <aliceVision/structures/Voxel.hpp>
#include <aliceVision/common/MultiViewParams.hpp>

#include <string>

bool get2dLineImageIntersection(Point2d* pFrom, Point2d* pTo, Point2d linePoint1, Point2d linePoint2,
                                const multiviewParams* mp, int camId);
bool getTarEpipolarDirectedLine(Point2d* pFromTar, Point2d* pToTar, Point2d refpix, int refCam, int tarCam,
                                const multiviewParams* mp);
bool triangulateMatch(Point3d& out, const Point2d& refpix, const Point2d& tarpix, int refCam, int tarCam,
                      const multiviewParams* mp);
bool triangulateMatchLeft(Point3d& out, const Point2d& refpix, const Point2d& tarpix, int refCam, int tarCam,
                          const multiviewParams* mp);
void printfPercent(int i, int n);
long initEstimate();
void printfEstimate(int i, int n, long startTime);
void finishEstimate();
std::string printfElapsedTime(long t1, std::string prefix = "");
void ransac_rsample(int* indexes, int npoints, int npoinsRansac);
// SampleCnt calculates number of samples needed to be done
int ransac_nsamples(int ni, int npoints, int npoinsRansac, float conf);
bool ransacPlaneFit(OrientedPoint& plane, StaticVector<Point3d>* points, StaticVector<Point3d>* points_samples,
                    const multiviewParams* mp, int rc, float pixEpsThr);
bool multimodalRansacPlaneFit(OrientedPoint& plane, StaticVector<StaticVector<Point3d>*>* modalPoints,
                              const multiviewParams* mp, int rc, float pixEpsThr);
float gaussKernelEnergy(OrientedPoint* pt, StaticVector<OrientedPoint*>* pts, float sigma);
int gaussKernelVoting(StaticVector<OrientedPoint*>* pts, float sigma);
float angularDistnace(OrientedPoint* op1, OrientedPoint* op2);
bool arecoincident(OrientedPoint* op1, OrientedPoint* op2, float pixSize);
bool isVisibleInCamera(const multiviewParams* mp, OrientedPoint* op, int rc);
bool isNonVisibleInCamera(const multiviewParams* mp, OrientedPoint* op, int rc);
bool checkPair(const Point3d& p, int rc, int tc, const multiviewParams* mp, float minAng, float maxAng);
bool checkCamPairAngle(int rc, int tc, const multiviewParams* mp, float minAng, float maxAng);
bool isClique(int k, int* perm, unsigned char* confidenceMatrix, int n);
// factorial
int myFact(int num);

void getHexahedronTriangles(Point3d tris[12][3], Point3d hexah[8]);
void getCamRectangleHexahedron(const multiviewParams* mp, Point3d hexah[8], int cam, float mind, float maxd, Point2d P[4]);
void getCamHexahedron(const multiviewParams* mp, Point3d hexah[8], int cam, float mind, float maxd);
bool intersectsHexahedronHexahedron(Point3d rchex[8], Point3d tchex[8]);
StaticVector<Point3d>* lineSegmentHexahedronIntersection(Point3d& linePoint1, Point3d& linePoint2, Point3d hexah[8]);
StaticVector<Point3d>* triangleHexahedronIntersection(Point3d& A, Point3d& B, Point3d& C, Point3d hexah[8]);
StaticVector<Point3d>* triangleRectangleIntersection(Point3d& A, Point3d& B, Point3d& C, const multiviewParams* mp, int rc,
                                                     Point2d P[4]);
bool isPointInHexahedron(const Point3d &p, const Point3d *hexah);
void inflateHexahedron(Point3d hexahIn[8], Point3d hexahOut[8], float scale);
void inflateHexahedronInDim(int dim, Point3d hexahIn[8], Point3d hexahOut[8], float scale);
void inflateHexahedronAroundDim(int dim, Point3d hexahIn[8], Point3d hexahOut[8], float scale);
float similarityKernelVoting(StaticVector<float>* sims);
bool checkPoint3d(Point3d n);
bool checkPoint2d(Point2d n);
StaticVector<int>* getDistinctIndexes(StaticVector<int>* indexes);
StaticVector<StaticVector<int>*>* convertObjectsCamsToCamsObjects(const multiviewParams* mp,
                                                                  StaticVector<StaticVector<int>*>* ptsCams);
StaticVector<StaticVector<Pixel>*>* convertObjectsCamsToCamsObjects(const multiviewParams* mp,
                                                                    StaticVector<StaticVector<Pixel>*>* ptsCams);
int computeStep(multiviewInputParams* mip, int scale, int maxWidth, int maxHeight);

StaticVector<Point3d>* computeVoxels(const Point3d* space, const Voxel& dimensions);
float getCGDepthFromSeeds(const multiviewParams* mp, int rc); // TODO: require seeds vector as input param
StaticVector<int>* createRandomArrayOfIntegers(int n);
float sigmoidfcn(float zeroVal, float endVal, float sigwidth, float sigMid, float xval);
float sigmoid2fcn(float zeroVal, float endVal, float sigwidth, float sigMid, float xval);


int findNSubstrsInString(const std::string& str, const std::string& val);
std::string num2str(int num);
std::string num2str(float num);
std::string num2str(int64_t num);
std::string num2strThreeDigits(int index);
std::string num2strFourDecimal(int index);
std::string num2strTwoDecimal(int index);
