/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * GData Client
 * Copyright (C) Philip Withnall 2008-2009 <philip@tecnocode.co.uk>
 *
 * GData Client is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * GData Client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GData Client.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * SECTION:gdata-types
 * @short_description: miscellaneous data types
 * @stability: Unstable
 * @include: gdata/gdata-types.h
 *
 * The structures here are used haphazardly across the library, describing
 * various small data types.
 **/

#include <glib.h>
#include <glib-object.h>
#include <string.h>
#include <stdlib.h>
#include <libsoup/soup.h>

#include "gdata-types.h"

static gpointer
gdata_color_copy (gpointer color)
{
	return g_memdup (color, sizeof (GDataColor));
}

GType
gdata_color_get_type (void)
{
	static GType type_id = 0;

	if (type_id == 0) {
		type_id = g_boxed_type_register_static (g_intern_static_string ("GDataColor"),
		                                        (GBoxedCopyFunc) gdata_color_copy,
		                                        (GBoxedFreeFunc) g_free);
	}

	return type_id;
}

/**
 * gdata_color_from_hexadecimal:
 * @hexadecimal: a hexadecimal color string
 * @color: (out caller-allocates): a #GDataColor
 *
 * Parses @hexadecimal and returns a #GDataColor describing it in @color.
 *
 * @hexadecimal should be in the form <literal>#<replaceable>rr</replaceable><replaceable>gg</replaceable><replaceable>bb</replaceable></literal>,
 * where <replaceable>rr</replaceable> is a two-digit hexadecimal red intensity value, <replaceable>gg</replaceable> is green
 * and <replaceable>bb</replaceable> is blue. The hash is optional.
 *
 * Return value: %TRUE on success, %FALSE otherwise
 **/
gboolean
gdata_color_from_hexadecimal (const gchar *hexadecimal, GDataColor *color)
{
	gint temp;

	g_return_val_if_fail (hexadecimal != NULL, FALSE);
	g_return_val_if_fail (color != NULL, FALSE);

	if (*hexadecimal == '#')
		hexadecimal++;
	if (strlen (hexadecimal) != 6)
		return FALSE;

	/* Red */
	temp = g_ascii_xdigit_value (*(hexadecimal++)) * 16;
	if (temp < 0)
		return FALSE;
	color->red = temp;
	temp = g_ascii_xdigit_value (*(hexadecimal++));
	if (temp < 0)
		return FALSE;
	color->red += temp;

	/* Green */
	temp = g_ascii_xdigit_value (*(hexadecimal++)) * 16;
	if (temp < 0)
		return FALSE;
	color->green = temp;
	temp = g_ascii_xdigit_value (*(hexadecimal++));
	if (temp < 0)
		return FALSE;
	color->green += temp;

	/* Blue */
	temp = g_ascii_xdigit_value (*(hexadecimal++)) * 16;
	if (temp < 0)
		return FALSE;
	color->blue = temp;
	temp = g_ascii_xdigit_value (*(hexadecimal++));
	if (temp < 0)
		return FALSE;
	color->blue += temp;

	return TRUE;
}

/**
 * gdata_color_to_hexadecimal:
 * @color: a #GDataColor
 *
 * Returns a string describing @color in hexadecimal form; in the form <literal>#<replaceable>rr</replaceable><replaceable>gg</replaceable>
 * <replaceable>bb</replaceable></literal>, where <replaceable>rr</replaceable> is a two-digit hexadecimal red intensity value,
 * <replaceable>gg</replaceable> is green and <replaceable>bb</replaceable> is blue. The hash is always present.
 *
 * Return value: the color string; free with g_free()
 *
 * Since: 0.3.0
 **/
gchar *
gdata_color_to_hexadecimal (const GDataColor *color)
{
	g_return_val_if_fail (color != NULL, NULL);
	return g_strdup_printf ("#%02x%02x%02x", color->red, color->green, color->blue);
}

gboolean 
gdata_color_from_string(const gchar* color_value, GDataColor *color){
    gchar *hex;

	g_return_val_if_fail (color_value != NULL, FALSE);
	g_return_val_if_fail (color != NULL, FALSE);
        
        if(g_strcmp0(color_value, "1") == 0){
            hex = g_strdup("#A4BDFC");
        }
        else if(g_strcmp0(color_value, "2") == 0){
            hex = g_strdup("#7AE8BF");
        }
        else if(g_strcmp0(color_value, "3") == 0){
            hex = g_strdup("#DBADFF");
        }
        else if(g_strcmp0(color_value, "4") == 0){
            hex = g_strdup("#FF887C");
        }
        else if(g_strcmp0(color_value, "5") == 0){
            hex = g_strdup("#FBD75B");
        }
        else if(g_strcmp0(color_value, "6") == 0){
            hex = g_strdup("#FFB878");
        }
        else if(g_strcmp0(color_value, "7") == 0){
            hex = g_strdup("#46D6DB");
        }
        else if(g_strcmp0(color_value, "8") == 0){
            hex = g_strdup("#E1E1E1");
        }
        else if(g_strcmp0(color_value, "9") == 0){
            hex = g_strdup("#5484ED");
        }
        else if(g_strcmp0(color_value, "10") == 0){
            hex = g_strdup("#51B749");
        }
        else if(g_strcmp0(color_value, "11") == 0){
            hex = g_strdup("#DC2127");
        }
        else{
            return FALSE;
        }
        
        return gdata_color_from_hexadecimal(hex, color);       
}

gchar* gdata_color_to_string(const GDataColor* color){
    gchar *hexstr;
    hexstr = gdata_color_to_hexadecimal(color);
    
    if(g_strcmp0(hexstr, "#A4BDFC") == 0){
        return g_strdup("1");
    }
    else if(g_strcmp0(hexstr, "#7AE8BF")){
        return g_strdup("2");
    }
    else if(g_strcmp0(hexstr, "#DBADFF")){
        return g_strdup("3");
    }
    else if(g_strcmp0(hexstr, "#FF887C")){
        return g_strdup("4");
    }
    else if(g_strcmp0(hexstr, "#FBD75B")){
        return g_strdup("5");
    }
    else if(g_strcmp0(hexstr, "#FFB878")){
        return g_strdup("6");
    }
    else if(g_strcmp0(hexstr, "#46D6DB")){
        return g_strdup("7");
    }
    else if(g_strcmp0(hexstr, "#E1E1E1")){
        return g_strdup("8");
    }
    else if(g_strcmp0(hexstr, "#5484ED")){
        return g_strdup("9");
    }
    else if(g_strcmp0(hexstr, "#51B749")){
        return g_strdup("10");
    }
    else if(g_strcmp0(hexstr, "#DC2127")){
        return g_strdup("11");
    }
    else{
        return NULL;
    }
    
}
