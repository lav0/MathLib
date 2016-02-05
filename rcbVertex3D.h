#pragma once

#include "rcbVector3D.h"
#include <set>

class rcbVertex3D;

bool unite_vertices(rcbVertex3D*, rcbVertex3D*);

//------------------------------------------------------------------------------
class rcbVertex3D : public rcbVector3D
{
  friend bool unite_vertices(rcbVertex3D*, rcbVertex3D*);

public:

  rcbVertex3D(const rcbVector3D& a_vc);
  rcbVertex3D(double a_x, double a_y, double a_z);

  rcbVertex3D& operator=(const rcbVector3D&);

  bool is_linked_to(const rcbVertex3D& a_vx) const;

private:

  void join_vertex(const rcbVertex3D& a_p_vx);

private:

  std::set<const rcbVertex3D*> m_links;
};

typedef std::shared_ptr<rcbVertex3D> rcbVertex3DPtr;
