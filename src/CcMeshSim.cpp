
#include <vcg/complex/algorithms/clean.h>

#include "quadric_simp.h"
#include "quadric_tex_simp.h"

#include "CcMeshSim.h"


bool simCallBackPos(const int pos, const char * str)
{
	if (pos == 1)
		std::cout << str << std::endl;
	else
		std::cout << "\r\t" << str << pos << "%";
	return true;
}

CcMeshSim::CcMeshSim()
{
}

CcMeshSim::~CcMeshSim()
{
}

void CcMeshSim::simplifier(CMeshO& mesh)
{
	if (mesh.face.size() == 0) return;

	if (!_settings.simWithTex)
	{
		simMesh(mesh);
	}
	else
	{
		simTexMesh(mesh);
	}
}

void CcMeshSim::simMesh(CMeshO& mesh)
{
	beginMakeSure(mesh);

	int TargetFaceNum = _settings.targetFaceNum;
	if (_settings.simRatio != 0.0f) TargetFaceNum = mesh.fn * _settings.simRatio;

	vcg::tri::TriEdgeCollapseQuadricParameter pp;

	QuadricSimplification(mesh, TargetFaceNum, false, pp, simCallBackPos);

}

void CcMeshSim::simTexMesh(CMeshO& mesh)
{
	beginMakeSure(mesh);

	if (!vcg::tri::HasPerWedgeTexCoord(mesh))
	{
		std::cerr << "Warning: nothing have been done. Mesh has no Texture." << std::endl ;
		return ;
	}
	if (!vcg::tri::Clean<CMeshO>::HasConsistentPerWedgeTexCoord(mesh)) 
	{
		std::cerr << "Mesh has some inconsistent tex coordinates (some faces without texture) << std::endl ";
		return; // can't continue, mesh can't be processed
	}

	int TargetFaceNum = _settings.targetFaceNum;
	if (_settings.simRatio != 0.0f) TargetFaceNum = mesh.fn * _settings.simRatio;

	vcg::tri::TriEdgeCollapseQuadricTexParameter pp;

	QuadricTexSimplification(mesh, TargetFaceNum, false, pp, simCallBackPos);

	endMakeSure(mesh);
}

void CcMeshSim::beginMakeSure(CMeshO& mesh)
{
	mesh.vert.EnableVFAdjacency();
	mesh.face.EnableVFAdjacency();
	vcg::tri::UpdateTopology<CMeshO>::VertexFace(mesh);
	mesh.vert.EnableMark();
	vcg::tri::UpdateFlags<CMeshO>::FaceBorderFromVF(mesh);
}

void CcMeshSim::endMakeSure(CMeshO& mesh)
{
	vcg::tri::UpdateBounding<CMeshO>::Box(mesh);
	if (mesh.fn>0)
	{
		vcg::tri::UpdateNormal<CMeshO>::PerFaceNormalized(mesh);
		vcg::tri::UpdateNormal<CMeshO>::PerVertexAngleWeighted(mesh);
	}
	vcg::tri::UpdateNormal<CMeshO>::NormalizePerFace(mesh);
	vcg::tri::UpdateNormal<CMeshO>::PerVertexFromCurrentFaceNormal(mesh);
	vcg::tri::UpdateNormal<CMeshO>::NormalizePerVertex(mesh);
}