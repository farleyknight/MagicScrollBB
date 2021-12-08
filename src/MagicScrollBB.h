#pragma once

#ifdef WIN32
  #define MagicScrollBB_EXPORT __declspec(dllexport)
#else
  #define MagicScrollBB_EXPORT
#endif

MagicScrollBB_EXPORT void MagicScrollBB();
