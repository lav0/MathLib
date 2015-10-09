#include "stdafx.h"
#include "rcbPlaneForScreen.h"



//==============================================================================
rcbPlaneForScreen::rcbPlaneForScreen(
  const rcbUnitVector3D& a_uvc_norm, 
  const rcbUnitVector3D& a_uvc_up_direction,
  const rcbVector3D& a_vc_screen_origin
)
  : rcbPlane(a_uvc_norm, a_vc_screen_origin)
  , m_uvc_up_direction(a_uvc_up_direction)
  , m_vc_screen_origin(a_vc_screen_origin)
//
//
//
{
  _ASSERT(!(m_uvc_up_direction || get_norm())); 
  
  if (!m_uvc_up_direction.is_orthogonal(get_norm())) 
  {
    rcbUnitVector3D uvc_third_ort( m_uvc_up_direction.vector_mul(get_norm()) );
    m_uvc_up_direction = get_norm().vector_mul(uvc_third_ort);
  }  
}


//==============================================================================
rcbVector3D rcbPlaneForScreen::screenToWorld(
  double a_screen_x, 
  double a_screen_y
) const
//
//
//
{
  const rcbUnitVector3D& z_axis = get_norm();
  const rcbUnitVector3D& y_axis = m_uvc_up_direction;
  const rcbUnitVector3D x_axis( y_axis.vector_mul(z_axis) );

  rcbVector3D vc_input(a_screen_x, a_screen_y, 0.0);

  rcbUnitVector3D col1(x_axis.getX(), y_axis.getX(), z_axis.getX());
  rcbUnitVector3D col2(x_axis.getY(), y_axis.getY(), z_axis.getY());
  rcbUnitVector3D col3(x_axis.getZ(), y_axis.getZ(), z_axis.getZ());
  
  return rcbVector3D(
    col1 * vc_input + m_vc_screen_origin.getX(), 
    col2 * vc_input + m_vc_screen_origin.getY(), 
    col3 * vc_input + m_vc_screen_origin.getZ()
  );
}


//==============================================================================