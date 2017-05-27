#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <math.h>

class Vector2D {
  private:
    float m_x;
    float m_y;
    
  public:
    Vector2D( float x, float y ) : m_x( x ), m_y( y ) {}
    ~Vector2D(){}
    
    float getX() { return m_x; }
    float getY() { return m_y; }
    
    void setX( float x ) { m_x = x; }
    void setY( float y ) { m_y = y; }
    
    float length() { return sqrt( m_x * m_x + m_y * m_y ); }
    
    Vector2D operator+( const Vector2D& v2 ) const {
      return Vector2D( m_x + v2.m_x, m_y + v2.m_y );
    }
    
    friend Vector2D& operator+=( Vector2D& v1, const Vector2D& v2 ) {
      v1.m_x += v2.m_x;
      v1.m_y += v2.m_y;
      return v1;
    }
    
    Vector2D operator*( float scaler ) {
      return Vector2D( m_x * scaler, m_y * scaler );
    }
    
    Vector2D& operator*=( float scaler ) {
      m_x *= scaler;
      m_y *= scaler;
      return *this;
    }
    
    Vector2D operator-( const Vector2D& v2 ) const {
      return Vector2D( m_x - v2.m_x, m_y - v2.m_y );
    }
    
    friend Vector2D& operator-=( Vector2D& v1, const Vector2D& v2 ) {
      v1.m_x -= v2.m_x;
      v1.m_y -= v2.m_y;
      return v1;
    }
    
    Vector2D operator/( float scaler ) {
      return Vector2D( m_x / scaler, m_y / scaler );
    }
    
    Vector2D& operator/=( float scaler ) {
      m_x /= scaler;
      m_y /= scaler;
      
      return *this;
    }
    
    void normalize() {
      float l = length();
      if( l > 0 ) {
        ( *this ) *= 1 / l;
      }
    }
  
    float distance( const Vector2D& v2 ) {
      return sqrt( pow( ( m_x - v2.m_x ), 2 ) +  pow( ( m_y - v2.m_y ), 2 ) );
    }
};

#endif //VECTOR2D_HPP
