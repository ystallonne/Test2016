#ifndef _FSM_H_
#define _FSM_H_

/****************************************************************************
 *
 *            Copyright (c) 2005-2008 by HCC Embedded
 *
 * This software is copyrighted by and is the sole property of
 * HCC.  All rights, title, ownership, or other interests
 * in the software remain the property of HCC.  This
 * software may only be used in accordance with the corresponding
 * license agreement.  Any unauthorized use, duplication, transmission,
 * distribution, or disclosure of this software is expressly forbidden.
 *
 * This Copyright notice may not be removed or modified without prior
 * written consent of HCC.
 *
 * HCC reserves the right to modify this software without notice.
 *
 * HCC Embedded
 * Budapest 1133
 * Vaci ut 110
 * Hungary
 *
 * Tel:  +36 (1) 450 1302
 * Fax:  +36 (1) 450 1303
 * http: www.hcc-embedded.com
 * email: info@hcc-embedded.com
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define FS_MAXDENAME 13		/* maximum direntry name */
#include <string.h>
#ifndef NULL
#define NULL (void *)0
#endif

/*  Directory entry definition  */
typedef struct {
	unsigned char attr;			/* attribute of the file */

	W_CHAR lname[FS_MAXDENAME]; /* file name */

	unsigned short nlfn;		/* next lfn entry */

	unsigned short ctime;		/* creation time */
	unsigned short cdate;		/* creation date */

	unsigned short sector;		/* start sector */
	unsigned short dirnum;		/* directory relative number */

	long len;					/* length of file */

    unsigned long secure;		/* security code */
#if (CRCONFILES)
    hcc_u32 crc32;				/* crc32 for file protection */
#endif
} FS_DIRENTRY;


typedef struct {
	unsigned char attr;			/* attribute of the file */
	unsigned short nlfn1;		/* next lfn entry */
	unsigned short nlfn2;		/* next lfn entry */
} FS_DIRENTRY_LFN;

#if HCC_16BIT_CHAR
#define FS_MAXLFN ((sizeof(FS_DIRENTRY)-sizeof(FS_DIRENTRY_LFN))>>1)
#else
#define FS_MAXLFN ((sizeof(FS_DIRENTRY)-sizeof(FS_DIRENTRY_LFN))>>1)
#endif

#define FS_MAXLNAME (FS_MAXDENAME + 4*FS_MAXLFN) /*  maximum name length -> 13+4*13 => 65  */

/*  definitions for file/entry attribute  */

#define FS_ATTR_DE			0x01	/* entry is used for direntry */
#define FS_ATTR_DIR			0x02	/* directory */
#define FS_ATTR_LFN1		0x04	/* structure holds long file name in the 1st half */
#define FS_ATTR_LFN2		0x08	/* structure holds long file name in the 2nd half */
#define FS_ATTR_LFN1NXT		0x10	/* there is next entry of 1 on next bottom */
#define FS_ATTR_LFN1NXTTOP	0x20	/* there is next entry of 1 on next top */
#define FS_ATTR_LFN2NXT		0x40	/* there is next entry of 2 on next bottom */
#define FS_ATTR_LFN2NXTTOP	0x80	/* there is next entry of 2 on next top */

#define FS_ATTR_ALLLFN1 (FS_ATTR_LFN1|FS_ATTR_LFN1NXT|FS_ATTR_LFN1NXTTOP)
#define FS_ATTR_ALLLFN2	(FS_ATTR_LFN2|FS_ATTR_LFN2NXT|FS_ATTR_LFN2NXTTOP)

#if TI_COMPRESS
#define FS_ATTR_COMPRESSED	0x100	/* file is compressed */
#endif

#define FSSEC_ATTR_ARC      (0x20UL<<(31-6))
#define FSSEC_ATTR_DIR      (0x10UL<<(31-6))
#define FSSEC_ATTR_VOLUME   (0x08UL<<(31-6))
#define FSSEC_ATTR_SYSTEM   (0x04UL<<(31-6))
#define FSSEC_ATTR_HIDDEN   (0x02UL<<(31-6))
#define FSSEC_ATTR_READONLY (0x01UL<<(31-6))
#define FSSEC_ATTR_USER		(0xffffffffUL^(FSSEC_ATTR_ARC|FSSEC_ATTR_DIR|FSSEC_ATTR_VOLUME|FSSEC_ATTR_SYSTEM|FSSEC_ATTR_HIDDEN|FSSEC_ATTR_READONLY))

