#pragma once

struct PlayerCoord
{
  float x, y, z;
};

class Player
{
public:
  Player();
  virtual ~Player();

  PlayerCoord GetLocation();

private:
  PlayerCoord m_location;

};

