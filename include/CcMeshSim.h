/*!
 * \file CcMeshSim.h
 * \date 2018/03/21 22:48
 *
 * \author LiMingci
 * Contact: mingcich@126.com
 *
 * \brief ��������ģ�ͽ��м�
 *
 * TODO: ����VCG���ṩ�ļ򻯷�����MeshLab�е����ݽṹ
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
 * \brief ������ģ�ͼ�
 *
 * \author LiMingci
 * \date ���� 2018
 */
class MESH_SIM_API CcMeshSim
{
public:
/*!
 * \class Settings
 *
 * \brief �򻯲�������
 *
 * \author LiMingci
 * \date ���� 2018
 */
	struct Settings
	{
		float              simRatio;              //�򻯱���
		unsigned int       targetFaceNum;         //��Ŀ��
		bool               simWithTex;            //��ʱ�Ƿ�������

		Settings() : simRatio(0.0f), targetFaceNum(0), simWithTex(false)
		{}
	};

public:
	CcMeshSim();
	~CcMeshSim();

	//��
	void simplifier(CMeshO& mesh);

	//���ü򻯲���
	void setSettings(Settings conf) { _settings = conf; }

	//��ü򻯲���
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
