//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2024 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef FSNODE_FACTORY_HXX
#define FSNODE_FACTORY_HXX

#include <memory>
#include <string> 

class AbstractFSNode;

#if defined(ZIP_SUPPORT)
  #include "FSNodeZIP.hxx"
#endif
#if defined(BSPF_UNIX) || defined(BSPF_MACOS)
  #include "FSNodePOSIX.hxx"
#elif defined(BSPF_WINDOWS)
  #include "FSNodeWINDOWS.hxx"
#elif defined(__LIB_RETRO__)
  #include "FSNodeLIBRETRO.hxx"
#else
  //#error Unsupported platform in FSNodeFactory!
#endif

/**
  This class deals with creating the different FSNode implementations.

  @author  Stephen Anthony
*/
class FSNodeFactory
{
  public:
    enum class Type { SYSTEM, ZIP };

  public:
    static std::unique_ptr<AbstractFSNode> create(std::string_view path, Type type)
    {
      switch(type)
      {
        case Type::SYSTEM:
        #if defined(BSPF_UNIX) || defined(BSPF_MACOS)
          return std::make_unique<FSNodePOSIX>(path);
        #elif defined(BSPF_WINDOWS)
          return std::make_unique<FSNodeWINDOWS>(path);
        #elif defined(__LIB_RETRO__)
          return std::make_unique<FSNodeLIBRETRO>(path);
        #endif
          break;
        case Type::ZIP:
        #if defined(ZIP_SUPPORT)
          return std::make_unique<FSNodeZIP>(path);
        #endif
          break;
      }
      return nullptr;
    }

  private:
    // Following constructors and assignment operators not supported
    FSNodeFactory() = delete;
    FSNodeFactory(const FSNodeFactory&) = delete;
    FSNodeFactory(FSNodeFactory&&) = delete;
    FSNodeFactory& operator=(const FSNodeFactory&) = delete;
    FSNodeFactory& operator=(FSNodeFactory&&) = delete;
};

#endif