/*  definitions for ctime  */
#define FS_CTIME_SEC_SHIFT	0
#define FS_CTIME_SEC_MASK  0x001f	/* 0-30 in 2seconds */
#define FS_CTIME_MIN_SHIFT	5
#define FS_CTIME_MIN_MASK  0x07e0	/* 0-59  */
#define FS_CTIME_HOUR_SHIFT	11
#define FS_CTIME_HOUR_MASK 0xf800	/* 0-23 */

/*  definitions for cdate  */

#define FS_CDATE_DAY_SHIFT		0
#define FS_CDATE_DAY_MASK		0x001f	/* 0-31 */
#define FS_CDATE_MONTH_SHIFT		5
#define FS_CDATE_MONTH_MASK	0x01e0	/* 1-12 */
#define FS_CDATE_YEAR_SHIFT		9
#define FS_CDATE_YEAR_MASK		0xfe00	/* 0-119 (1980+value) */

/*  definitions for dirnum variable  */

#define FS_DIR_ROOT  ((unsigned short)0xffff)
#define FS_DIR_LABEL ((unsigned short)0xfff0)

typedef struct {
   unsigned long total;
   unsigned long free;
   unsigned long used;
   unsigned long bad;
} FS_SPACE;

/*  struct for FS_NAME  */

typedef struct {
	int drivenum;				/*  0-A 1-B 2-C  */
	W_CHAR path [FS_MAXPATH];		/*   /directory1/dir2/   */
	W_CHAR lname[FS_MAXPATH];		/*  filename  */
	unsigned short dirnum;		/*  0xffff-root other case in subdir n  */
} FS_NAME;

/*  struct for find file  */

typedef struct {
	char attr;					/* attribute of the file/entry */
	char filename[FS_MAXPATH];	/* file name+ext */

	unsigned short ctime;		/* creation time */
	unsigned short cdate;		/* creation date */

	unsigned long filesize;	 	/* length of file */

	unsigned long secure;		/* secure */

	FS_NAME findfsname;		   	/* find properties */
	unsigned short findpos;		/* find position */
} FS_FIND;

#ifdef HCC_UNICODE
typedef struct {
	char attr;					/* attribute of the file/entry */
	W_CHAR filename[FS_MAXPATH];	/* file name+ext */

	unsigned short ctime;		/* creation time */
	unsigned short cdate;		/* creation date */

	unsigned long filesize;	   	/* length of file */

	unsigned long secure;		/* secure */

	FS_NAME findfsname;		   	/* find properties */
	unsigned short findpos;		/* find position */
} FS_WFIND;
#endif


/* definition for fs_stat*/
typedef struct
{
	unsigned long filesize;
	unsigned short createdate;
	unsigned short createtime;
	unsigned long secure;
	int drivenum;
} FS_STAT;


/*  definitions for FS_FILE  */
typedef struct {
	long reference;		/* reference which fileint used */
} FS_FILE;

/*  definitions for FS_FILE internally used  */
typedef	struct FS_FILEINT FS_FILEINT;

typedef struct FS_FILEINT {
	FS_FILE file;
	FS_DIRENTRY *direntry;	/* link to directory list */
	long pos;				/* current position for read, file size for write */
	long relpos;			/*  relative position in a sector  */
	int mode;				/* mode to open 0-close, 1-read, 2-write/append */
	int drivenum;			/* drive number */
	char *buffer;			/* rd/write buffer */
	int modified;			/* if write buffer is modified */

	unsigned short *sector;	/*  this points where to write/read next sector info  */
	unsigned short sectorstart;  /* after file is closed this has to be copied into direntry */

	unsigned short *discard;	 /*  this points where to write/read last discard sector is  */
	unsigned short discardstart; /* after file is closed this has to be set as discardable */
	long len;		/* file size, this is copied after fs_close */
	int state;		/* file status  */
	FS_FILEINT *appsync;	/* for append sync */
} _FS_FILEINT;

/*  definitions for fs_file state  */

#define ST_FILE_LOADED	 0x01
#define ST_FILE_SYNC	 0x02
#define ST_FILE_NEXTPROH 0x04
#define ST_FILE_CRCON	 0x08

/*  definitions for fs_file mode  */

enum
{
	FS_FILE_CLOSE,
	FS_FILE_RD,
	FS_FILE_RDP,
	FS_FILE_WR,
	FS_FILE_WRP,
	FS_FILE_A,
	FS_FILE_AP,
	FS_FILE_ABORT,
	FS_FILE_LOCKED
};


