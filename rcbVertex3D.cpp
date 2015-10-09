#include "stdafx.h"
#include "rcbVertex3D.h"



//==============================================================================
bool unite_vertices(rcbVertex3D* a_vx_left, rcbVertex3D* a_vx_right)
{
  _ASSERT(a_vx_left);
  _ASSERT(a_vx_right);
  _ASSERT(
    a_vx_left->is_linked_to(*a_vx_right) == a_vx_right->is_linked_to(*a_vx_left)
  );

  if (a_vx_left->is_linked_to(*a_vx_right))
    return false;

  a_vx_left->join_vertex(*a_vx_right);
  a_vx_right->join_vertex(*a_vx_left);

  return true;
}


//==============================================================================
rcbVertex3D::rcbVertex3D(const rcbVector3D& a_vc) : rcbVector3D(a_vc) {}

//==============================================================================
rcbVertex3D::rcbVertex3D(double a_x, double a_y, double a_z) 
: rcbVector3D(a_x, a_y, a_z) {}

//==============================================================================
rcbVertex3D& rcbVertex3D::operator=(const rcbVector3D& a_vc)
{
  return dynamic_cast<rcbVertex3D&>(rcbVector3D::operator=(a_vc));
}
//==============================================================================
bool rcbVertex3D::is_linked_to(const rcbVertex3D& a_vx) const
{ 
  return m_links.find(&a_vx) != m_links.end(); 
}

//==============================================================================
void rcbVertex3D::join_vertex(const rcbVertex3D& a_p_vx)
{
  m_links.insert(&a_p_vx);
}