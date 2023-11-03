

@class ZoomSDKUserInfo;

@interface ZoomSDKCustomWaitingRoomData : NSObject
/**
 * @brief The title.
 */
@property (copy, nonatomic, readonly) NSString* title;
/**
 * @brief The description.
 */
@property (copy, nonatomic, readonly) NSString* dataDescription;
/**
 * @brief The path of logo image.
 */
@property (copy, nonatomic, readonly) NSString* logoPath;
/**
 * @brief The path of video file.
 */
@property (copy, nonatomic, readonly) NSString* videoPath;
/**
 * @brief The type.
 */
@property (assign, nonatomic, readonly) ZoomSDKWaitingRoomLayoutType type;
/**
 * @brief The status.
 */
@property (assign, nonatomic, readonly) ZoomSDKCustomWaitingRoomDataStatus status;
@end


/**
 * @brief Handler to download waiting room customize data if download fail.
 */
@interface ZoomSDKWaitingRoomDataDownloadHandler : NSObject
/**
 * @brief Retry to download the waiting room customize data information in the waiting room.
 */
-(void)retry;
/**
 * @brief Ignore to downloade the waiting room customize data information in the waiting room.
 */
-(void)ignore;
@end



@protocol ZoomSDKWaitingRoomDelegate <NSObject>
/**
 * @brief Callback of that user joins waiting room.
 * @param userid The ID of user who joins waiting room.
 */
-(void)onUserJoinWaitingRoom:(unsigned int)userid;
/**
 * @brief Callback of that user leaves waiting room.
 * @param userid The ID of user who leaves waiting room.
 */
-(void)onUserLeftWaitingRoom:(unsigned int)userid;

/**
 * @brief During the waiting room, this callback event will be triggered when host change audio status.
 * @param audioCanTurnOn YES means audio can be turned on. Otherwise not.
 */
-(void)onWaitingRoomPresetAudioStatusChanged:(BOOL)audioCanTurnOn;

/**
 * @brief During the waiting room, this callback event will be triggered when host change video status.
 * @param videoCanTurnOn YES means video can be turned on. Otherwise not.
 */
-(void)onWaitingRoomPresetVideoStatusChanged:(BOOL)videoCanTurnOn;

/**
 * @brief Callback of that customize data info updated.
 * @param bData The object of ZoomSDKCustomWaitingRoomData.
 * @param handle The object of ZoomSDKWaitingRoomDataDownloadHandler to handle download failed
 */
-(void)onCustomWaitingRoomDataUpdated:(ZoomSDKCustomWaitingRoomData*)bData handle:(ZoomSDKWaitingRoomDataDownloadHandler*)handle;

/**
 * @brief Callback indicating that the name of a user in the waiting room has changed.
 * @param userID The ID of the user whose user name has changed.
 * @param userName The new user name.
 */
- (void)onWaitingRoomUserNameChanged:(unsigned int)userID userName:(NSString *)userName;
@end

@interface ZoomSDKWaitingRoomController : NSObject
{
    id<ZoomSDKWaitingRoomDelegate> _delegate;
}
@property (assign, nonatomic) id<ZoomSDKWaitingRoomDelegate> delegate;
/**
 * @brief Query if the meeting supports waiting room.
 * @return YES means supported, otherwise not.
 */
- (BOOL)isSupportWaitingRoom;
/**
 * @brief Query if waiting room is enabled in current meeting.
 * @return YES means enabled, otherwise not.	
 */
- (BOOL)isEnableWaitingRoomOnEntry;
/**
 * @brief Set to enable/disable waiting room.
 * @param enable YES means enabled, NO disabled.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)enableWaitingRoomOnEntry:(BOOL)enable;
/**
 * @brief Get the list of users in the waiting room.
 * @return If the function succeeds, it will return a NSArray.
 */
- (NSArray*)getWaitRoomUserList;
/** 
 * @brief Get the information of users in the waiting room.
 * @param userid The ID of user who is in the waiting room.
 * @return If the function succeeds, it will return the object of ZoomSDKUserInfo for the specified user.
 */
- (ZoomSDKUserInfo*)getWaitingRoomUserInfo:(unsigned int)userid;
/**
 * @brief Admit user to join meeting.
 * @param userid The ID of user who joins meeting.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)admitToMeeting:(unsigned int)userid;

/**
 * @brief  Permit all of the users currently in the waiting room to join the meeting.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)admitAllToMeeting;

/**
 * @brief Put user into waiting room.
 * @param userid The ID of user who is put into waiting room by host/co-host.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)putIntoWaitingRoom:(unsigned int)userid;

/**
 * @brief Determine if the attendee is enabled to turn on audio when joining the meeting.
 * @return True indicates to enable to turn on.
 */
- (BOOL)isAudioEnabledInWaitingRoom;

/**
 * @brief Determine if the attendee is enabled to turn on video when joining the meeting.
 * @return True indicates to enable to turn on.
 */
- (BOOL)isVideoEnabledInWaitingRoom;

/**
 * @brief Get the WaitingRoom CustomizeData information in the waiting room.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)requestCustomWaitingRoomData;

/**
 * @brief Determine if the host or cohost can rename users in the waiting room.
 * @return YES means the host or cohost can rename users in the waiting room. Otherwise they can’t.
 */
- (BOOL)canRenameUser;

/**
 * @brief Change a user's screen name in the waiting room.
 * @param userID The ID of users put into the waiting room by a host or cohost.
 * @param userName The new user name.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)renameUser:(unsigned int)userID newUserName:(NSString *)userName;

/**
 * @brief Determine if a host or cohost can expel users in the waiting room.
 * @return YES means that a host or cohost can expel users in the waiting room. Otherwise they may not.
 */
- (BOOL)canExpelUser;

/**
 * @brief Remove a specified user from the waiting room.
 * @param userID The ID of the user  removed from the waiting room by a host or cohost.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)expelUser:(unsigned int)userID;
@end