/*  definitions for FLASH physical functions   */

typedef int (*FS_PHYREAD)(void *data, long block, long blockrel, long datalen);
typedef int (*FS_PHYERASE)(long block);
typedef int (*FS_PHYWRITE)(void *data, long block,long relsector, long size,long sdata);
typedef int (*FS_PHYVERIFY)(void *data, long block,long relsector, long size,long sdata);
typedef int (*FS_PHYCHECK)(long block);
typedef long (*FS_PHYSIGN)(long block);
typedef int (*FS_PHYCACHE)(void *data, long block, long page, long pagenum, long sdata);
typedef int (*FS_PHYBLKCPY)(long destblock, long soublock);

/*  definitions for FLASH info and phy  */

typedef struct {
long maxblock;				/* maximum number of block can be used */
long blocksize;			/* block size in bytes */
long sectorsize;			/* sector size wanted to use (less than block size */
long sectorperblock;		/* sector per block (block size/sector size); */
long blockstart;			/* where relative physically block start */
long descsize; 			/* max size of fat+directory+block index */
long descblockstart;		/* 1st block which is used for descriptor above (NOR) */
long descblockend;		/* last block which is used for descriptor above (NOR) */
long separatedir;			/* if directory used separatelly from FAT (NAND) */
long cacheddescsize;   		/* cached descriptor size in descriptor < descsize (NOR) */
long cachedpagenum;			/* cached pagenum (page/block NAND) */
long cachedpagesize;		/* cached page size (page size. cachedpagenum*cachedpagesize=blocksize */
FS_PHYREAD   ReadFlash;         /* read content */
FS_PHYERASE  EraseFlash;        /* erase a block */
FS_PHYWRITE  WriteFlash;        /* write content */
FS_PHYVERIFY VerifyFlash;       /* verify content */
FS_PHYCHECK  CheckBadBlock;     /* check if block is bad block (NAND) */
FS_PHYSIGN   GetBlockSignature; /* get block signature data (NAND) */
FS_PHYCACHE	 WriteVerifyPage;	/* Write and verify page (NAND) */
FS_PHYBLKCPY BlockCopy;			/* HW/SW accelerated block copy in physical (NAND/NOR) optional */
unsigned char *chkeraseblk;     /* buffer for preerasing blocks optional request to erase */
unsigned char *erasedblk;       /* buffer for preerasing blocks optional set to erased */
} FS_FLASH;

#define FS_MAXPREDISTANCE 128
/* distance for preerased blk selection */

typedef int (*FS_PHYGETID)(FS_FLASH *flash);

/*  definitions for fat descriptor  */

typedef struct {
	hcc_u32 crc32;			/* crc of this structure */
	hcc_u32 reference;		/* reference counter */
	long nextdesc;			/* which desc needs to be written */
	hcc_u32 dircrc32;		/* directory crc32 */
/*  FAT + Direntries + Block index is allocated here, the extra's size is flash->descsize  */
} FS_FATDESC;


#define FS_CHACHETYPE_DESC 0x8001
#define FS_CHACHETYPE_DIR  0x8002

#define FS_STCACHE_DESCCHANGE 0x01 /* descriptor change */
#define FS_STCACHE_DIRCHANGE  0x02 /* direntry change */
#define FS_STCACHE_FULL       0x04 /* cache full */
#define FS_STCACHE_ENTRY      0x08 /* cache has entry */

#define FS_MAXCACHEDE 32	/* max cacheable de */

typedef struct 
{
	hcc_u32 *desc; /* NOR+NAND */
	hcc_u32 *sptr; /* start ptr of current changes */
	hcc_u32 *ptr;  /* current position */
	hcc_u32 status; /* status of cache */

	hcc_u32 reference; /* reference counter NAND+NOR */
	hcc_32 free;		/* free space in cache NAND+NOR */
	hcc_32 size;		/* size of cache NAND+NOR */

	int maxde;		/* number of de entry in des */
	void *des [FS_MAXCACHEDE]; /* de entries here */

	long currdescnum;/* current descriptor block for NOR */

} FS_WRCACHE;

