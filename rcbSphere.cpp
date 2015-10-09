#include "stdafx.h"
#include "rcbSphere.h"


//==============================================================================
static bool solve_sphere_plane_plane_system(
  const rcbVector3D& a_sphere_coefs, double R,
  const rcbVector3D& a_line_1_coefs, double d2,
  const rcbVector3D& a_line_2_coefs, double d3,
  rcbVector3D& a_vc_out1,rcbVector3D& a_vc_out2
)
{
  _ASSERT(!(a_line_1_coefs || a_line_2_coefs));
  
  auto a1 = a_sphere_coefs.getX();
  auto b1 = a_sphere_coefs.getY();
  auto c1 = a_sphere_coefs.getZ();
  
  auto a2 = a_line_1_coefs.getX();
  auto b2 = a_line_1_coefs.getY();
  auto c2 = a_line_1_coefs.getZ();
  
  auto a3 = a_line_2_coefs.getX();
  auto b3 = a_line_2_coefs.getY();
  auto c3 = a_line_2_coefs.getZ();

  short components_replaced_count = 0;
  
  auto forward_replace_components = [](double& x, double& y, double& z) 
  {
    auto tmp = z;
    z = y;
    y = x;
    x = tmp;
  };
  auto backward_replace_components = [](double& x, double& y, double& z) 
  {
    auto tmp = x;
    x = y;
    y = z;
    z = tmp;
  };

  while (is_zero_dbl(a2) || is_zero_dbl(b3 * a2 - a3 * b2)) 
  {
    _ASSERT(components_replaced_count < 3);
    forward_replace_components(a1, b1, c1);
    forward_replace_components(a2, b2, c2);
    forward_replace_components(a3, b3, c3);
    ++components_replaced_count;
  }

  const auto ak = a3 / a2;
  const auto bk = (b3 - ak * b2);

  const auto P = (d3 - ak * d2) / bk;
  const auto Q = (c3 - ak * c2) / bk;
  
  const auto U = d2 / a2 - (b2 / a2) * P;
  const auto W = (b2 / a2) * Q - c2 / a2;
  
  const auto A = W*W +Q*Q + 1;
  const auto B = U*W - a1*W - P*Q + b1*Q - c1;
  const auto D = a1*a1 + b1*b1 + c1*c1 - R*R + U*U - 2*a1*U + P*P - 2*b1*P;

  auto discr = B*B - A*D;

  if (discr < 0)
    return false;

  discr = sqrt(discr);

  auto z1 = ( -B + discr) / A;
  auto z2 = ( -B - discr) / A;
  auto x1 = U + W * z1;
  auto x2 = U + W * z2;
  auto y1 = P - Q * z1;
  auto y2 = P - Q * z2;

  while (components_replaced_count-- != 0) 
  {
    backward_replace_components(x1, y1, z1);
    backward_replace_components(x2, y2, z2);
  }

  a_vc_out1 = rcbVector3D(x1, y1, z1);
  a_vc_out2 = rcbVector3D(x2, y2, z2);

  return true;
}



//==============================================================================
//
// Internal member functions
//
//==============================================================================
rcbSphere::rcbSphere(const rcbVector3D& a_vc, double a_rad)
  : m_centre(a_vc)
  , m_radius(a_rad)
{
}

//==============================================================================
bool rcbSphere::intersection(
  const rcbLine3D& a_line, 
  rcbVector3D& a_vc_out1, 
  rcbVector3D& a_vc_out2
) const
//
// true if intersection found
//
{
  const rcbUnitVector3D& uvc = a_line.get_vector_along();

  double x = 1;
  double z = 0;
  double y = 0;

  if (!is_zero_dbl(uvc.getY())) 
  {
    z = 1;
    y = - (uvc.getZ() / uvc.getY()) - uvc.getX();    
  }
  else if (!is_zero_dbl(uvc.getZ())) 
  {
    y = 1;
    z = - (uvc.getY() / uvc.getZ()) - uvc.getX();
  } 
  else if (!is_zero_dbl(uvc.getX())) 
  {
    x = 0;
    y = 1;
    z = 1;
  }  
  else { _ASSERT(0); }
  
  rcbUnitVector3D uvc_aux(x, y, z);
  rcbUnitVector3D uvc_norm1(uvc.vector_mul(uvc_aux));
  rcbUnitVector3D uvc_norm2(uvc_norm1.vector_mul(uvc));
  
  rcbPlane plane1(uvc_norm1, a_line.get_point_on_line());
  rcbPlane plane2(uvc_norm2, a_line.get_point_on_line());

  return solve_sphere_plane_plane_system(
    m_centre, m_radius,
    plane1.get_norm(), plane1.get_free_coef(),
    plane2.get_norm(), plane2.get_free_coef(),
    a_vc_out1, a_vc_out2
  );
}


//==============================================================================
bool rcbSphere::intersection(
  const rcbLine3D& a_line, 
  rcbVector3D& a_vc_out
) const
//
// true if intersection found. gives closest point to rcbLine3D::get_point_on_line()
//
{
  rcbVector3D a_vc_1;
  rcbVector3D a_vc_2;

  if (!intersection(a_line, a_vc_1, a_vc_2))
    return false;

  auto vc_point = a_line.get_point_on_line();

  a_vc_out = (a_vc_1 - vc_point).norm() < (a_vc_2 - vc_point).norm() ?
    a_vc_1 : a_vc_2;

  return true;
}