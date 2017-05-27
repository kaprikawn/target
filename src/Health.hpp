#ifndef HEALTH_HPP
#define HEALTH_HPP

class Health {
  
  private:
    int m_hp;
    int m_max_hp;
  
  public:
    Health( int hp ) {
      m_hp = m_max_hp = hp;
    }
    
    void setInitialHp( int hp ) {
      m_hp = m_max_hp = hp;
    }
    
    void reduceHp( int attackAmount ) {
      m_hp -= attackAmount;
    }
    
    int getCurrentHp() {
      return m_hp;
    }
    
    int getMaxHp() {
      return m_max_hp;
    }
};

#endif //HEALTH_HPP