/*  definitions for volume info   */
typedef struct 
{
	int drivenum;				/* which drive is to belong 0-a, 1-b, ... */
	char *buffer;				/* next alloc pointer for alloc data function */
	long freemem;				/* free memory space on alloc */
	long usedmem;				/* used memory */
	long maxsectornum;			/* maximum sector used */
	unsigned short *_fat;		/* pointer to memory FAT (data found after volumeinfo) */
	unsigned short *fatmirror;	/* pointer to memory FAT (data found after volumeinfo) */

	W_CHAR *cwd;					/* current working folder in this volume */

	unsigned int maxdirentry;	/* directory entry used */
	FS_DIRENTRY *direntries; 	/* pointer to dirinfo */
	long sectorsize;			/* sector size */
	int maxfile;				/* maximum number of used file */
	FS_FILEINT *files;			/* s_fileint pointers */
	FS_FLASH *flash;			/* flash device properties */
	FS_FATDESC *fatdesc;  		/* user driver data 1 */
	char *ramdrivedata;			/* ramdrive data pointer */
	unsigned char *zerosector; 	/* nandflash zero sector */
	hcc_32 *_wearlevel;			/* used for wear leveling */
	long resetwear;				/* signal if wear leveling useable or need resetting */
	long maxfat;				/* maximum number of fat */
	long currfat;				/* current fat */
	unsigned long *fatbits;		/* preerased blocks sectors state */
	unsigned short fatbitsblock;/* preerased blocks logical number */
	unsigned short prevbitsblock;/* previously block have contained sectors */
	unsigned short lockblock;	 /* lock block for previous stored block */
	unsigned long *copybits;	/* previous block sector copy needed state */
	unsigned short *_blockindex;/* block orders (maxblock used size); */
	char *rdbuffer;				/* temporary block reading then writing (block size) */
	FS_WRCACHE cache;			/* descriptor cache */
	long laststaticwear;		/* last static weared block */
	long staticcou;				/* static counter for period counter */
	FS_MUTEX_TYPE mutex;		/* for multitasking */
	long *version;				/* pointer to stored data driver version */
	int stoperr;				/* flag for stop using filesystem */
	unsigned long reserved;	 	/* reserved size */
	int dobadblock;				/* endif */
	long desc1;					/* descriptor 1 physical */
	long desc2;					/* descriptor 2 physical */
	long *pnextdesc;			/* pointer to next descriptor */
} FS_VOLUMEINFO;



/*  definitions for multicwd   */

#if (!FS_CAPI_USED)
typedef struct {
  long ID;
  int fs_curdrive;					   /* current drive */
  struct {
	  W_CHAR cwd[FS_MAXPATH];		/* current working folder in this volume */
  } fs_vols[FS_MAXVOLUME];

  FS_MUTEX_TYPE *pmutex;		/* for multitasking */
  int lasterror;					/* last error in this task */
} FS_MULTI;

extern FS_MULTI gl_multi[FS_MAXTASK]; /* array for multitask users */

#endif

extern void fl_releaseFS(long ID);

/*  definitions for driver functions   */

typedef int (*FS_DRVFUNC1)(FS_VOLUMEINFO *vi);
typedef int (*FS_DRVFUNC2)(FS_VOLUMEINFO *vi,FS_FILEINT *file,void *data,long datalen);
typedef int (*FS_DRVFUNC4)(const FS_VOLUMEINFO *vi,long secnum,void *data, long offset,long datalen);

/*  definitions for volume descriptor  */


typedef struct {
FS_DRVFUNC1 storefat;			/* function pointer */
FS_DRVFUNC2 storesector; 		/* function pointer */
FS_DRVFUNC4 getsector;			/* function pointer */
FS_DRVFUNC1 format; 			/* function pointer */
FS_VOLUMEINFO *vi;				/* volumeinfo pointer */
int state;					/* state of this volume  */
} FS_VOLUMEDESC;


/*  definitions for volumedesc state  */

#define FS_VOL_OK			0	/* mounted, formatted */
#define FS_VOL_NOTMOUNT		1	/* not mounted (init value) */
#define FS_VOL_NOTFORMATTED	2	/* not formatted must be same as F_ERR_NOTFORMATTED */
#define FS_VOL_NOMEMORY		3	/* not enougth memory */
#define FS_VOL_NOMORE		4	/* no more drive availabale */
#define FS_VOL_DRVERROR		5	/* driver error */
#define FS_VOL_DRVALREADYMNT  F_ERR_DRVALREADYMNT	/* definitions for drive function mount  */
#define FS_VOL_ALLOCATION	  F_ERR_ALLOCATION		/* invalid address of memory (odd)*/
#define FS_VOL_TASKNOTFOUND   F_ERR_TASKNOTFOUND	/* task not found in the list */

typedef int (*FS_DRVMOUNT)(FS_VOLUMEDESC *vd,FS_PHYGETID phyfunc);

