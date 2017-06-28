/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/**
 * @file
 * SNMP server MIB API to implement thread synchronization
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Dirk Ziegelmeier <dziegel@gmx.de>
 *
 */

#ifndef LWIP_HDR_APPS_SNMP_THREADSYNC_H
#define LWIP_HDR_APPS_SNMP_THREADSYNC_H

#include <net/lwip/apps/snmp_opts.h>

#ifdef __cplusplus
extern "C" {
#endif

#if LWIP_SNMP					/* don't build if not configured for use in lwipopts.h */

#include <net/lwip/apps/snmp_core.h>
#include <net/lwip/sys.h>

typedef void (*snmp_threadsync_called_fn) (void *arg);
typedef void (*snmp_threadsync_synchronizer_fn) (snmp_threadsync_called_fn fn, void *arg);

/** Thread sync runtime data. For internal usage only. */
struct threadsync_data {
	union {
		snmp_err_t err;
		s16_t s16;
	} retval;
	union {
		const u32_t *root_oid;
		void *value;
	} arg1;
	union {
		u8_t root_oid_len;
		u16_t len;
	} arg2;
	const struct snmp_threadsync_node *threadsync_node;
	struct snmp_node_instance proxy_instance;
};

/** Thread sync instance. Needed EXCATLY once for every thread to be synced into. */
struct snmp_threadsync_instance {
	sys_sem_t sem;
	sys_mutex_t sem_usage_mutex;
	snmp_threadsync_synchronizer_fn sync_fn;
	struct threadsync_data data;
};

/** SNMP thread sync proxy leaf node */
struct snmp_threadsync_node {
	/* inherited "base class" members */
	struct snmp_leaf_node node;

	const struct snmp_leaf_node *target;
	struct snmp_threadsync_instance *instance;
};

snmp_err_t snmp_threadsync_get_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance *instance);
snmp_err_t snmp_threadsync_get_next_instance(const u32_t *root_oid, u8_t root_oid_len, struct snmp_node_instance *instance);

/** Create thread sync proxy node */
#define SNMP_CREATE_THREAD_SYNC_NODE(oid, target_leaf_node, threadsync_instance) \
	{{{ SNMP_NODE_THREADSYNC, (oid) }, \
		snmp_threadsync_get_instance, \
		snmp_threadsync_get_next_instance }, \
		(target_leaf_node), \
		(threadsync_instance) }

/** Create thread sync instance data */
void snmp_threadsync_init(struct snmp_threadsync_instance *instance, snmp_threadsync_synchronizer_fn sync_fn);

#endif							/* LWIP_SNMP */

#ifdef __cplusplus
}
#endif
#endif							/* LWIP_HDR_APPS_SNMP_THREADSYNC_H */
