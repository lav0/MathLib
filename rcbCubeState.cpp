#include "stdafx.h"
#include "rcbCubeState.h"

//==============================================================================
bool operator==(eTurnAxis a_e_axis, eCubeSide a_e_side)
{
  switch (a_e_axis) {
  case TA_X: return a_e_side == CS_FRONT || a_e_side == CS_BACK;
  case TA_Y: return a_e_side == CS_RIGHT || a_e_side == CS_LEFT;
  case TA_Z: return a_e_side == CS_DOWN  || a_e_side == CS_UP;
  };
  _ASSERT(0);
  return false;
}
//==============================================================================
eCubeSide opposite(eCubeSide a_e_side)
{
  switch (a_e_side) {
  case CS_DOWN : return CS_UP;
  case CS_UP   : return CS_DOWN;
  case CS_BACK : return CS_FRONT;
  case CS_FRONT: return CS_BACK;
  case CS_RIGHT: return CS_LEFT;
  case CS_LEFT : return CS_RIGHT;
  };
  _ASSERT(0);
  return CS_UP;
}

//==============================================================================
eCubeSide turn_rules(eCubeSide a_side, eTurnAxis a_axis, eAngle a_angle)
{
  if (a_axis == a_side) 
    return a_side;

  if (a_angle == A_180)
    return opposite(a_side);
  else if (a_angle == A_270)
    return opposite(turn_rules(a_side, a_axis, A_90));

  switch (a_side) {
  case CS_UP:
    if (a_axis == TA_X)      return CS_LEFT;
    else if (a_axis == TA_Y) return CS_FRONT;
    else                     _ASSERT(0);

  case CS_DOWN:
    if (a_axis == TA_X)      return CS_RIGHT;
    else if (a_axis == TA_Y) return CS_BACK;
    else                     _ASSERT(0);

  case CS_FRONT:
    if (a_axis == TA_Y)      return CS_DOWN;
    else if (a_axis == TA_Z) return CS_RIGHT;
    else                     _ASSERT(0);

  case CS_BACK:
    if (a_axis == TA_Y)      return CS_UP;
    else if (a_axis == TA_Z) return CS_LEFT;
    else                     _ASSERT(0);

  case CS_RIGHT:
    if (a_axis == TA_X)      return CS_UP;
    else if (a_axis == TA_Z) return CS_BACK;
    else                     _ASSERT(0);

  case CS_LEFT:
    if (a_axis == TA_X)      return CS_DOWN;
    else if (a_axis == TA_Z) return CS_FRONT;
    else                     _ASSERT(0);
  };

  _ASSERT(0);
  return CS_DOWN;
}

//==============================================================================
rcbCubeState::rcbCubeState()
: m_z_side(CS_UP), m_x_side(CS_FRONT) {}

//==============================================================================
rcbCubeState::rcbCubeState(eCubeSide a_z, eCubeSide a_x)
: m_z_side(a_z), m_x_side(a_x) {}

//==============================================================================
void rcbCubeState::turn(eTurnAxis a_e_axis, eAngle a_e_angle)
{
  m_z_side = turn_rules(m_z_side, a_e_axis, a_e_angle);
  m_x_side = turn_rules(m_x_side, a_e_axis, a_e_angle);
}

//==============================================================================



//==============================================================================
//  rcbCubePosition further
//==============================================================================
rcbCubePosition::rcbCubePosition(Dimention size, Dimention x, Dimention y, Dimention z)
  : m_size(size)
  , m_pos_x(x)
  , m_pos_y(y)
  , m_pos_z(z)
{
}

//==============================================================================
void rcbCubePosition::turn(eTurnAxis a_e_axis, eAngle a_e_angle)
{
  if (a_e_angle == A_180)
  {
    turn(a_e_axis, A_90);
    turn(a_e_axis, A_90);
    return;
  } else if (a_e_angle == A_270)
  {
    turn(a_e_axis, A_180);
    turn(a_e_axis, A_90);
    return;
  }
  
  _ASSERT(a_e_angle == A_90);
    
  if (a_e_axis == TA_X)
  {
    Dimention tmp = m_pos_z;
    m_pos_z = m_pos_y;
    m_pos_y = m_size - tmp;    
  }
  else if (a_e_axis == TA_Y)
  {
    Dimention tmp = m_pos_x;
    m_pos_x = m_pos_z;
    m_pos_z = m_size - tmp;
  }
  else if (a_e_axis == TA_Z)
  {
    Dimention tmp = m_pos_y;
    m_pos_y = m_pos_x;
    m_pos_x = m_size - tmp;
  }
  
}

//==============================================================================