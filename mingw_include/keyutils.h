/* keyutils.h: key utility library interface
 *
 * Copyright (C) 2005 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef KEYUTILS_H
#define KEYUTILS_H

#include <stdint.h>

/* key serial number */
typedef int32_t key_serial_t;
typedef int32_t uid_t;
typedef int32_t gid_t;

/* special process keyring shortcut IDs */
#define KEY_SPEC_THREAD_KEYRING		-1	/* - key ID for thread-specific keyring */
#define KEY_SPEC_PROCESS_KEYRING	-2	/* - key ID for process-specific keyring */
#define KEY_SPEC_SESSION_KEYRING	-3	/* - key ID for session-specific keyring */
#define KEY_SPEC_USER_KEYRING		-4	/* - key ID for UID-specific keyring */
#define KEY_SPEC_USER_SESSION_KEYRING	-5	/* - key ID for UID-session keyring */
#define KEY_SPEC_GROUP_KEYRING		-6	/* - key ID for GID-specific keyring */
#define KEY_SPEC_REQKEY_AUTH_KEY	-7	/* - key ID for assumed request_key auth key */

/* request-key default keyrings */
#define KEY_REQKEY_DEFL_NO_CHANGE		-1
#define KEY_REQKEY_DEFL_DEFAULT			0
#define KEY_REQKEY_DEFL_THREAD_KEYRING		1
#define KEY_REQKEY_DEFL_PROCESS_KEYRING		2
#define KEY_REQKEY_DEFL_SESSION_KEYRING		3
#define KEY_REQKEY_DEFL_USER_KEYRING		4
#define KEY_REQKEY_DEFL_USER_SESSION_KEYRING	5
#define KEY_REQKEY_DEFL_GROUP_KEYRING		6

/* key handle permissions mask */
typedef uint32_t key_perm_t;

#define KEY_POS_VIEW	0x01000000	/* possessor can view a key's attributes */
#define KEY_POS_READ	0x02000000	/* possessor can read key payload / view keyring */
#define KEY_POS_WRITE	0x04000000	/* possessor can update key payload / add link to keyring */
#define KEY_POS_SEARCH	0x08000000	/* possessor can find a key in search / search a keyring */
#define KEY_POS_LINK	0x10000000	/* possessor can create a link to a key/keyring */
#define KEY_POS_SETATTR	0x20000000	/* possessor can set key attributes */
#define KEY_POS_ALL	0x3f000000

#define KEY_USR_VIEW	0x00010000	/* user permissions... */
#define KEY_USR_READ	0x00020000
#define KEY_USR_WRITE	0x00040000
#define KEY_USR_SEARCH	0x00080000
#define KEY_USR_LINK	0x00100000
#define KEY_USR_SETATTR	0x00200000
#define KEY_USR_ALL	0x003f0000

#define KEY_GRP_VIEW	0x00000100	/* group permissions... */
#define KEY_GRP_READ	0x00000200
#define KEY_GRP_WRITE	0x00000400
#define KEY_GRP_SEARCH	0x00000800
#define KEY_GRP_LINK	0x00001000
#define KEY_GRP_SETATTR	0x00002000
#define KEY_GRP_ALL	0x00003f00

#define KEY_OTH_VIEW	0x00000001	/* third party permissions... */
#define KEY_OTH_READ	0x00000002
#define KEY_OTH_WRITE	0x00000004
#define KEY_OTH_SEARCH	0x00000008
#define KEY_OTH_LINK	0x00000010
#define KEY_OTH_SETATTR	0x00000010
#define KEY_OTH_ALL	0x0000003f

/* keyctl commands */
#define KEYCTL_GET_KEYRING_ID		0	/* ask for a keyring's ID */
#define KEYCTL_JOIN_SESSION_KEYRING	1	/* join or start named session keyring */
#define KEYCTL_UPDATE			2	/* update a key */
#define KEYCTL_REVOKE			3	/* revoke a key */
#define KEYCTL_CHOWN			4	/* set ownership of a key */
#define KEYCTL_SETPERM			5	/* set perms on a key */
#define KEYCTL_DESCRIBE			6	/* describe a key */
#define KEYCTL_CLEAR			7	/* clear contents of a keyring */
#define KEYCTL_LINK			8	/* link a key into a keyring */
#define KEYCTL_UNLINK			9	/* unlink a key from a keyring */
#define KEYCTL_SEARCH			10	/* search for a key in a keyring */
#define KEYCTL_READ			11	/* read a key or keyring's contents */
#define KEYCTL_INSTANTIATE		12	/* instantiate a partially constructed key */
#define KEYCTL_NEGATE			13	/* negate a partially constructed key */
#define KEYCTL_SET_REQKEY_KEYRING	14	/* set default request-key keyring */
#define KEYCTL_SET_TIMEOUT		15	/* set timeout on a key */
#define KEYCTL_ASSUME_AUTHORITY		16	/* assume authority to instantiate key */
#define KEYCTL_GET_SECURITY		17	/* get key security label */
#define KEYCTL_SESSION_TO_PARENT	18	/* set my session keyring on my parent process */

/*
 * syscall wrappers
 */
extern key_serial_t add_key(const char *type,
			    const char *description,
			    const void *payload,
			    size_t plen,
			    key_serial_t ringid);

extern key_serial_t request_key(const char *type,
				const char *description,
				const char *callout_info,
				key_serial_t destringid);

extern long keyctl(int cmd, ...);

/*
 * keyctl function wrappers
 */
extern key_serial_t keyctl_get_keyring_ID(key_serial_t id, int create);
extern key_serial_t keyctl_join_session_keyring(const char *name);
extern long keyctl_update(key_serial_t id, const void *payload, size_t plen);
extern long keyctl_revoke(key_serial_t id);
extern long keyctl_chown(key_serial_t id, uid_t uid, gid_t gid);
extern long keyctl_setperm(key_serial_t id, key_perm_t perm);
extern long keyctl_describe(key_serial_t id, char *buffer, size_t buflen);
extern long keyctl_clear(key_serial_t ringid);
extern long keyctl_link(key_serial_t id, key_serial_t ringid);
extern long keyctl_unlink(key_serial_t id, key_serial_t ringid);
extern long keyctl_search(key_serial_t ringid,
			  const char *type,
			  const char *description,
			  key_serial_t destringid);
extern long keyctl_read(key_serial_t id, char *buffer, size_t buflen);
extern long keyctl_instantiate(key_serial_t id,
			       const void *payload,
			       size_t plen,
			       key_serial_t ringid);
extern long keyctl_negate(key_serial_t id, unsigned timeout, key_serial_t ringid);
extern long keyctl_set_reqkey_keyring(int reqkey_defl);
extern long keyctl_set_timeout(key_serial_t key, unsigned timeout);
extern long keyctl_assume_authority(key_serial_t key);
extern long keyctl_get_security(key_serial_t key, char *buffer, size_t buflen);
extern long keyctl_session_to_parent(void);

/*
 * utilities
 */
extern int keyctl_describe_alloc(key_serial_t id, char **_buffer);
extern int keyctl_read_alloc(key_serial_t id, void **_buffer);
extern int keyctl_get_security_alloc(key_serial_t id, char **_buffer);


#endif /* KEYUTILS_H */
