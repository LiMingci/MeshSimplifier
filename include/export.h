#ifndef CC_MESH_SIM_EXPORT_H
#define CC_MESH_SIM_EXPORT_H

#ifdef MAKE_CCMESHSIM_DLL
#define MESH_SIM_API  __declspec(dllexport)
#else
#define MESH_SIM_API  __declspec(dllimport)
#endif // MAKE_CCMESHSIM_DLL

#endif // !CC_MESH_SIM_EXPORT_H
