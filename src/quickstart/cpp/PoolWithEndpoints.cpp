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

/*
 * The PoolWithEndpoints QuickStart Example.
 *
 * This example takes the following steps:
 *
 * 1. Create CacheFactory using the settings from the gfcpp.properties file by
 * default.
 * 2. Create a Geode Cache.
 * 3. Create Poolfactory with endpoint and then create pool using poolfactory.
 * 4. Create a Example Region programmatically.
 * 5. Put Entries (Key and Value pairs) into the Region.
 * 6. Get Entries from the Region.
 * 7. Invalidate an Entry in the Region.
 * 8. Destroy an Entry in the Region.
 * 9. Close the Cache.
 *
 */

// Include the Geode library.
#include <gfcpp/GeodeCppCache.hpp>

// Use the "geode" namespace.
using namespace apache::geode::client;

// The PoolWithEndpoints QuickStart example.
int main(int argc, char** argv) {
  try {
    // Create CacheFactory using the settings from the gfcpp.properties file by
    // default.
    CacheFactoryPtr cacheFactory = CacheFactory::createCacheFactory();

    LOGINFO("Created CacheFactory");

    // Create a Geode Cache.
    CachePtr cachePtr = cacheFactory->setSubscriptionEnabled(true)->create();

    LOGINFO("Created the Geode Cache");

    // Create Poolfactory with endpoint and then create pool using poolfactory.
    PoolFactoryPtr pfact = PoolManager::createFactory();
    pfact->addServer("localhost", 40404);
    PoolPtr pptr = pfact->create("examplePool");

    RegionFactoryPtr regionFactory =
        cachePtr->createRegionFactory(CACHING_PROXY);

    LOGINFO("Created the RegionFactory");

    // Create the example Region programmatically.
    RegionPtr regionPtr =
        regionFactory->setPoolName("examplePool")->create("exampleRegion");

    LOGINFO("Created the Region Programmatically");

    // Put an Entry (Key and Value pair) into the Region using the
    // direct/shortcut method.
    regionPtr->put("Key1", "Value1");

    LOGINFO("Put the first Entry into the Region");

    // Put an Entry into the Region by manually creating a Key and a Value pair.
    CacheableKeyPtr keyPtr = CacheableInt32::create(123);
    CacheablePtr valuePtr = CacheableString::create("123");
    regionPtr->put(keyPtr, valuePtr);

    LOGINFO("Put the second Entry into the Region");

    // Get Entries back out of the Region.
    CacheablePtr result1Ptr = regionPtr->get("Key1");

    LOGINFO("Obtained the first Entry from the Region");

    CacheablePtr result2Ptr = regionPtr->get(keyPtr);

    LOGINFO("Obtained the second Entry from the Region");

    // Invalidate an Entry in the Region.
    regionPtr->invalidate("Key1");

    LOGINFO("Invalidated the first Entry in the Region");

    // Destroy an Entry in the Region.
    regionPtr->destroy(keyPtr);

    LOGINFO("Destroyed the second Entry in the Region");

    // Close the Geode Cache.
    cachePtr->close();

    LOGINFO("Closed the Geode Cache");

    return 0;

  }
  // An exception should not occur
  catch (const Exception& geodeExcp) {
    LOGERROR("PoolWithEndpoints Geode Exception: %s", geodeExcp.getMessage());

    return 1;
  }
}
