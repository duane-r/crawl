/**
 * @file
 * @brief Functions for blood, chunk, & corpse rot.
 **/

#include "AppHdr.h"

#include "rot.h"

#include <algorithm>

#include "areas.h"

#include "delay.h"
#include "dungeon.h"
#include "english.h"
#include "env.h"
#include "god-conduct.h"
#include "item-prop.h"
#include "items.h"
#include "player-equip.h"
#include "religion.h"
#include "shopping.h"

#define TIMER_KEY "timer"

static bool _item_needs_rot_check(const item_def &item);

static void _rot_corpse(item_def &it, int mitm_index, int rot_time);



// Compare two CrawlStoreValues storing type T.
template<class T>
static bool _storeval_greater(const CrawlStoreValue &a,
                              const CrawlStoreValue &b)
{
    return T(a) > T(b);
}

// Sort a CrawlVector containing only Ts.
template<class T>
static void _sort_cvec(CrawlVector &vec)
{
    sort(vec.begin(), vec.end(), _storeval_greater<T>);
}

/**
 * Check whether an item decays over time. (Corpses, chunks, and blood.)
 *
 * @param item      The item to check.
 * @return          Whether the item changes (rots) over time.
 */
static bool _item_needs_rot_check(const item_def &item)
{
    if (!item.defined())
        return false;

    if (item.props.exists(CORPSE_NEVER_DECAYS))
        return false;

    return item.base_type == OBJ_CORPSES
           && item.sub_type <= CORPSE_SKELETON; // XXX: is this needed?
}

/**
 * Rot a corpse or skeleton lying on the floor.
 *
 * @param it            The corpse or skeleton to rot.
 * @param mitm_index    The slot of the corpse in the floor item array.
 * @param rot_time      The amount of time to rot the corpse for.
 */
static void _rot_corpse(item_def &it, int mitm_index, int rot_time)
{
    ASSERT(it.base_type == OBJ_CORPSES);
    ASSERT(!it.props.exists(CORPSE_NEVER_DECAYS));

    it.freshness -= rot_time;
    if (it.freshness > 0)
        return;

    if (it.sub_type == CORPSE_SKELETON || !mons_skeleton(it.mon_type))
    {
        item_was_destroyed(it);
        destroy_item(mitm_index);
    }
    else
    {
        turn_corpse_into_skeleton(it);
        const int piety = x_chance_in_y(2, 5) ? 2 : 1; // match fungal_bloom()
        did_god_conduct(DID_ROT_CARRION, piety);
    }
}

/**
 * Decay items on the floor: corpses, chunks, and Gozag gold auras.
 *
 * @param elapsedTime   The amount of time to rot the corpses for.
 */
void rot_floor_items(int elapsedTime)
{
    if (elapsedTime <= 0)
        return;

    const int rot_time = elapsedTime / ROT_TIME_FACTOR;

    for (int mitm_index = 0; mitm_index < MAX_ITEMS; ++mitm_index)
    {
        item_def &it = mitm[mitm_index];

        if (is_shop_item(it) || !_item_needs_rot_check(it))
            continue;

        if (it.base_type == OBJ_CORPSES)
            _rot_corpse(it, mitm_index, rot_time);
    }
}
