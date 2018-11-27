#ifndef __MAZETILE_H
#define __MAZETILE_H



enum Tiles
{
    TILE_FLOOR,
    TILE_WALL,
    TILE_START,
	TILE_END,
    TILE_TRIGGER,
    TILE_PLAYER,
    TILE_MINOTAUR,
	TILE_TRAP,
    TILE_ERROR
};

class CMazeTile
{
private:
    Tiles m_type;
    unsigned char m_colour;
    unsigned char m_symbol;
public:
    void showTile();
    void setTileFromCharacter(char);
    Tiles getTileType();
	void setTile(unsigned char, unsigned char);
	unsigned char getSymbol();
    CMazeTile();
};

#endif