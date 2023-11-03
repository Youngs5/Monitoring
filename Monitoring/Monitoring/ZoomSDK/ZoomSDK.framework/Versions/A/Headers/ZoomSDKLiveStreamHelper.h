

#import "ZoomSDKErrors.h"
/**
 * @brief ZOOM SDK live stream item.
 */
@interface ZoomSDKLiveStreamItem : NSObject
/**
 * @brief Get live stream URL.
 * @return The live stream URL.							   
 */
-(NSString*)getLiveStreamURL;
/**
 * @brief Get description of live stream URL.
 * @return The descriptions of live stream URL.
 */
-(NSString*)getLiveStreamURLDescription;
@end

/**
 * @brief Information of raw live stream info.
 */
@interface ZoomSDKRawLiveStreamInfo : NSObject
/**
 * @brief Get the user ID.
 */
@property(nonatomic, assign, readonly) unsigned int userID;
/**
 * @brief Get the broadcast URL.
 */
@property(nonatomic, copy, readonly) NSString *broadcastUrl;
/**
 * @brief Get the broadcast name.
 */
@property(nonatomic, copy, readonly) NSString *broadcastName;
@end


/**
 * @brief Process after the host receives the requirement from the user to give the raw live stream privilege.
 */
@interface ZoomSDKRequestRawLiveStreamPrivilegeHandler : NSObject
/**
 * @brief Get the request ID.
 */
@property(nonatomic, copy, readonly) NSString *requestId;
/**
 * @brief Get the user ID who requested privilege.
 */
@property(nonatomic, assign, readonly) unsigned int requesterId;
/**
 * @brief Get the user name who requested privileges.
 */
@property(nonatomic, copy, readonly) NSString *requesterName;
/**
 * @brief Get the broadcast URL.
 */
@property(nonatomic, copy, readonly) NSString *broadcastUrl;
/**
 * @brief Get the broadcast name.
 */
@property(nonatomic, copy, readonly) NSString *broadcastName;

/**
 * @brief Allows the user to start raw live stream and finally self-destroy.
 * @return If the function succeeds, the return value ZoomSDKErrors_Success.
 */
- (ZoomSDKError)grantRawLiveStreamPrivilege;

/**
 * @brief Denies the user permission to start raw live stream and finally self-destroy.
 * @return If the function succeeds, the return value ZoomSDKError_Success.
 */
- (ZoomSDKError)denyRawLiveStreamPrivilege;
@end


@protocol ZoomSDKLiveStreamHelperDelegate <NSObject>
/**
 * @brief Callback event when live stream status changes.
 * @param Status The live streaming status.
 */
- (void)onLiveStreamStatusChange:(LiveStreamStatus)status;

/**
 * @brief Callback event when the current user's raw live streaming privilege changes.
 * @param bHasPrivilege Specify whether or not the user has privilege.
 */
- (void)onRawLiveStreamPrivilegeChanged:(BOOL)bHasPrivilege;

/**
 * @brief Callback event when the current user's request has times out.
 */
- (void)onRawLiveStreamPrivilegeRequestTimeout;

/**
 * @brief Callback event when another user's raw live streaming privilege changes.
 * @param userID The ID of the user whose privilege changed.
 * @param bHasPrivilege Specify whether or not the user has privilege.
 */
- (void)onUserRawLiveStreamPrivilegeChanged:(unsigned int)userID hasPrivilege:(BOOL)bHasPrivilege;

/**
 * @brief Callback event when a user requests raw live streaming privilege.
 * @param handler A pointer to the ZoomSDKRequestRawLiveStreamPrivilegeHandler.
 */
- (void)onRawLiveStreamPrivilegeRequested:(ZoomSDKRequestRawLiveStreamPrivilegeHandler*)handler;

/**
 * @brief Callback event when users start or stop raw live streaming.
 * @param liveStreamList A list of users with an active raw live stream.
 */
- (void)onUserRawLiveStreamingStatusChanged:(NSArray<ZoomSDKRawLiveStreamInfo*>*)liveStreamList;
@end



@interface ZoomSDKLiveStreamHelper : NSObject
{
    id<ZoomSDKLiveStreamHelperDelegate> _delegate;
}
@property(nonatomic, assign)id<ZoomSDKLiveStreamHelperDelegate> delegate;
/**
 * @brief Query if it is able for the user to enable live stream.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise failed.
 */

- (ZoomSDKError)canStartLiveStream;

/**
 * @brief Get the items of live stream supported by the SDK.
 * @return If the function succeeds, it will return the items, otherwise failed.
 */

