
#ifndef __QUADRICTEXSIMP_H
#define __QUADRICTEXSIMP_H

#include <vcg/complex/algorithms/local_optimization/tri_edge_collapse_quadric_tex.h>

namespace vcg
{
namespace tri
{

typedef BasicVertexPair<CVertexO> VertexPair;

class MyTriEdgeCollapseQTex: public TriEdgeCollapseQuadricTex< CMeshO, VertexPair, MyTriEdgeCollapseQTex, QuadricTexHelper<CMeshO> > {
						public:
            typedef  TriEdgeCollapseQuadricTex< CMeshO,  VertexPair, MyTriEdgeCollapseQTex, QuadricTexHelper<CMeshO> > TECQ;
            inline MyTriEdgeCollapseQTex(  const VertexPair &p, int i,BaseParameterClass *pp) :TECQ(p,i,pp){}
};

} // end namespace tri
} // end namespace vcg

void QuadricTexSimplification(CMeshO &m, int  TargetFaceNum, bool Selected, vcg::tri::TriEdgeCollapseQuadricTexParameter &pp, vcg::CallBackPos *cb);

#endif
