#pragma once

#include "rcbVector3D.h"

class rcbUnitVector3D : public rcbVector3D
{
public:

  rcbUnitVector3D(double a_x, double a_y, double a_z);
  rcbUnitVector3D(const rcbVector3D&);
  rcbUnitVector3D(const rcbUnitVector3D&);
  rcbUnitVector3D(rcbUnitVector3D&&);
  rcbUnitVector3D(rcbVector3D&&);
  
  rcbUnitVector3D& operator=(rcbUnitVector3D&& a_uvc_rvalue);

  void normalize()            override;
  bool is_normalized()  const override;
  bool is_zero_vector() const override;
  
  double norm()        const override;
  double square_norm() const override;

  rcbVector3D projectionOnPlane(const rcbVector3D& vc) const;
  
  static rcbUnitVector3D ort_x() { return rcbUnitVector3D(1.0, 0.0, 0.0); };
  static rcbUnitVector3D ort_y() { return rcbUnitVector3D(0.0, 1.0, 0.0); };
  static rcbUnitVector3D ort_z() { return rcbUnitVector3D(0.0, 0.0, 1.0); };
};