-(NSArray*)getSupportLiveStreamItem;

/**
 * @brief Start a live stream.
 * @param item The item of live stream supported by the SDK.
 * @return If the function succeeds, it will return the ZoomSDKError_Success, otherwise failed. 
 */
-(ZoomSDKError)startLiveStream:(ZoomSDKLiveStreamItem*)item;

/**
 * @brief Start a live stream with the URL customized by user.
 * @param streamURL The URL of customized live stream.
 * @param key The key of customized stream stream.
 * @param broadcastURL Everyone who uses this link can watch the live broadcast.
 * @return If the function succeeds, it will return the ZoomSDKError_Success, otherwise failed.
 */
-(ZoomSDKError)startLiveStreamByURL:(NSString*)streamURL StreamKey:(NSString*)key BroadcastURL:(NSString*)broadcastURL;

/**
 * @brief Stop a live stream.
 * @return If the function succeeds, it will return the ZoomSDKError_Success, otherwise failed.
 */
-(ZoomSDKError)stopLiveStream;

/**
 * @brief Get the status of current live stream.
 * @return If the function succeeds, it will return the LiveStreamStatus_InProgress, otherwise failed.
 */
-(LiveStreamStatus)getLiveStreamStatus;

/**
 * @brief Query Whether the meeting supports raw live streams.
 * @return Yes if supported, NO if not supported.
 */
-(BOOL)isRawLiveStreamSupported;

/**
 * @brief Whether if the current user is able to start raw live streaming.
 * @return If the current user is able to start raw live streaming, the return value is ZoomSDKError_Success, otherwise failed.
 */
-(ZoomSDKError)canStartRawLiveStream;

/**
 * @brief Send a request to enable the SDK to start a raw live stream.
 * @param broadcastURL The broadcast URL of the live-stream.
 * @return If the function succeeds, the return value is ZoomSDKError_Success and the SDK will send the request, otherwise it fails and the request will not be sent.
 */
-(ZoomSDKError)requestRawLiveStream:(NSString*)broadcastURL DEPRECATED_MSG_ATTRIBUTE("Use -requestRawLiveStreaming: broadcastName: instead");

/**
 * @brief Send a request to enable the SDK to start a raw live stream.
 * @param broadcastURL The broadcast URL of the live-stream.
 * @param broadcastName The broadcast name of the live-stream.
 * @return If the function succeeds, the return value is ZoomSDKError_Success and the SDK will send the request, otherwise it fails and the request will not be sent.
 */
-(ZoomSDKError)requestRawLiveStreaming:(NSString*)broadcastURL broadcastName:(NSString*)broadcastName;

/**
 * @brief Start raw live streaming.
 * @param broadcastURL The broadcast URL of the live-stream.
 * @return If the function succeeds, it will return the ZoomSDKError_Success, otherwise failed.
 */
-(ZoomSDKError)startRawLiveStream:(NSString *)broadcastURL DEPRECATED_MSG_ATTRIBUTE("Use -startRawLiveStreaming: broadcastName: instead");

/**
 * @brief Start raw live streaming.
 * @param broadcastURL The broadcast URL of the live-stream.
 * @param broadcastName The broadcast name of the live-stream.
 * @return If the function succeeds, it will return the ZoomSDKError_Success, otherwise failed.
 */
-(ZoomSDKError)startRawLiveStreaming:(NSString *)broadcastURL broadcastName:(NSString*)broadcastName;

/**
 * @brief Stop raw live streaming.
 * @return If the function succeeds, it will return the ZoomSDKError_Success, otherwise failed.
 */
-(ZoomSDKError)stopRawLiveStream;

/**
 * @brief Remove the raw live stream privilege.
 * @param userID Specify the ID of the user whose privilege will be removed.
 * @return If the function succeeds, the return value is ZoomSDKError_Success, otherwise it fails.
 */
-(ZoomSDKError)removeRawLiveStreamPrivilege:(unsigned int)userID;

/**
 * @brief Get a list of current active raw live streams.
 * @return If the function succeeds, the return value is a pointer to the NSArray object, otherwise nil.
 */
-(NSArray<ZoomSDKRawLiveStreamInfo*>*)getRawLiveStreamingInfoList;

/**
 * @brief Get the list of users’ IDs who have raw live stream privileges.
 * @return If the function succeeds, the return value is a pointer to the NSArray object.
 */
-(NSArray<NSNumber*>*)getRawLiveStreamPrivilegeUserList;
@end
