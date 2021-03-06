#include "stdafx.h"
#include "rcbUnitVector3D.h"


//==============================================================================
//
//
//==============================================================================
rcbUnitVector3D::rcbUnitVector3D(double a_x, double a_y, double a_z)
{
  rcbVector3D vc(a_x, a_y, a_z);

  vc.normalize();

  become(vc.getX(), vc.getY(), vc.getZ());
}

//==============================================================================
rcbUnitVector3D::rcbUnitVector3D(const rcbVector3D& a_vc)
{
  rcbVector3D vc(a_vc);

  vc.normalize();

  become(vc.getX(), vc.getY(), vc.getZ());
}

//==============================================================================
rcbUnitVector3D::rcbUnitVector3D(const rcbUnitVector3D& a_uvc)
  : rcbVector3D(a_uvc.getX(), a_uvc.getY(), a_uvc.getZ())
{
  assert(is_zero_dbl(rcbVector3D::square_norm()-1));
}

//==============================================================================
rcbUnitVector3D::rcbUnitVector3D(rcbUnitVector3D&& a_uvc_rvalue)
  : rcbVector3D(dynamic_cast<rcbVector3D&&>(a_uvc_rvalue))
{
  assert(is_zero_dbl(rcbVector3D::square_norm()-1));
}

//==============================================================================
rcbUnitVector3D::rcbUnitVector3D(rcbVector3D&& a_vc_rvalue)
{
  a_vc_rvalue.normalize();

  rcbVector3D::operator=(a_vc_rvalue);

  assert(is_zero_dbl(rcbVector3D::square_norm()-1));
}

//==============================================================================
rcbUnitVector3D& rcbUnitVector3D::operator=(rcbUnitVector3D&& a_uvc_rvalue)
{
  rcbVector3D::operator=(dynamic_cast<rcbVector3D&&>(a_uvc_rvalue));

  assert(is_zero_dbl(rcbVector3D::square_norm()-1));

  return *this;
}

//==============================================================================
double rcbUnitVector3D::norm() const
{
  assert(is_zero_dbl(rcbVector3D::square_norm()-1));

  return 1.0;
}

//==============================================================================
double rcbUnitVector3D::square_norm() const
{
  assert(is_zero_dbl(rcbVector3D::square_norm()-1));

  return 1.0;
}

//==============================================================================
void rcbUnitVector3D::normalize()
{
  assert(is_zero_dbl(rcbVector3D::square_norm()-1));
}

//==============================================================================
bool rcbUnitVector3D::is_normalized() const
{
  assert(is_zero_dbl(rcbVector3D::square_norm() - 1));

  return true;
}

//==============================================================================
bool rcbUnitVector3D::is_zero_vector() const
{
  assert(is_zero_dbl(rcbVector3D::square_norm()-1));

  return false;
}

//==============================================================================
rcbVector3D rcbUnitVector3D::projectionOnPlane(const rcbVector3D& vc) const
{
    auto axis = vector_mul(vc);

    if (is_zero_dbl(axis.square_norm()))
    {
        return rcbVector3D(0.0, 0.0, 0.0);
    }

    auto uvc_on_plane = rcbUnitVector3D(axis.vector_mul(*this));

    assert(uvc_on_plane.is_normalized());

    auto length = vc.norm();
    auto angle = vc ^ uvc_on_plane;
    auto cosine = cos(angle);

    return uvc_on_plane * cosine * length;

}
//==============================================================================