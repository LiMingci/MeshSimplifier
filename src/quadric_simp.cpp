
#include "ml_mesh_type.h"
#include "quadric_simp.h"

using namespace vcg;
using namespace std;

void QuadricSimplification(CMeshO &m,int  TargetFaceNum, bool Selected, tri::TriEdgeCollapseQuadricParameter &pp, CallBackPos *cb)
{
  math::Quadric<double> QZero;
  QZero.SetZero();
  tri::QuadricTemp TD(m.vert,QZero);
  tri::QHelper::TDp()=&TD;

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

  if(pp.PreserveBoundary && !Selected) 
	{
    pp.FastPreserveBoundary=true;
		pp.PreserveBoundary = false;
	}
		
  if(pp.NormalCheck) pp.NormalThrRad = M_PI/4.0;
	
	
  vcg::LocalOptimization<CMeshO> DeciSession(m,&pp);
	cb(1,"Initializing simplification");
	DeciSession.Init<tri::MyTriEdgeCollapse >();

	if(Selected)
		TargetFaceNum= m.fn - (m.sfn-TargetFaceNum);
	DeciSession.SetTargetSimplices(TargetFaceNum);
	DeciSession.SetTimeBudget(0.05f); // this allow to update the progress bar 10 time for sec...
//  if(TargetError< numeric_limits<double>::max() ) DeciSession.SetTargetMetric(TargetError);
  //int startFn=m.fn;
  int faceToDel=m.fn-TargetFaceNum;
 while( DeciSession.DoOptimization() && m.fn>TargetFaceNum )
 {
   cb(100-100*(m.fn-TargetFaceNum)/(faceToDel), "Simplifying...");
 };

	DeciSession.Finalize<tri::MyTriEdgeCollapse >();
  
  if(Selected) // Clear Writable flags 
  {
    CMeshO::VertexIterator  vi;
    for(vi=m.vert.begin();vi!=m.vert.end();++vi) 
	{
      if (!(*vi).IsD()) (*vi).SetW();
	  if ((*vi).IsS()) (*vi).ClearS();
	}
  }
}
