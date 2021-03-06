#ifndef __JSON_INT_H
#define __JSON_INT_H

/*
	libjson - a C library to parse and construct JSON data structures.

	Copyright (C) 2012 onwards  Attie Grande (attie@attie.co.uk)

	libjson is free software: you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	libjson is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define EXPORT __attribute__((visibility("default")))
#define LH() fprintf(stderr, "%s:%d %s()\n", __FILE__, __LINE__, __FUNCTION__)

#include "json.h"
#include "buf.h"

struct json;
struct json_parse;
struct json_parseState;
struct json_element;

enum identifierType {
	ID_INVALID,
	ID_NUMBER,
	ID_IDENTIFIER,
};

enum characterType {
	CHAR_NONE,
	CHAR_SPACE,
	CHAR_NUMERIC,
	CHAR_NONNUMERIC,
	CHAR_DOT,
};

struct json_parseState {
	unsigned int s_name;
	unsigned int e_name;
	unsigned int q_name; /* quoted? 2 = yes, 1 = no, 0 = unknown */
	unsigned int i_colon;
	unsigned int s_value;
	unsigned int e_value;
	unsigned int q_value; /* quoted? 2 = yes, 1 = no, 0 = unknown */
};

struct json_parse {
	json_err err;
	struct json_buf buf;
	unsigned int pos;
	struct json_element *element;
	struct json_parseState state;
};

struct json {
	struct json_parse parse;
	struct json_element *root;
};

struct json_element {
	struct json *json;
	struct json_element *parent;
	struct json_element *sibling_prev;
	struct json_element *sibling_next;
	struct json_element *child_head;

	void *user_data;

	unsigned char *name;

	enum json_dataTypes type;
	unsigned int data_len;
	union {
		unsigned char *asRaw;
		int asInt;
		double asFloat;
	} data;
};

#endif /* __JSON_INT_H */
