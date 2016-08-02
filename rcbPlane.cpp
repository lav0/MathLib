#include "stdafx.h"
#include "rcbPlane.h"

//==============================================================================
rcbPlane::rcbPlane(
  const rcbUnitVector3D& a_uvc_norm, 
  const rcbVector3D& a_vc_point_on
)
  : m_uvc_norm(a_uvc_norm)
  , d_free_coef(a_uvc_norm * a_vc_point_on)
{
}

//==============================================================================
bool rcbPlane::intersection(
  const rcbLine3D& a_line, 
  rcbVector3D& a_vc_result
) const
{
  auto na = m_uvc_norm * a_line.get_vector_along();

  if (is_zero_dbl(na))
    return false;

  auto nr = m_uvc_norm * a_line.get_point_on_line();

  a_vc_result = a_line.get_point_by_param( (d_free_coef - nr) / na);

  return true;
}

//==============================================================================
const rcbUnitVector3D& rcbPlane::get_norm() const
{
  return m_uvc_norm;
}

//==============================================================================
double rcbPlane::get_free_coef() const
{ 
  return d_free_coef; 
}
