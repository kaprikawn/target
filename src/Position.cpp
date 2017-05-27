#include "Position.hpp"
#include <iostream>

Position::Position( int width, int height, int hb_left_adjust, int hb_right_adjust, int hb_top_adjust, int hb_bottom_adjust ) :
    m_position( 0, 0 )
  , m_hitbox( 0, 0 )
  , spriteCenter_( 0, 0 )
  , m_width( width )
  , m_height( height )
  , m_hb_left_adjust( hb_left_adjust )
  , m_hb_right_adjust( hb_right_adjust )
  , m_hb_top_adjust( hb_top_adjust )
  , m_hb_bottom_adjust( hb_bottom_adjust )
  {
  
}

void Position::updatePosition( Vector2D new_xy ) {
  m_position.setX( new_xy.getX() );
  m_position.setY( new_xy.getY() );
  
  m_scale = 0.5f + ( ( 1.0f - 0.5f ) * ( m_bottomY / 720.0f ) );
  if( m_scale > 1.0f ) { m_scale = 1.0f; }
  if( m_scale < 0.5f ) { m_scale = 0.5f; }
  
  m_destWidth  = m_width  * m_scale;
  m_destHeight = m_height * m_scale;
  
  // update hitbox position
  hitbox_.left    = m_position.getX() + ( m_hb_left_adjust * m_scale ) ;
  hitbox_.top     = m_position.getY() + ( m_hb_top_adjust  * m_scale );
  hitbox_.right   = hitbox_.left + ( ( m_width - m_hb_left_adjust - m_hb_right_adjust ) * m_scale );
  hitbox_.bottom  = hitbox_.top  + ( ( m_height - m_hb_top_adjust - m_hb_bottom_adjust ) * m_scale );
  /*
  std::cout << "left is " << hitbox_.left << std::endl;
  std::cout << "right is " << hitbox_.right << std::endl;
  std::cout << "top is " << hitbox_.top << std::endl;
  std::cout << "bottom is " << hitbox_.bottom << std::endl;
  */
  //m_hitbox.setX( m_position.getX() + ( m_hb_left_adjust * m_scale ) );
  //m_hitbox.setY( m_position.getY() + ( m_hb_top_adjust  * m_scale ) );
  
  //m_hitbox_width = ( ( m_width * m_scale ) - ( m_hb_left_adjust * m_scale ) - ( m_hb_right_adjust * m_scale ) );
  //m_hitbox_height = ( ( m_height * m_scale ) - ( m_hb_top_adjust * m_scale ) - ( m_hb_bottom_adjust * m_scale ) );
  
  m_bottomY = m_position.getY() + m_destHeight;
  
  //m_spriteCenter.setX( m_position.getX() + ( m_destWidth / 2 ) );
  //m_spriteCenter.setY( m_position.getY() + ( m_destHeight / 2 ) );
  
  if( m_position.getX() < ( 0 - m_width )
   || m_position.getX() > 1280
   || m_position.getY() < ( 0 - m_height )
   || m_position.getY() > 720 ) {
  
    m_outOfBounds = true;
  } else if ( m_outOfBounds ) {
    m_outOfBounds = false;
  }
  
}

Vector2D Position::getSpriteCenter() {
  spriteCenter_.setX( hitbox_.left + ( ( hitbox_.right - hitbox_.left ) / 2 ) );
  spriteCenter_.setY( hitbox_.top + ( ( hitbox_.bottom - hitbox_.top ) / 2 ) );
  return spriteCenter_;
}

