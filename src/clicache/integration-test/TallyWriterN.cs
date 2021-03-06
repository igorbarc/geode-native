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

using System;
using System.Threading;

namespace Apache.Geode.Client.UnitTests
{
  using Apache.Geode.DUnitFramework;
  using Apache.Geode.Client;
  class TallyWriter<TKey, TVal> : CacheWriterAdapter<TKey, TVal>
  {
    #region Private members

    private int m_creates = 0;
    private int m_updates = 0;
    private int m_invalidates = 0;
    private int m_destroys = 0;
    private Object m_callbackArg = null;
    private int m_clears = 0;
    private Object m_lastKey = null;
    private Object m_lastValue = null;
    private bool isWriterFailed = false;
    private bool isWriterInvoke = false;
    private bool isCallbackCalled = false;

    #endregion

    #region Public accessors

    public int Creates
    {
      get
      {
        return m_creates;
      }
    }
    public int Clears
    {
      get
      {
        return m_clears;
      }
    }

    public int Updates
    {
      get
      {
        return m_updates;
      }
    }

    public int Invalidates
    {
      get
      {
        return m_invalidates;
      }
    }

    public int Destroys
    {
      get
      {
        return m_destroys;
      }
    }


    public Object LastKey
    {
      get
      {
        return m_lastKey;
      }
    }

    public Object CallbackArgument
    {
      get
      {
        return m_callbackArg;
      }
    }


    public Object LastValue
    {
      get
      {
        return m_lastValue;
      }
    }

   public void SetWriterFailed( )
   {
    isWriterFailed = true;
   }

  public void SetCallBackArg( object callbackArg )
  {
    m_callbackArg = callbackArg;
  }

  public void ResetWriterInvokation()
  {
    isWriterInvoke = false;
    isCallbackCalled = false;
  }

  public  bool IsWriterInvoked
  {
    get
    {
      return isWriterInvoke;
    }
  }
  public bool IsCallBackArgCalled
  {
    get
    {
      return isCallbackCalled;
    }
  }
    #endregion

    public int ExpectCreates(int expected)
    {
      int tries = 0;
      while ((m_creates < expected) && (tries < 200))
      {
        Thread.Sleep(100);
        tries++;
      }
      return m_creates;
    }

    public int ExpectUpdates(int expected)
    {
      int tries = 0;
      while ((m_updates < expected) && (tries < 200))
      {
        Thread.Sleep(100);
        tries++;
      }
      return m_updates;
    }
    
    public void ShowTallies()
    {
      Util.Log("TallyWriter state: (updates = {0}, creates = {1}, invalidates = {2}, destroys = {3})",
        Updates, Creates, Invalidates, Destroys);
    }

    public void CheckcallbackArg<TKey1, TVal1>(EntryEvent<TKey1, TVal1> ev)
      {
        Util.Log("TallyWriterN: Checking callback arg for EntryEvent " +
          "key:{0} oldval: {1} newval:{2} cbArg:{3} for region:{4} and remoteOrigin:{5}",
          ev.Key, ev.NewValue, ev.OldValue, ev.CallbackArgument, ev.Region.Name, ev.RemoteOrigin);

        if(!isWriterInvoke)
          isWriterInvoke = true;
      /*
        if (m_callbackArg != null)
        {
          IGFSerializable callbkArg1 = ev.CallbackArgument as IGFSerializable;
          IGFSerializable callbkArg2 = m_callbackArg as IGFSerializable;
          if (callbkArg1 != null && callbkArg1.Equals(callbkArg2))
          {
            isCallbackCalled = true;
          }
          string callbkArg3 = ev.CallbackArgument as string;
          string callbkArg4 = m_callbackArg as string;
          if (callbkArg3 != null && callbkArg3.Equals(callbkArg4))
          {
            isCallbackCalled = true;
          }
        }
           * */
        if (m_callbackArg != null && m_callbackArg.Equals(ev.CallbackArgument))
        {
          isCallbackCalled = true;
        }
      }

    public static TallyWriter<TKey, TVal> Create()
    {
      return new TallyWriter<TKey, TVal>();
    }

    #region ICacheWriter Members

    public override bool BeforeCreate(EntryEvent<TKey, TVal> ev)
    {
      m_creates++;
      Util.Log("TallyWriter::BeforeCreate");
      CheckcallbackArg(ev);
      return !isWriterFailed;
    }

    public override bool BeforeDestroy(EntryEvent<TKey, TVal> ev)
    {
      m_destroys++;
      Util.Log("TallyWriter::BeforeDestroy");
      CheckcallbackArg(ev);
      return !isWriterFailed;
    }

    public override bool BeforeRegionClear(RegionEvent<TKey, TVal> ev)
    {
      m_clears++;
      Util.Log("TallyWriter::BeforeRegionClear");
      return true;
    }

    public override bool BeforeUpdate(EntryEvent<TKey, TVal> ev)
    {
      m_updates++;
      Util.Log("TallyWriter::BeforeUpdate");
      CheckcallbackArg(ev);
      return !isWriterFailed;
    }
   #endregion
  }
}
