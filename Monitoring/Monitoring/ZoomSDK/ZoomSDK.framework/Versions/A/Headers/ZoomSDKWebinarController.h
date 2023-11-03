
#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@interface ZoomSDKWebinarMeetingStatus : NSObject
{
    BOOL _allowPanellistStartVideo;
    BOOL _allowAttendeeChat;
    BOOL _allowRaiseHand;
    BOOL _isSupportAttendeeTalk;
}
/**
 * @brief Query if panelist is allowed to start video.
 * @return YES means that panelist is allowed to enable video, otherwise not.
 */
- (BOOL)isAllowPanellistStartVideo;
/**
 * @brief Query if attendee is allowed to chat.
 * @return YES means that attendee is allowed to chat, otherwise not.
 */
- (BOOL)isAllowAttendeeChat;
/**
 * @brief Query if attendee raise hand status.
 * @return If it is enabled, the return value is YES. Otherwise, the return value is NO.
 */
- (BOOL)isAllowRaiseHand;
/**
 * @brief Query if webinar supports attendee to talk.
 * @return YES means supporting the feature of allowing attendee to talk, otherwise not.
 */ 
- (BOOL)isSupportAttendeeTalk;

/**
 * @brief Query if emoji reactions status.
 * @return If it is enabled, the return value is YES. If not, the return value is NO.
 */
- (BOOL)isWebinarEmojiReactionAllowed;

/**
 * @brief Query if attendee to view the participant count status.
 * @return If this is enabled, the return value is YES. Otherwise the return value is NO.
 */
- (BOOL)canAttendeesViewParticipantCount;
@end

@interface ZoomSDKWebinarRegisterHelper :NSObject
{
    WebinarRegisterType   _webinarRegisterType;
}
/**
 * @brief Get type of user registers webinar.
 * @return The type of user to register webinar.
 */
-(WebinarRegisterType)getWebinarRegisterType;
/**
 * @brief Get URL of user registers webinar.
 * @return The url for user to register webinar.	
 */
-(NSURL*)getWebinarRegisterURL;
/**
 * @brief Input email and screen name to register webinar. 
 * @param email The email to register webinar
 * @param name The display name to register webinar.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
-(ZoomSDKError)inputEmail:(NSString*)email screenName:(NSString*)name;
/**
 * @brief Cancel to register webinar.
 */
-(ZoomSDKError)cancel;
@end


@protocol ZoomSDKWebinarControllerDelegate <NSObject>
@optional
/**
 * @brief Callback of users are allowed to talk in webinar. User needs to enable the mic in the view-only mode of webinar if he wants to talk.
 */
- (void)onSelfAllowTalkNoti;
/**
 * @brief Callback of users are disallowed to talk in webinar. 
 */
- (void)onSelfDisallowTalkNoti;
/**
 * @brief Callback to promote attendee to panelist.
 * @param result The result of promotion. If the promotion is successful, the result is zero(0). Otherwise it is an error code.
 */
- (void)onPromoteAttendee2PanelistResultNoti:(unsigned int)result;
/**
 * @brief Callback to demote panelist to attendee.
 * @param result The result of demotion. If the promotion is successful, the result is zero(0). Otherwise it is an error code.
 */
- (void)onDepromotePanelist2AttendeeResultNoti:(unsigned int)result;
/**
 * @brief Callback to enable the attendees to chat.
 */
- (void)onAllowAttendeeChatStatusChangedNoti DEPRECATED_MSG_ATTRIBUTE("Use -onChatStatusChangedNotification: instead");
/**
 * @brief Callback to disable the attendees to chat.
 */
- (void)onDisAllowAttendeeChatStatusChangedNoti DEPRECATED_MSG_ATTRIBUTE("Use -onChatStatusChangedNotification: instead");
/**
 * @brief Callback to enable the panelist to start the video.
 */
- (void)onAllowPanelistStartVideoNoti;
/**
 * @brief Callback to disable the panelist to start the video.
 */
- (void)onDisAllowPanelistStartVideoNoti;
/**
 * @brief Panelist will receive this callback if the attendee's audio status changed. 
 * @param userid The user ID of attendee whose audio status changes.
 * @param is_muted YES means the user is muted, otherwise not.
 */
- (void)onAttendeeAudioStatusNoti:(unsigned int)userid canTalk:(BOOL)can_talk isMuted:(BOOL)is_muted;
/**
 * @brief During the webinar, this callback will be triggered if the user needs to register.
 * @param webinarRegisterHelper An object used by user to complete all the related operations. 
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)onWebinarNeedRegisterResponse:(ZoomSDKWebinarRegisterHelper*)webinarRegisterHelper;
/**
 * @brief Panelist will receive this callback if the attendee's audio status changed.
 * @param userid The user ID of attendee whose promote.
 * @param agree YES means the user is agree join webinar as panelist.
 */
- (void)onAttendeePromoteConfirmResult:(unsigned int)userid isAgree:(BOOL)agree;

/**
 * @brief Callback for when the host enables/disables emoji reactions.
 * @param isAllowed If the reaction is allowed, the value of isAllow is true, otherwise false.
 */
- (void)onAllowWebinarReactionStatusChanged:(BOOL)isAllowed;

/**
 * @brief Callback to attendee raise hand status changed.
 * @param isAllowed If the raise hand is allowed, the result is YES. If not, the result is NO.
 */
- (void)onAllowAttendeeRaiseHandStatusChanged:(BOOL)isAllowed;

/**
 * @brief Callback to attendee view the participant count status changed.
 * @param isAllowed If attendees are allowed to view the participant count, the result is YES. Otherwise, the result is NO.
 */
