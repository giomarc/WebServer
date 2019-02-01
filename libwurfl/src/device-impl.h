/* Copyright (C) 2011 Fantayeneh Asres Gizaw, Filippo De Luca
 *  
 * This file is part of libWURFL.
 *
 * libWURFL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or 
 * any later version.
 *
 * libWURFL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libWURFL.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Written by Filippo De Luca <me@filippodeluca.com>.  */

#ifndef DEVICE_IMPL_H_
#define DEVICE_IMPL_H_

#include "device.h"
#include "devicedef.h"
#include "utils/hashmap.h"

struct _device_t {
	const char* id;
	const char* user_agent;
	hashmap_t* capabilities;
};

device_t* device_init(hashmap_t* devices, const devicedef_t* devicedef);

#endif /* DEVICE_IMPL_H_ */
