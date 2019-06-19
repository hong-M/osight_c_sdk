/*
 * SExxx.h
 *
 *  Created on: 05-09-2017
 *  Author: Zihong Ma
 ***************************************************************************
 *  OSIGHT *
 * www.osighttech.com  *
 ***************************************************************************/

#ifndef SEXXX_H_
#define SEXXX_H_

#include <../include/se_buffer.h>
#include <../include/se_structs.h>
//#include <string>
#include<string.h>
#include<stdint.h>
#include<stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
  undefined = 0,
  initialisation = 1,
  configuration = 2,
  idle = 3,
  rotated = 4,
  in_preparation = 5,
  ready = 6,
  ready_for_measurement = 7
} status_t;

  bool connected_;
  int socket_fd_;

  int run_node(char *vphostPC, int vlPortPC);
  void StartMeasureTransmission();
  void StopMeasureTransmission();
  INT32 GetLidarMeasDataDistance(SCAN_DATA *vpstScanData);


  DATA_HEAD get_data_head();
  USER_PARA_SYNC_RSP_T get_lidar_para();
  INT32 GetLidarData(SCAN_DATA *vpstScanData);

  INT32 se_connect(char* hostPC, int portPC);
  void disconnect();
  bool isConnected();
 INT32 GetLidarMeasData();
  INT32 UserParaSync();
  INT32 PackUserParaSyncReq(USER_PARA_SYNC_REQ_T *vpstUserParaSyncReq, BITS8 *vpucBuff);
  INT32 UnpackUserParaSyncRsp(BITS8 *vpucMsg, USER_PARA_SYNC_RSP_T *vpstUserParaSyncRsp, INT32 lLength);
  INT32 PackStartMeasureTransmissionReq(MEAS_DATA_HEAD_REQ_T *vpstMeasParaReq, BITS8 *vpucBuff);
  INT32 UnpackMeasData(BITS8 *vpucMsg, MEAS_DATA_RSP_T *vpstMeasDataRsp);

  void   send_data (void* vpSrc, BITS16 usCnt);
  INT32 read_data (void* vpSrc, BITS16 usCnt);

#endif /* SEXXX_H_ */