- (void)onAllowAttendeeViewTheParticipantCountStatusChanged:(BOOL)isAllowed;
@end


/**
 * @brief Webinar controller interface.
 */
@interface ZoomSDKWebinarController : NSObject
{
    id<ZoomSDKWebinarControllerDelegate> _delegate;
    ZoomSDKWebinarMeetingStatus* _webinarMeetingStatus;
}
@property(nonatomic, assign)id<ZoomSDKWebinarControllerDelegate> delegate;
@property(nonatomic, retain)ZoomSDKWebinarMeetingStatus* webinarMeetingStatus;

/**
 * @brief Promote the specified attendee to panelist.
 * @param userId The ID of the specified attendee.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)PromoteAttendee2Panelist:(unsigned int)userId;

/**
 * @brief Demote the specified panelist to attendee.
 * @param userId The ID of the specified panelist. 
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)DepromotePanelist2Attendee:(unsigned int)userId;

/**
 * @brief The attendee is permitted to use the audio device.
 * @param userId Specify the permitted user ID.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)AllowAttendeeTalk:(unsigned int)userId;

/**
 * @brief Forbid the attendee to use the audio device.
 * @param userId Specify the forbidden user ID.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)DisallowAttendeeTalk:(unsigned int)userId;

/**
 * @brief The panelist is permitted to start the video.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)AllowPanelistStartVideo;

/**
 * @brief Forbid the panelist to start video.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)DisallowPanelistStartVideo;

/**
 * @brief The attendees are permitted to chat.
 * @param priviledge Specify the chat priviledge type.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)allowAttendeeChat:(ZoomSDKChatPriviledgeType)priviledge DEPRECATED_MSG_ATTRIBUTE("Use -setParticipantsChatPriviledge: instead");

/**
 * @brief Forbid the attendees to chat.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. 
 */
-(ZoomSDKError)DisallowAttendeeChat DEPRECATED_MSG_ATTRIBUTE("Use -setParticipantsChatPriviledge: instead");

/**
 * @brief Get the webinar status.
 * @return If the function succeeds, it will return an object of ZoomSDKWebinarMeetingStatus.
 */
-(ZoomSDKWebinarMeetingStatus*)getZoomSDKWebinarMeetingStatus;

/**
 * @brief Get the list of attendees in the meeting.
 * @return If the function succeeds, it will return an NSArray of attendees.
 */
- (NSArray*)getAttendeeList;

/**
 * @brief Set the chat privilege of the panelist.
 * @param privilege The chat privilege of the panelist.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)setPanelistChatPrivilege:(ZoomSDKPanelistChatPrivilege)privilege;

/**
 * @brief Get the chat privilege of the panelist.
 * @param privilege The chat privilege of the panelist. It validates only when the return value is ZoomSDKError_Success.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)getPanelistChatPrivilege:(ZoomSDKPanelistChatPrivilege*)privilege;

/**
 * @brief Set the view mode of the attendee.
 * @param mode The view mode of the attendee. For more details see {@link ZoomSDKAttendeeViewMode}.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise the function returns an error.
 */
- (ZoomSDKError)setAttendeeViewMode:(ZoomSDKAttendeeViewMode)mode;

/**
 * @brief Get the view mode of the attendee.
 * @return If the function succeeds, it will return the attendee's view mode. For more details, see {@link ZoomSDKAttendeeViewMode}.
 */
- (ZoomSDKAttendeeViewMode)getAttendeeViewMode;

/**
 * @brief Permitted to use emoji reactions.
 * @note If the function succeeds, the user receives the '- (void)onAllowWebinarReactionStatusChanged:(BOOL)isAllowed' callback event. Available only for the host.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)allowWebinarEmojiReaction;

/**
 * @brief Forbid use of emoji reactions.
 * @note If the function succeeds, the user receives the '- (void)onAllowWebinarReactionStatusChanged:(BOOL)isAllowed' callback event. Available only for the host.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)disallowWebinarEmojiReaction;

/**
 * @brief The attendees can raise their hands.
 * @note If the function succeeds, the user receives the '- (void)onAllowAttendeeRaiseHandStatusChanged:(BOOL)isAllowed' callback event. Available only for the host.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)allowAttendeeRaiseHand;

/**
 * @brief Do not let the attendee to raise their hand.
 * @note If the function succeeds, the user receives the '- (void)onAllowAttendeeRaiseHandStatusChanged:(BOOL)isAllowed' callback event. Available only for the host.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)disallowAttendeeRaiseHand;

/**
 * @brief The attendee is permitted to view the participant count.
 * @note If the function succeeds, the user receives the '- (void)onAllowAttendeeViewTheParticipantCountStatusChanged:(BOOL)isAllowed' callback event. Available only for the host.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)allowAttendeeViewTheParticipantCount;

/**
 * @brief Forbid the attendee to view the participant count.
 * @note If the function succeeds, the user receives the '- (void)onAllowAttendeeViewTheParticipantCountStatusChanged:(BOOL)isAllowed' callback event. Available only for the host.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)disallowAttendeeViewTheParticipantCount;

/**
 * @brief Get the participant count.
 * @return The participant count of.
 */
- (int)getParticipantCount;

/**
 @brief Get the webinal legal notices prompt.
 @return If the function succeeds, it will return the webinal legal notices prompt. Otherwise nil.
 */
- (NSString *)getWebinarRegistrationLegalNoticesPrompt;

/**
 @brief Get the webinal legal notices explained.
 @return If the function succeeds, it will return the webinal legal notices explained. Otherwise nil.
 */
- (ZoomSDKWebinarRegistrationExplainInfo *)getWebinarRegistrationLegalNoticesExplained;
@end
