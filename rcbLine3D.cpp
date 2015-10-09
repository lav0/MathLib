#include "stdafx.h"
#include "rcbLine3D.h"


//==============================================================================
rcbLine3D::rcbLine3D(
  const rcbVector3D& a_vc_point_1, 
  const rcbVector3D& a_vc_point_2
) 
  : m_vc_point_on(a_vc_point_1)
  , m_uvc_paral_vector(a_vc_point_2 - a_vc_point_1)
{
}

//==============================================================================
const rcbVector3D& rcbLine3D::get_point_on_line() const
{
  return m_vc_point_on;
}
//==============================================================================
const rcbUnitVector3D& rcbLine3D::get_vector_along() const
{
  return m_uvc_paral_vector;
}
  
//==============================================================================
rcbVector3D rcbLine3D::get_point_by_param(double a_t) const
{
  return m_vc_point_on + m_uvc_paral_vector * a_t;
}

//==============================================================================

