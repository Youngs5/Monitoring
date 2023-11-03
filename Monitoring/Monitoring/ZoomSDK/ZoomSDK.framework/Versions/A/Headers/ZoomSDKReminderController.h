//

#import <Foundation/Foundation.h>

@interface ZoomSDKReminderContent : NSObject
/**
 * Get the reminder’s type.
 */
@property(nonatomic,assign,readonly)ZoomSDKReminderType type;
/**
 * Get the reminder dialog content’s title.
 */
@property(nonatomic,copy,readonly)NSString *title;
/**
 * Get the detail content of the reminder dialog content.
 */
@property(nonatomic,copy,readonly)NSString *content;
/**
 * Whether to block the user from joining or staying in the meeting.
 */
@property(nonatomic,assign,readonly)BOOL isBlocking;

@end

@interface ZoomSDKReminderHandler : NSObject
/**
 * accept the reminder.
 */
-(void)accept;
/**
* declined the reminder.
*/
-(void)decline;
/**
* ignore the reminder.
*/
-(void)ignore;

@end

@protocol ZoomSDKReminderControllerDelegate <NSObject>
/**
 * Callback event when the reminder dialog displays.
 * @param handle The helper to handle the reminder dialog.
 * @param content The detail content in the reminder dialog.
 */
-(void)onReminderNotify:(ZoomSDKReminderHandler*)handle reminderContent:(ZoomSDKReminderContent*)content;

@end

@interface ZoomSDKReminderController : NSObject
/*
 *@brief Reminder callback event handler.
 */
@property(nonatomic,assign) id<ZoomSDKReminderControllerDelegate> delegate;
@end
