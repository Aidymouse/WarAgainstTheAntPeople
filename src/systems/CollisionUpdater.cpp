/** Each ent with position and collider, updates the collider to the position,
 * and updates spot in the collision grid. This should happen after all movement
 * but before any collisions. Kinda annoying. */

// Actually, transform system handles this, because the collider only needs to
// update when position is updated.
