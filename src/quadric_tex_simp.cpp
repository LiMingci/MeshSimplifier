

#include "ml_mesh_type.h"   
#include "quadric_tex_simp.h"

using namespace vcg;
using namespace std;
using namespace vcg::tri;

void QuadricTexSimplification(CMeshO &m,int  TargetFaceNum, bool Selected, tri::TriEdgeCollapseQuadricTexParameter &pp, CallBackPos *cb)
{
  tri::UpdateNormal<CMeshO>::PerFace(m);
	math::Quadric<double> QZero;
	QZero.SetZero();
  QuadricTexHelper<CMeshO>::QuadricTemp TD3(m.vert,QZero);
  QuadricTexHelper<CMeshO>::TDp3()=&TD3;

  std::vector<std::pair<vcg::TexCoord2<float>,Quadric5<double> > > qv;

  QuadricTexHelper<CMeshO>::Quadric5Temp TD(m.vert,qv);
  QuadricTexHelper<CMeshO>::TDp()=&TD;

	if(Selected) // simplify only inside selected faces
  {
    // select only the vertices having ALL incident faces selected
    tri::UpdateSelection<CMeshO>::VertexFromFaceStrict(m);
		
    // Mark not writable un-selected vertices
    CMeshO::VertexIterator  vi;
    for(vi=m.vert.begin();vi!=m.vert.end();++vi) if(!(*vi).IsD())
    {
			if(!(*vi).IsS()) (*vi).ClearW();
			else (*vi).SetW();
    }
  }
	
  vcg::LocalOptimization<CMeshO> DeciSession(m,&pp);
	cb(1,"Initializing simplification");
	DeciSession.Init<MyTriEdgeCollapseQTex>();

	if(Selected)
		TargetFaceNum= m.fn - (m.sfn-TargetFaceNum);
	DeciSession.SetTargetSimplices(TargetFaceNum);
	DeciSession.SetTimeBudget(0.1f);
//	int startFn=m.fn;
  
	int faceToDel=m.fn-TargetFaceNum;
	
	while( DeciSession.DoOptimization() && m.fn>TargetFaceNum )
	{
    char buf[256];
    sprintf(buf,"Simplifing heap size %i ops %i\n",int(DeciSession.h.size()),DeciSession.nPerfmormedOps);
	   cb(100-100*(m.fn-TargetFaceNum)/(faceToDel), buf);
	};

	DeciSession.Finalize<MyTriEdgeCollapseQTex>();
	
	if(Selected) // Clear Writable flags 
  {
    CMeshO::VertexIterator  vi;
	for (vi = m.vert.begin(); vi != m.vert.end(); ++vi)
	{
		if (!(*vi).IsD()) (*vi).SetW();
		if ((*vi).IsS()) (*vi).ClearS();
	}
  }
	

}
