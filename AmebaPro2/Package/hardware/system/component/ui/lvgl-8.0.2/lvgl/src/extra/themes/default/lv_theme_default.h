/**
 * @file lv_theme_default.h
 *
 */

#ifndef LV_THEME_DEFAULT_H
#define LV_THEME_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../core/lv_obj.h"

#if LV_USE_THEME_DEFAULT

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the theme
 * @param color_primary the primary color of the theme
 * @param color_secondary the secondary color for the theme
 * @param font pointer to a font to use.
 * @return a pointer to reference this theme later
 */
lv_theme_t *lv_theme_default_init(lv_disp_t *disp, lv_color_t color_primary, lv_color_t color_secondary, bool dark, const lv_font_t *font);


bool lv_theme_default_is_inited(void);

/**********************
 *      MACROS
 **********************/

#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_THEME_DEFAULT_H*/
