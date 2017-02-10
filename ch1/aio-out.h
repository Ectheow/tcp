



#ifndef _AIO_H
#define _AIO_H	1

#include <features.h>
#include <sys/types.h>
#define __need_sigevent_t
#include <bits/siginfo.h>
#define __need_timespec
#include <time.h>

__BEGIN_DECLS


struct aiocb
{
  int aio_fildes;		
  int aio_lio_opcode;		
  int aio_reqprio;		
  volatile void *aio_buf;	
  size_t aio_nbytes;		
  struct sigevent aio_sigevent;	

  
  struct aiocb *__next_prio;
  int __abs_prio;
  int __policy;
  int __error_code;
  __ssize_t __return_value;

#ifndef __USE_FILE_OFFSET64
  __off_t aio_offset;		
  char __pad[sizeof (__off64_t) - sizeof (__off_t)];
#else
  __off64_t aio_offset;		
#endif
  char __glibc_reserved[32];
};


#ifdef __USE_LARGEFILE64
struct aiocb64
{
  int aio_fildes;		
  int aio_lio_opcode;		
  int aio_reqprio;		
  volatile void *aio_buf;	
  size_t aio_nbytes;		
  struct sigevent aio_sigevent;	

  
  struct aiocb *__next_prio;
  int __abs_prio;
  int __policy;
  int __error_code;
  __ssize_t __return_value;

  __off64_t aio_offset;		
  char __glibc_reserved[32];
};
#endif


#ifdef __USE_GNU

struct aioinit
  {
    int aio_threads;		
    int aio_num;		
    int aio_locks;		
    int aio_usedba;		
    int aio_debug;		
    int aio_numusers;		
    int aio_idle_time;		
    int aio_reserved;
  };
#endif



enum
{
  AIO_CANCELED,
#define AIO_CANCELED AIO_CANCELED
  AIO_NOTCANCELED,
#define AIO_NOTCANCELED AIO_NOTCANCELED
  AIO_ALLDONE
#define AIO_ALLDONE AIO_ALLDONE
};



enum
{
  LIO_READ,
#define LIO_READ LIO_READ
  LIO_WRITE,
#define LIO_WRITE LIO_WRITE
  LIO_NOP
#define LIO_NOP LIO_NOP
};



enum
{
  LIO_WAIT,
#define LIO_WAIT LIO_WAIT
  LIO_NOWAIT
#define LIO_NOWAIT LIO_NOWAIT
};



#ifdef __USE_GNU
extern void aio_init (const struct aioinit *__init) __THROW __nonnull ((1));
#endif


#ifndef __USE_FILE_OFFSET64

extern int aio_read (struct aiocb *__aiocbp) __THROW __nonnull ((1));

extern int aio_write (struct aiocb *__aiocbp) __THROW __nonnull ((1));


extern int lio_listio (int __mode,
		       struct aiocb *const __list[__restrict_arr],
		       int __nent, struct sigevent *__restrict __sig)
  __THROW __nonnull ((2));


extern int aio_error (const struct aiocb *__aiocbp) __THROW __nonnull ((1));

extern __ssize_t aio_return (struct aiocb *__aiocbp) __THROW __nonnull ((1));


extern int aio_cancel (int __fildes, struct aiocb *__aiocbp) __THROW;


extern int aio_suspend (const struct aiocb *const __list[], int __nent,
			const struct timespec *__restrict __timeout)
  __nonnull ((1));


extern int aio_fsync (int __operation, struct aiocb *__aiocbp)
  __THROW __nonnull ((2));
#else
# ifdef __REDIRECT_NTH
extern int __REDIRECT_NTH (aio_read, (struct aiocb *__aiocbp), aio_read64)
  __nonnull ((1));
extern int __REDIRECT_NTH (aio_write, (struct aiocb *__aiocbp), aio_write64)
  __nonnull ((1));

extern int __REDIRECT_NTH (lio_listio,
			   (int __mode,
			    struct aiocb *const __list[__restrict_arr],
			    int __nent, struct sigevent *__restrict __sig),
			   lio_listio64) __nonnull ((2));

extern int __REDIRECT_NTH (aio_error, (const struct aiocb *__aiocbp),
			   aio_error64) __nonnull ((1));
extern __ssize_t __REDIRECT_NTH (aio_return, (struct aiocb *__aiocbp),
				 aio_return64) __nonnull ((1));

extern int __REDIRECT_NTH (aio_cancel,
			   (int __fildes, struct aiocb *__aiocbp),
			   aio_cancel64);

extern int __REDIRECT_NTH (aio_suspend,
			   (const struct aiocb *const __list[], int __nent,
			    const struct timespec *__restrict __timeout),
			   aio_suspend64) __nonnull ((1));

extern int __REDIRECT_NTH (aio_fsync,
			   (int __operation, struct aiocb *__aiocbp),
			   aio_fsync64) __nonnull ((2));

# else
#  define aio_read aio_read64
#  define aio_write aio_write64
#  define lio_listio lio_listio64
#  define aio_error aio_error64
#  define aio_return aio_return64
#  define aio_cancel aio_cancel64
#  define aio_suspend aio_suspend64
#  define aio_fsync aio_fsync64
# endif
#endif

#ifdef __USE_LARGEFILE64
extern int aio_read64 (struct aiocb64 *__aiocbp) __THROW __nonnull ((1));
extern int aio_write64 (struct aiocb64 *__aiocbp) __THROW __nonnull ((1));

extern int lio_listio64 (int __mode,
			 struct aiocb64 *const __list[__restrict_arr],
			 int __nent, struct sigevent *__restrict __sig)
  __THROW __nonnull ((2));

extern int aio_error64 (const struct aiocb64 *__aiocbp)
  __THROW __nonnull ((1));
extern __ssize_t aio_return64 (struct aiocb64 *__aiocbp)
  __THROW __nonnull ((1));

extern int aio_cancel64 (int __fildes, struct aiocb64 *__aiocbp) __THROW;

extern int aio_suspend64 (const struct aiocb64 *const __list[], int __nent,
			  const struct timespec *__restrict __timeout)
  __THROW __nonnull ((1));

extern int aio_fsync64 (int __operation, struct aiocb64 *__aiocbp)
  __THROW __nonnull ((2));
#endif

__END_DECLS

#endif 
