#ifndef RANDO_SLEEP_H
#define RANDO_SLEEP_H


 /******************************************************************************
  * Function        : RandomSleepBounded
  * Description     : Zephyr sleeps (k_sleep) for a bounded pseudo-random duration.
  * inputs          :min_sleep_ms - minimum sleep duration
  *                  min_offset - lower offset bound (random number >= to this)
  *                  max_offset - upper offset bound (random number <= to this)
  * outputs          NONE
  ******************************************************************************/
void RandomSleepBounded(uint32_t min_sleep_ms, uint32_t min_offset, uint32_t max_offset);

#endif RANDO_SLEEP_H