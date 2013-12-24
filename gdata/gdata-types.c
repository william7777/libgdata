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

/**
 * gdata_color_from_color_id:
 * @color_id: a color_id color string
 * @color: (out caller-allocates): a #GDataColor
 *
 * Parses @color_id and returns a #GDataColor describing it in @color.
 *
 * @color_id should be a string representing a number ranging from 1 to 11. 
 * For more information, see the <ulink type="http" url="https://developers.google.com/google-apps/calendar/v3/reference/events?hl=en">
 * 
 * Return value: %TRUE on success, %FALSE otherwise
 * 
 * Since: UNRELEASED
 **/
gboolean 
gdata_color_from_color_id (const gchar *color_id, GDataColor *color)
{
	g_return_val_if_fail (color_id != NULL, FALSE);
	g_return_val_if_fail (color != NULL, FALSE);
	
	guint64 parsed_color_value;
	gchar *end_ptr;
	const gchar *hex;
	static const gchar *hex_colors[] = {
		"#A4BDFC",
		"#7AE8BF",
		"#DBADFF",
		"#FF887C",
		"#FBD75B",
		"#FFB878",
		"#46D6DB",
		"#E1E1E1",
		"#5484ED",
		"#51B749",
		"#DC2127",
	};
	
	parsed_color_value = g_ascii_strtoull(color_id, &end_ptr, 10);		
	if (parsed_color_value == 0 || (*end_ptr) != '\0' || parsed_color_value > G_N_ELEMENTS (hex_colors)){
		return FALSE;
	}
	
	hex = hex_colors[parsed_color_value-1];
	return gdata_color_from_hexadecimal (hex, color); 	      
}

/**
 * gdata_color_to_color_id:
 * @color: a #GDataColor
 *
 * Returns a string describing @color in color_id form; color_id is a string representing an integer ranging from 1 to 11;
 * 
 * For more information, see the <ulink type="http" url="https://developers.google.com/google-apps/calendar/v3/reference/events?hl=en">
 *
 * Return value: the color_id string; free with g_free()
 *
 * Since: UNRELEASED
 **/
gchar * 
gdata_color_to_color_id (const GDataColor *color)
{
	guint iter;
	gchar *hexstr;
	static const gchar *hex_colors[] = {
		"#A4BDFC",
		"#7AE8BF",
		"#DBADFF",
		"#FF887C",
		"#FBD75B",
		"#FFB878",
		"#46D6DB",
		"#E1E1E1",
		"#5484ED",
		"#51B749",
		"#DC2127",
	};
	
	hexstr = gdata_color_to_hexadecimal (color);
	
	for (iter = 0; iter < G_N_ELEMENTS (hex_colors); iter++){
		if (g_strcmp0 (hexstr, hex_colors[iter]) == 0){
			g_free (hexstr);
			return g_strdup_printf ("%d", iter+1);
		}
	}
	
	g_free (hexstr);
	return NULL;
}
