#include <string>
#include <iostream>

#include "CcMeshSim.h"
#include "ml_mesh_type.h"

#include <wrap/io_trimesh/import_obj.h>
#include <wrap/io_trimesh/export.h>


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cerr << "testMeshSim  [Input Mesh(*.obj)]  [Output Mesh(*.obj)]  [Ratio(simplify ratio)]" << std::endl;
		return -1;
	}

	std::string filepath(argv[1]);

	vcg::tri::io::ImporterOBJ<CMeshO>::Info oi;
	oi.cb = NULL;

	CMeshO vcg_mesh;

	int result = vcg::tri::io::ImporterOBJ<CMeshO>::Open(vcg_mesh, filepath.c_str(), oi);
	//if (result != vcg::tri::io::ImporterOBJ<CMeshO>::E_NOERROR)
	//{
	//	std::cerr << "load mesh error" << std::endl;
	//	return -1;
	//}
	std::stringstream ss;
	ss.str(argv[3]);

	CcMeshSim::Settings conf;
	ss >> conf.simRatio;
	conf.simWithTex = false;

	CcMeshSim mesh_sim;
	mesh_sim.setSettings(conf);
	mesh_sim.simplifier(vcg_mesh);

	std::cout << "Simplify mesh over" << std::endl;

	std::string outpath(argv[2]);
	vcg::tri::io::ExporterOBJ<CMeshO>::Save(vcg_mesh, outpath.c_str(), oi.mask);


	return 0;
}