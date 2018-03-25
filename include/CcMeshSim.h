/*!
 * \file CcMeshSim.h
 * \date 2018/03/21 22:48
 *
 * \author LiMingci
 * Contact: mingcich@126.com
 *
 * \brief 对三角网模型进行简化
 *
 * TODO: 采用VCG中提供的简化方法和MeshLab中的数据结构
 *
 * \note
*/
#ifndef CC_MESH_SIM_H
#define CC_MESH_SIM_H

#include "export.h"
class CMeshO;

/*!
 * \class CcMeshSim
 *
 * \brief 三角网模型简化
 *
 * \author LiMingci
 * \date 三月 2018
 */
class MESH_SIM_API CcMeshSim
{
public:
/*!
 * \class Settings
 *
 * \brief 简化参数设置
 *
 * \author LiMingci
 * \date 三月 2018
 */
	struct Settings
	{
		float              simRatio;              //简化比例
		unsigned int       targetFaceNum;         //简化目标
		bool               simWithTex;            //简化时是否考虑纹理

		Settings() : simRatio(0.0f), targetFaceNum(0), simWithTex(false)
		{}
	};

public:
	CcMeshSim();
	~CcMeshSim();

	//简化
	void simplifier(CMeshO& mesh);

	//设置简化参数
	void setSettings(Settings conf) { _settings = conf; }

	//获得简化参数
	Settings& getSettings() { return _settings; }

private:
	void simMesh(CMeshO& mesh);

	void simTexMesh(CMeshO& mesh);

	void beginMakeSure(CMeshO& mesh);

	void endMakeSure(CMeshO& mesh);

private:
	Settings    _settings;


};

#endif // !CC_MESH_SIM_H
