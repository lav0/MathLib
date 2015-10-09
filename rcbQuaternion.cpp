#include "stdafx.h"
#include "rcbQuaternion.h"


//==============================================================================
//  EXTERNAL OPERATORS 
//==============================================================================
rcbQuaternion operator*(const rcbQuaternion& a_qt, double a)
{
  return rcbQuaternion(a * a_qt.scal_part(), a_qt.vect_part() * a);
}
//==============================================================================
rcbQuaternion operator*(double a, const rcbQuaternion& a_qt)
{
  return a_qt * a;
}
//==============================================================================
rcbQuaternion operator*(const rcbQuaternion& a_qt, const rcbVector3D& a_v)
{
  return a_qt * rcbQuaternion(0, a_v);
}
//==============================================================================
rcbQuaternion operator*(const rcbQuaternion& a_qt_left, const rcbQuaternion& a_qt_right)
{
  rcbVector3D vc(
    a_qt_left.vect_part().vector_mul(a_qt_right.vect_part()) +
    a_qt_left.vect_part() * a_qt_right.scal_part() + 
    a_qt_left.scal_part() * a_qt_right.vect_part()
  );
  double c =  a_qt_left.scal_part() * a_qt_right.scal_part() -
    a_qt_left.vect_part() * a_qt_right.vect_part();

  return rcbQuaternion(c, vc);
}
//===============================================================================
rcbQuaternion operator+(const rcbQuaternion& a_qt_left, const rcbQuaternion& a_qt_right)
{
  return rcbQuaternion(
    a_qt_left.scal_part() + a_qt_right.scal_part(),
    a_qt_left.vect_part() + a_qt_right.vect_part()
  );
}

//===============================================================================
// INTERNAL MUMBER FUNCTIONS
//===============================================================================
rcbQuaternion::rcbQuaternion(double a_c, double a_i, double a_j, double a_k) 
: m_c(a_c), m_v(a_i, a_j, a_k) {}

//===============================================================================
rcbQuaternion::rcbQuaternion(double a_c, const rcbVector3D& a_vc) 
: m_c(a_c), m_v(a_vc) {}

//===============================================================================
rcbQuaternion::rcbQuaternion(const Rotation& a_rotation) {
  m_c = cos(a_rotation.angle() / 2);
  m_v = a_rotation.axis() * sin(a_rotation.angle() / 2);
}

//===============================================================================
double rcbQuaternion::scal_part() const 
{
  return m_c;
}
//===============================================================================
const rcbVector3D& rcbQuaternion::vect_part() const 
{
  return m_v;
}
//===============================================================================
double rcbQuaternion::norm() const {
  return m_c*m_c + m_v.square_norm();
}

//===============================================================================
rcbQuaternion rcbQuaternion::conjugate() const {
  const rcbVector3D& vc_inv(m_v.inverted());
  return rcbQuaternion(m_c, vc_inv.getX(), vc_inv.getY(), vc_inv.getZ());

}
//===============================================================================
rcbQuaternion rcbQuaternion::backward() const {
  if (m_c * m_c < _ZERO && m_v.is_zero_vector()) {
    return rcbQuaternion(0, 0, 0, 0);
  }
  double d_inv_norm = 1 / norm();
  return rcbQuaternion(
    m_c * d_inv_norm, m_v * d_inv_norm
  ).conjugate();
}

//===============================================================================
rcbVector3D rcbQuaternion::turn(const rcbVector3D& a_vc) {
  return ((*this * a_vc) * conjugate()).vect_part();
}

//===============================================================================