/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ThinClientPutAllWithCallBack.hpp"

DUNIT_MAIN
  {
    CALL_TASK(CreateServer1);
    CALL_TASK(CreateServer2);

    CALL_TASK(CreateClient1RegionsWithCachingWithConcurrencyCheck);
    CALL_TASK(CreateClient2Regions);

    CALL_TASK(RegisterClient1Keys);
    CALL_TASK(RegisterClient2Keys);

    CALL_TASK(VerifyInitialEntries);
    CALL_TASK(TriggerAfterUpdateEvents);
    CALL_TASK(VerifyUpdatedEntries);
    CALL_TASK(ExecuteLargePutAll);
    CALL_TASK(VerifyLargePutAll);
    CALL_TASK(VerifyRegionService);
    CALL_TASK(InvalidateKeys);
    CALL_TASK(VerifyPutAllWithLongKeyAndStringValue);
    CALL_TASK(VerifyPutAllWithLongKeyAndLongValue);
    CALL_TASK(VerifyPutAllWithObjectKey);

    CALL_TASK(CloseCache1);
    CALL_TASK(CloseCache2);
    CALL_TASK(CloseServer1);
    CALL_TASK(CloseServer2);
  }
END_MAIN
