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

/** 
 * @file CommandReader.hpp
 * @since   1.0
 * @version 1.0
 * @see
*/

#ifndef __COMMAND_READER_HPP__
#define __COMMAND_READER_HPP__

#include <vector>
#include <string>

// ----------------------------------------------------------------------------

typedef std::vector<std::string> tCommandReaderList;

// ----------------------------------------------------------------------------

/**
 * @class CommandReader
 *
 * @brief Helper class for reading stdin and parsing commands 
 */ 
class CommandReader
{
public:
  CommandReader(void);
  CommandReader(std::string);
  ~CommandReader();

  /** 
    * @brief helper function to compare strings 
    * @param pszToken NULL terminated string token
    * @param pszText NULL terminated string to compare token with
    * @retval returns true if match, false if no match
    */
  static bool startsWith(const char* pszToken, const char* pszText);

  /**
    * @brief read command line from stdin up to 80 characters and stores value to 
    * current command list and current command string
    */
  void readCommandLineFromStdin( );

  /**
    * @brief compares a command string to the current command, 
    * case is compared, length is compared
    * @param pszCommand NULL terminated string to search command
    * @retval true if success, false if unsucessful
    */
  bool isCommand( const char* pszCommand);

  /**
    * @brief compares a command string to the current command, 
    * case is compared, length of input string is compared
    * @param pszCommand NULL terminated string to search command
    * @retval true if success, false if unsucessful
    */
  bool isCommandStartsWith( const char* pszCommand);

  /**
    * @brief compares a command string to the current command, 
    * no case is compared, length is compared
    * @param pszCommand NULL terminated string to search command
    * @retval true if success, false if unsucessful
    */
  bool isCommandNoCase( const char* pszCommand );

  /**
    * @brief compares a command string to the current token, 
    * no case is compared, length of input is compared
    * @param pszCommand NULL terminated string to search command
    * @retval true if success, false if unsucessful
    */
  bool isCommandStartsWithNoCase( const char* pszCommand );

  /**
    * @brief compares a token string to the current token, 
    * case is compared, length is compared
    * @param pszToken NULL terminated string to search token
    * @param iIndex index refenence of token
    * @retval true if success, false if unsucessful
    */
  bool isToken( const char* pszToken, int iIndex = 0 );

  /**
    * @brief compares a token string to the current token, 
    * case is compared, length of input string is compared
    * @param pszToken NULL terminated string to search token
    * @param iIndex index refenence of token
    * @retval true if success, false if unsucessful
    */
  bool isTokenStartsWith( const char* pszToken, int iIndex = 0 );

  /**
    * @brief compares a token string to the current token, 
    * no case is compared, length is compared
    * @param pszToken NULL terminated string to search token
    * @param iIndex index refenence of token
    * @retval true if success, false if unsucessful
    */
  bool isTokenNoCase( const char* pszToken, int iIndex = 0);

  /**
    * @brief compares a token string to the current token, 
    * no case is compared, length of input string is compared
    * @param pszToken NULL terminated string to search token
    * @param iIndex index refenence of token
    * @retval true if success, false if unsucessful
    */
  bool isTokenStartsWithNoCase( const char* pszToken, int iIndex = 0 );

  /**
    * @brief gets command line string
    * @retval returns the current command line string
    */
  std::string getCommandString( );
  
  /**
    * @brief gets token of the command line string
    * @retval returns a token from the command line string
    */
  std::string getTokenString( int iIndex , bool isQuery = false);

  /**
    * @brief returns the number of tokens, including the command token
    * @retval returns the number of tokens from command line input
    */
  int getNumberOfTokens( );

private:
  /**
    * @brief clears current command list and command string
    */
  void clearCommand( );
  
  /**
    * @brief parses a text string delimited by spaces into a vector array
    */
  void parseStringToList( const std::string& sText, tCommandReaderList& commandList );

private:
  tCommandReaderList m_commandList;
  std::string        m_sCommand;
};

// ----------------------------------------------------------------------------

#endif // __COMMAND_READER_HPP__
