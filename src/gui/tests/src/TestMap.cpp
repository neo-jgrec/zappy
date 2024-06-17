#include <criterion/criterion.h>
#include <vector>

#include "../../src/parser/Map.hpp"
#include "../../src/utils/GuiException.hpp"

Test(Map, constructor)
{
    Map map;

    std::vector<int> size = map.getSize();
    cr_assert_eq(size[0], 0, "Map size, Expected 0, got %d", size[0]);
    cr_assert_eq(size[1], 0, "Map size, Expected 0, got %d", size[1]);
}

Test(Map, fillMap)
{
    Map map;

    map.fillMap(5, 5);
    std::vector<int> size = map.getSize();
    cr_assert_eq(size[0], 5, "Map size, Expected 5, got %d", size[0]);
    cr_assert_eq(size[1], 5, "Map size, Expected 5, got %d", size[1]);
}

Test(Map, updateTile)
{
    Map map;

    map.fillMap(5, 5);
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    map.updateTile(2, 2, values);
    std::vector<int> res = map.getMap().at(2).at(2).getRessources();
    cr_assert_eq(res[0], 1, "Expected 1, got %d", res[0]);
    cr_assert_eq(res[1], 2, "Expected 2, got %d", res[1]);
    cr_assert_eq(res[2], 3, "Expected 3, got %d", res[2]);
    cr_assert_eq(res[3], 4, "Expected 4, got %d", res[3]);
    cr_assert_eq(res[4], 5, "Expected 5, got %d", res[4]);
    cr_assert_eq(res[5], 6, "Expected 6, got %d", res[5]);
    cr_assert_eq(res[6], 7, "Expected 7, got %d", res[6]);
}

Test(Tile, getTileAt)
{
    Map map;

    map.fillMap(5, 5);
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    map.updateTile(2, 2, values);
    Tile tile = map.getTileAt(2, 2);
    cr_assert_eq(tile.getResAt(0), 1, "Expected 1, got %d", tile.getResAt(0));
}

Test(Tile, updateTileWrongPos)
{
    Map map;

    map.fillMap(5, 5);
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    cr_assert_throw(map.updateTile(3, 6, values), guiException);
    cr_assert_throw(map.updateTile(6, 3, values), guiException);
    cr_assert_throw(map.updateTile(6, 6, values), guiException);
}

Test(Tile, getTileAtWrongPos)
{
    Map map;

    map.fillMap(5, 5);
    cr_assert_throw(map.getTileAt(6, 6), std::exception, "Expected std::exception");
    cr_assert_throw(map.getTileAt(6, 3), std::exception, "Expected std::exception");
    cr_assert_throw(map.getTileAt(3, 6), std::exception, "Expected std::exception");
}

Test(Map, getMap)
{
    Map map;

    map.fillMap(2, 2);
    std::vector<std::vector<Tile>> tiles = map.getMap();
    cr_assert_eq(tiles.size(), 2, "Expected 2, got %ld", tiles.size());
    cr_assert_eq(tiles[0].size(), 2, "Expected 2, got %ld", tiles[0].size());
}