/*  definitions for file system  */

typedef struct {
FS_VOLUMEDESC vd[FS_MAXVOLUME];	/* volumes */
} FS_FILESYSTEM;

/* define fat entries */

#define FS_FAT_FREE	   ((unsigned short)0x0FFFF) /* - free of used */
#define FS_FAT_EOF	   ((unsigned short)0x0FFF0) /* - end of file */
#define FS_FAT_NOTUSED ((unsigned short)0x0FFF1) /* - not useable (maybe bad block or reserved) */
#define FS_FAT_DISCARD ((unsigned short)0x0FFF2) /* - needs to be discard */
#define FS_FAT_CHBLK   ((unsigned short)0x0FFF3) /* - cache block */
#define FS_FAT_LCKBLK  ((unsigned short)0x0FFF4) /* - lock block */
#define FS_FAT_DIR	   ((unsigned short)0x0FFF8) /* - directory entry, if separated */

/*  crc defs  */

#define FS_CRCINIT 0xffffffffL

/*  functions for middle layer file system  */

extern long fsm_allocdatasize(long size);
extern void *fsm_allocdata(FS_VOLUMEINFO *vi,long size);
extern int fsm_checkname(const W_CHAR *lname);
extern int fsm_checknamewc(const W_CHAR *lname);
extern long fsm_setnameext(char *s, char *name, char *ext);
extern int	fsm_setmaxfile(FS_VOLUMEINFO *vi,int maxfile);
extern int	fsm_setsectorsize(FS_VOLUMEINFO *vi,long sectorsize);
//extern void fsm_memcpy(void *d, void *s, long len);
#define fsm_memcpy memcpy
extern hcc_u32 fsm_calccrc32(hcc_u32  dwcrc, const void *vbuf, unsigned long  dwlen);
extern int fsm_findfreeblock(const FS_VOLUMEINFO *vi,unsigned short *sector);
//extern void fsm_memset(void *d, unsigned char fill, long len);
#define fsm_memset memset
extern int fsm_findfreesector(FS_VOLUMEINFO *vi,unsigned short *badsector);
extern void fsm_swapbadblock(FS_VOLUMEINFO *vi,unsigned short badsector);
extern void fsm_wearleveling(FS_VOLUMEINFO *vi);
extern void fsm_addsectorchain(const FS_VOLUMEINFO *vi,FS_FILEINT *file,unsigned short sector);
extern int fsm_checksectorfree(const FS_VOLUMEINFO *vi,long sector);
extern int fsm_checksectorbad(const FS_VOLUMEINFO *vi,long sector);
extern unsigned long _fs_checkfreeblocks(const FS_VOLUMEINFO *vi,unsigned long sbnum);
extern W_CHAR _fsm_toupper(W_CHAR ch);
extern void _fsm_cacheaddlptr(FS_VOLUMEINFO *vi,hcc_32 *ptr);
extern void _fsm_cacheaddsptr(FS_VOLUMEINFO *vi,unsigned short *ptr,unsigned short value);
extern void _fsm_cacheaddde(FS_VOLUMEINFO *vi,void *de);
extern void _fsm_cachepagecheck(FS_VOLUMEINFO *vi);
extern void _fsm_cachenext(FS_VOLUMEINFO *vi);
extern void _fsm_cachereset(FS_VOLUMEINFO *vi);
extern int _fsm_chacheupdatechanges(FS_VOLUMEINFO *vi);
extern void _fsm_cacheupdate(FS_VOLUMEINFO *vi);
extern int _fsm_writenextsector(FS_VOLUMEINFO *vi,FS_FILEINT *file,long relsector,void *data,long sdata);
extern void fg_setlasterror_noret (FS_MULTI *fm, int errorcode);
extern int fg_setlasterror (FS_MULTI *fm, int errorcode);
#define fsm_strlen strlen
//extern int fsm_strlen(char *string);
extern int fsm_writeverifyflash(const FS_VOLUMEINFO *vi,void *data, long block,long relsector, long size,long sdata);
extern int fsm_readflash(const FS_VOLUMEINFO *vi, void *data, long block, long blockrel, long datalen);

#ifdef HCC_UNICODE
extern W_CHAR *_fsm_towchar(W_CHAR *nconv,const char *s);
extern void _fsm_fromwchar(char *d, W_CHAR *s);
#endif
#ifdef __cplusplus
}
#endif

/****************************************************************************
 *
 * End of fsm.h
 *
 ***************************************************************************/

#endif   /* _FSM_H_ */
