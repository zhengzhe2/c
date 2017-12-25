#ifndef JTYPE_H
#define JTYPE_H

#define	KEY_KIND_NONE				0x00				/* 锟斤拷锟斤拷锟絃锟絒锟饺傦拷							*/
#define	KEY_KIND_HARD				0x01				/* 锟絳锟教僉锟絒								*/
#define	KEY_KIND_ROTARY				0x02				/* 锟斤拷锟絒锟絕锟斤拷锟絒							*/
#define	KEY_KIND_TOUCH				0x03				/* 锟絕锟絙锟絗锟絧锟絣锟斤拷							*/
#define	KEY_KIND_WIRED				0x04				/* 锟斤拷锟紺锟斤拷锟絒锟絟锟斤拷锟斤拷锟絉锟斤拷					*/
#define	KEY_KIND_TOUCH_BUTTON		0x05
#define	KEY_KIND_AIRGESTURE			0x06
#define	KEY_KIND_REMOTE				0x07
#define	KEY_KIND_PANEL_KEY			0x08
#define	KEY_KIND_INFRARED_KEY		0x09

#define	KEY_STATE_DOWN 				0x01
#define	KEY_STATE_UP 				0x00

#define KEYDCD_TOUCH_INVALID 			0
#define KEYDCD_TOUCH_DOWN 			4
#define KEYDCD_TOUCH_UP 			5
#define KEYDCD_TOUCH_MOVE 			1


#define KEY_TOUCH_DUAL				( 0x02 )
#define KEY_TOUCH_PUSH				( 0x01 )
#define KEY_TOUCH_SEPARATE			( 0x00 )


#define OPERATE_NORMAL 				(0x00)
#define OPERATE_CANCEL				(0x01)


struct ST_COORD
{
    signed short                    x;
    signed short                    y;
    unsigned char                   curr_state;
    unsigned char                   touch_id;

};

struct ST_TOUCH_STATUS
{
    struct ST_COORD				pos_1;							/* 锟絕锟絙锟絗锟斤拷锟絎1(x,y)					*/
    struct ST_COORD				pos_2;							/* 锟絕锟絙锟絗锟斤拷锟絎2(x,y)					*/
    struct ST_COORD				pos_3;							/* 锟絕锟絙锟絗锟斤拷锟絎2(x,y)					*/
    struct ST_COORD				pos_4;							/* 锟絕锟絙锟絗锟斤拷锟絎2(x,y)					*/
    struct ST_COORD				pos_5;							/* 锟絕锟絙锟絗锟斤拷锟絎2(x,y)					*/
    unsigned char 				gesture_type;					/* 锟絎锟紽锟絏锟絗锟斤拷锟斤拷锟?				*/
    unsigned char				touch_info;						/* 锟絕锟絙锟絗锟斤拷詮锟斤拷					*/
    unsigned char				touch_numb;						/* 锟絕锟絙锟絗锟斤拷詮锟斤拷					*/
};


struct ST_FIXATION_KEY_CODE
{
    unsigned long				freq_push;						/* 锟斤拷锟斤拷锟斤拷(125msec)锟絤锟斤拷锟?		*/
    struct ST_COORD				touch_coord;					/* 锟解惓锟较傦拷AD锟斤拷锟絎					*/
    /*	ULONG					slide_info;	*/				/* 锟絏锟斤拷锟紺锟絟锟斤拷锟?					*/
    unsigned long				operate_info;
    struct ST_TOUCH_STATUS		touch_status;					/* touch status   */
    unsigned short 				fix_key_code;					/* 锟絤锟斤拷L锟絒锟絉锟絒锟絟(锟絳锟絕锟斤拷锟絉锟絒锟絟)		*/
    unsigned char				key_type;						/* 锟絃锟絒锟斤拷锟?						*/
};

#define TOUCH_TYPE_DOWN   "\"down\""
#define TOUCH_TYPE_UP     "\"up\""
#define TOUCH_TYPE_MOVE   "\"move\""


#endif // JTYPE_H

