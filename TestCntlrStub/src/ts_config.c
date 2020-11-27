/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */


/**********************************************************************

     Name:     S1SIM Test Controller Stub 
  
     Type:     C source file
  
     Desc:     This file contains the stub code for configurations. 

     File:     ts_config.c

     Prg:      

**********************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#include "fw_api_int.x"
#include "trfgen.x"
#include "ts_utls.x"

void tsUeConfig(unsigned char ueId, unsigned char *imsi, int imsiLen)
{
   void* msgptr;
   int imsiIdx = 0;

   /* Send UE config msg */
   msgptr = malloc(sizeof(ueConfig_t));
   memset(msgptr, 0, sizeof(ueConfig_t));
   ((ueConfig_t*)msgptr)->ue_id = ueId;
   ((ueConfig_t*)msgptr)->auth_key = 1;
  
   ((ueConfig_t*)msgptr)->imsiLen = imsiLen; 
   for(imsiIdx =0; imsiIdx < imsiLen;imsiIdx++)
   {
      ((ueConfig_t*)msgptr)->imsi[imsiIdx]= imsi[imsiIdx];
   }
   ((ueConfig_t*)msgptr)->imei[0]= 3;
   ((ueConfig_t*)msgptr)->imei[1]= 5;
   ((ueConfig_t*)msgptr)->imei[2]= 3;
   ((ueConfig_t*)msgptr)->imei[3]= 4;
   ((ueConfig_t*)msgptr)->imei[4]= 9;
   ((ueConfig_t*)msgptr)->imei[5]= 0;
   ((ueConfig_t*)msgptr)->imei[6]= 0;
   ((ueConfig_t*)msgptr)->imei[7]= 6;
   ((ueConfig_t*)msgptr)->imei[8]= 9;
   ((ueConfig_t*)msgptr)->imei[9]= 0;
   ((ueConfig_t*)msgptr)->imei[10]= 0;
   ((ueConfig_t*)msgptr)->imei[11]= (ueId / 100) % 10;
   ((ueConfig_t*)msgptr)->imei[12]= (ueId / 10) % 10;
   ((ueConfig_t*)msgptr)->imei[13]= ueId % 10;
   ((ueConfig_t*)msgptr)->imei[14]= 1;
   ((ueConfig_t*)msgptr)->imei[15]= 0;

   printf("\n[STUB]: Sending Ue Config.\n");
   tfwApi(UE_CONFIG, msgptr);
   free(msgptr);

   /* Wait for UE config complete indication */
   if (TC_msg_recv(UE_CONFIG_COMPLETE_IND, 10) == 0)
   {
      printf("\n[Stub] UE %d Config Completed\n", (unsigned char)ueId);
   }
   else
   {
      printf("\n[Stub] UE Config failed\n");
   }
}

void tsUeAppConfig(void)
{
   void* msgptr;

   /* Fill UE App config parameter */
   msgptr = malloc(sizeof(ueAppConfig_t));
   memset(msgptr, 0, sizeof(ueAppConfig_t));
   ((ueAppConfig_t*)msgptr)->nasProcGuardTimer_pr.pres = TRUE;
   ((ueAppConfig_t*)msgptr)->nasProcGuardTimer_pr.nas_proc_guard_timer = 5;

   /* Configure UeApp */
   printf("[Stub] Sending UE App config\n");
   tfwApi(UE_APPL_CONFIG, msgptr);
   free(msgptr);

   /* Wait for UeApp config complete indication */
   if (TC_msg_recv(UE_APP_CONFIG_COMPLETE_IND, 10) == 0)
   {
      printf("\n[Stub] UE APP Config Completed\n");
   }
   else
   {
      printf("\n[Stub] UE APP Config failed\n");
   }
}
