#include "stdafx.h"
#include "rcbVector3D.h"


bool is_zero_dbl(double a) { return abs(a) < _ZERO; }
bool is_zero_dbl(double a, double tolerance) { return abs(a) < tolerance; }

//==============================================================================
//  EXTERNAL OPERATORS 
//==============================================================================
rcbVector3D operator*(const rcbVector3D& a_vc, double a_f)
{
  return rcbVector3D(a_vc.getX() * a_f, a_vc.getY() * a_f, a_vc.getZ() * a_f);
}
//==============================================================================
rcbVector3D operator*(double a_f, const rcbVector3D& a_vc)
{
  return a_vc * a_f;
}
//==============================================================================
rcbVector3D operator+(const rcbVector3D& a_vc_left, const rcbVector3D& a_vc_right)
{
  return rcbVector3D(
    a_vc_left.getX() + a_vc_right.getX(),
    a_vc_left.getY() + a_vc_right.getY(),
    a_vc_left.getZ() + a_vc_right.getZ()
  );
}
//==============================================================================
rcbVector3D operator-(const rcbVector3D& a_vc_left, const rcbVector3D& a_vc_right)
{
  return rcbVector3D(
    a_vc_left.getX() - a_vc_right.getX(),
    a_vc_left.getY() - a_vc_right.getY(),
    a_vc_left.getZ() - a_vc_right.getZ()
  );
}
//==============================================================================
double operator*(const rcbVector3D& a_vc_left, const rcbVector3D& a_vc_right)
{
  return a_vc_left.getX() * a_vc_right.getX() +
    a_vc_left.getY() * a_vc_right.getY() +
    a_vc_left.getZ() * a_vc_right.getZ();
}
//==============================================================================
double operator^(const rcbVector3D& a_vc_left, const rcbVector3D& a_vc_right)
{
  if (a_vc_left.is_zero_vector() || a_vc_right.is_zero_vector()) 
    return _2_PI;

  return atan2(
    a_vc_left.vector_mul(a_vc_right).norm(),
    a_vc_left * a_vc_right
  );
}
//==============================================================================
bool operator==(const rcbVector3D& a_vc_left, const rcbVector3D& a_vc_right)
{
  return is_zero_dbl(a_vc_left.getX() - a_vc_right.getX()) &&
         is_zero_dbl(a_vc_left.getY() - a_vc_right.getY()) &&
         is_zero_dbl(a_vc_left.getZ() - a_vc_right.getZ());
}
//==============================================================================
bool operator!=(const rcbVector3D& a_vc_left, const rcbVector3D& a_vc_right)
{
  return !(a_vc_left == a_vc_right);
}

//==============================================================================
bool operator||(const rcbVector3D& a_vc_left, const rcbVector3D& a_vc_right)
{
  return is_zero_dbl(a_vc_left.vector_mul(a_vc_right).norm());
}


//==============================================================================
//  INTERNAL MEMBER FUNCTIONS
//==============================================================================
rcbVector3D::rcbVector3D()
  : m_x(0), m_y(0), m_z(0) {}

//==============================================================================
rcbVector3D::rcbVector3D(double a_x, double a_y, double a_z) 
  : m_x(a_x), m_y(a_y), m_z(a_z) {}


//==============================================================================
rcbVector3D::rcbVector3D(rcbVector3D&& a_vc_rvalue)
  : m_x(std::move(a_vc_rvalue.m_x))
  , m_y(std::move(a_vc_rvalue.m_y))
  , m_z(std::move(a_vc_rvalue.m_z))
{}

//==============================================================================
rcbVector3D& rcbVector3D::operator=(const rcbVector3D& a_vc)
{ 
  m_x = a_vc.m_x;
  m_y = a_vc.m_y;
  m_z = a_vc.m_z;

  return *this;
}

//==============================================================================
rcbVector3D& rcbVector3D::operator=(rcbVector3D&& a_vc_rvalue)
{
  m_x = std::move(a_vc_rvalue.m_x);
  m_y = std::move(a_vc_rvalue.m_y);
  m_z = std::move(a_vc_rvalue.m_z);

  return *this;
}

//==============================================================================
double rcbVector3D::norm() const
{
  return sqrt(square_norm());
}

//==============================================================================
double rcbVector3D::square_norm() const
{
  const rcbVector3D& vc(*this);
  return vc * vc;
}

//==============================================================================
void rcbVector3D::normalize()
{
  auto sq_norm = square_norm();
  
  if (is_zero_dbl(sq_norm, _ZERO_SQ))
  {
    _ASSERT(0);
    become(0, 0, 1);
    return;
  }
  if (is_zero_dbl(sq_norm - 1, _ZERO_SQ)) {
    return;
  }

  double d_inv = 1 / norm();
  become(m_x * d_inv, m_y * d_inv, m_z * d_inv);
}
//==============================================================================
bool rcbVector3D::is_zero_vector() const
{
  return square_norm() < _ZERO;
}

//==============================================================================
void rcbVector3D::become(const double& a_x, const double& a_y, const double& a_z)
{
  m_x = a_x;
  m_y = a_y;
  m_z = a_z;
}

//==============================================================================
void rcbVector3D::become(double&& a_x, double&& a_y, double&& a_z)
{
  m_x = std::move(a_x);
  m_y = std::move(a_y);
  m_z = std::move(a_z);
}

//==============================================================================
rcbVector3D& rcbVector3D::operator+=(const rcbVector3D& a_vc)
{
  become(m_x + a_vc.m_x, m_y + a_vc.m_y, m_z + a_vc.m_z);
  return *this;
}

//==============================================================================
rcbVector3D rcbVector3D::vector_mul(const rcbVector3D& a_vc) const
{
  return rcbVector3D(
    m_y*a_vc.m_z - m_z*a_vc.m_y,
    -m_x*a_vc.m_z + m_z*a_vc.m_x,
    m_x*a_vc.m_y - m_y*a_vc.m_x
  );
}

//==============================================================================
bool rcbVector3D::is_orthogonal(const rcbVector3D& a_vc) const
{
  return is_zero_dbl( *this * a_vc );
}
  

