/*
 *  Copyright (C) 2015 YunOS Project. All rights reserved.
 */

#ifndef _NUTTX_SECURITY_H
#define _NUTTX_SECURITY_H

#include <nuttx/fs/fs.h>
#include <nuttx/net/net.h>
#include <nuttx/sched.h>
#include <sys/socket.h>
#include <debug.h>
#include <stdint.h>

#ifdef CONFIG_SECURITY_IDMAC

/* prototypes */
extern int security_init(void);

/* subject related */
int security_task_create(struct tcb_s *tcb_task, char *name, uint8_t type);
void security_task_free(struct tcb_s *tcb_task);


/* inode related */
int security_inode_alloc(struct inode *inode);
void security_inode_free(struct inode *inode);

/* file related */
int security_file_open(struct file *file);
int security_file_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* socket related */
int security_socket_create(int family, int type, int protocol);
int security_socket_bind(struct socket *sock, struct sockaddr *address, int addrlen);
int security_socket_connect(struct socket *sock, struct sockaddr *address, int addrlen);
int security_socket_listen(struct socket *sock, int backlog);
int security_socket_accept(struct socket *sock, struct socket *newsock);
int security_socket_sendmsg(struct socket *sock, void *msg, int size);
int security_socket_recvmsg(struct socket *sock, void *msg, int size, int flags);

#else /* CONFIG_SECURITY_IDMAC */

/*
 * This is the default capabilities functionality.
 */

static inline int security_init(void)
{
    dbg("security initialization!");
    return 0;
}

static inline int security_task_create(struct tcb_s *tcb_task, char *name, uint8_t type)
{
    return 0;
}

void security_task_free(struct tcb_s *tcb_task)
{ }

static inline int security_inode_alloc(struct inode *inode)
{
    return 0;
}

static inline void security_inode_free(struct inode *inode)
{ }

static inline int security_file_open(struct file *file)
{
    return 0;
}

static inline int security_file_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    return 0;
}

static inline int security_socket_create(int family, int type, int protocol, int kern)
{
    return 0;
}

static inline int security_socket_bind(struct socket *sock, struct sockaddr *address, int addrlen)
{
    return 0;
}

static inline int security_socket_connect(struct socket *sock, struct sockaddr *address, int addrlen)
{
    return 0;
}

static inline int security_socket_listen(struct socket *sock, int backlog)
{
    return 0;
}

static inline int security_socket_accept(struct socket *sock, struct socket *newsock)
{
    return 0;
}

static inline int security_socket_sendmsg(struct socket *sock, void *msg, int size)
{
    return 0;
}

static inline int security_socket_recvmsg(struct socket *sock, void *msg, int size, int flags)
{
    return 0;
}
#endif /* CONFIG_SECURITY_IDMAC */
#endif /* ! __NUTTX_SECURITY_H */

