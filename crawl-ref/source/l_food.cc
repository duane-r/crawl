#include "AppHdr.h"

#include "l_libs.h"


#include "cluautil.h"
#include "itemprop.h"
#include "player.h"

/////////////////////////////////////////////////////////////////////
// Food information.

static int food_do_eat(lua_State *ls)
{
    lua_pushboolean(ls, false);
    return 1;
}

static int food_prompt_eat_chunks(lua_State *ls)
{
    lua_pushboolean(ls, false);
    return 1;
}

static int food_prompt_inventory_menu(lua_State *ls)
{
    lua_pushboolean(ls, false);
    return 1;
}

static int food_can_eat(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, false);
    return 1;
}

static int food_eat(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, false);
    return 1;
}

static int food_dangerous(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);

    lua_pushboolean(ls, false);
    return 1;
}

static int food_ischunk(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, false);
    return 1;
}

static int food_isfruit(lua_State *ls)
{
    LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, is_fruit(*item));
    return 1;
}

static int food_ismeaty(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, false);
    return 1;
}

static int food_isveggie(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, false);
    return 1;
}

static int food_bottleable(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, false);
    return 1;
}

// differs from food_can_eat in several respects
static int food_edible(lua_State *ls)
{
    //LUA_ITEM(ls, item, 1);
    lua_pushboolean(ls, false);
    return 1;
}

static const struct luaL_reg food_lib[] =
{
    { "do_eat",            food_do_eat },
    { "prompt_eat_chunks", food_prompt_eat_chunks },
    { "prompt_inv_menu",   food_prompt_inventory_menu },
    { "can_eat",           food_can_eat },
    { "eat",               food_eat },
    { "dangerous",         food_dangerous },
    { "ischunk",           food_ischunk },
    { "isfruit",           food_isfruit },
    { "ismeaty",           food_ismeaty },
    { "isveggie",          food_isveggie },
    { "bottleable",        food_bottleable },
    { "edible",            food_edible },
    { nullptr, nullptr },
};

void cluaopen_food(lua_State *ls)
{
    luaL_openlib(ls, "food", food_lib, 0);
}
