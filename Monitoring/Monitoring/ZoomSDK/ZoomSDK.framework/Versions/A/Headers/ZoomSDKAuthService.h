

#import <Cocoa/Cocoa.h>
#import "ZoomSDKErrors.h"
#import "ZoomSDKNotificationServiceController.h"

@interface ZoomSDKAuthContext : NSObject

/**
 *@brief jwtToken The new auth token.
 */
@property(nonatomic, copy) NSString *jwtToken;

@end

@interface ZoomSDKWebinarRegistrationExplainInfo : NSObject
/**
 *@brief content content of the webinar Registration Explain Info
 */
@property(nonatomic, copy,readonly) NSString *content;
/**
 *@brief accountOwnerLink accountOwnerLink of the webinar Registration Explain Info
 */
@property(nonatomic, copy,readonly) NSString *accountOwnerLink;
/**
 *@brief termLink termLink of the webinar Registration Explain Info
 */
@property(nonatomic, copy,readonly) NSString *termLink;
/**
 *@brief policyLink policyLink of the webinar Registration Explain Info
 */
@property(nonatomic, copy,readonly) NSString *policyLink;

@end

@interface ZoomSDKAccountInfo : NSObject
/**
 * @brief Get user's screen name.
 * @return If the function succeeds, it will return user's screen name. 
 */
- (NSString*) getDisplayName;
/**
 * @brief Get the type of user.
 * @return If the function succeeds, it will return the type of the user,
 */
- (ZoomSDKUserType) getSDKUserType;
@end

@protocol ZoomSDKAuthDelegate;
/**
 * @brief Callback event of ZOOM SDK authorization. 
 * Authorize Zoom SDK and the custom application with the key/secret before usage. Once authorize successfully, ZoomSDKAuthDelegate will return ZoomSDKAuthError_Success via onZoomSDKAuthReturn.
 * @note You should authorize ZOOM SDK firstly before using it, or no, it may not work.
 */
@interface ZoomSDKAuthService : NSObject
{
    id<ZoomSDKAuthDelegate> _delegate;
}
@property (assign, nonatomic) id<ZoomSDKAuthDelegate> delegate;

/**
 @brief New authenticate SDK.
 @param jwttoken A Class object containing auth information.
 @return If the function succeeds, it will return ZoomSDKError_Success.
 @note If the jwttoken expired,will return "onZoomAuthIdentityExpired" callback.
 */
- (ZoomSDKError)sdkAuth:(ZoomSDKAuthContext*)jwttoken;

/**
 * @brief Determine if SDK is authorized.
 * @return YES means that it is authorized, otherwise failed.
 */
- (BOOL)isAuthorized;

/**
* @brief Generate SSO login web url.
* @param prefixOfVanityUrl The prefix of vanity url.
* @return If the function succeeds,will return url of can launch app.
*/
- (NSString*)generateSSOLoginWebURL:(NSString*)prefixOfVanityUrl;

/**
 * @brief Login ZOOM with uri protocol.
 * @param uriProtocol For the parameter to be used for sso account login.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)SSOLoginWithWebUriProtocol:(NSString*)uriProtocol;
/**
 * @brief Logout ZOOM.
 * @return If the function succeeds, it will return ZoomSDKError_Success, meanwhile it will call asynchronously onZoomSDKLogout.
 */
- (ZoomSDKError)logout;

/**
 * @brief Get user's account information. 
 * @return When user logged in, it will return ZoomSDKAccountInfo object if the function calls successfully. Otherwise returns nil.
 */
- (ZoomSDKAccountInfo*)getAccountInfo;

/**
 * @brief Get SDK identity.
 * @return The SDK identity.
 */
- (NSString*)getSDKIdentity;

/**
 * @brief Enable or disable auto register notification service. This is enabled by default.
 * @param enable YES means enabled, otherwise not.
 */
- (void)enableAutoRegisterNotificationServiceForLogin:(BOOL)enable;

/**
 * @brief Register notification service.
 * @param accessToken Initialize parameter of notification service.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)registerNotificationService:(NSString*)accessToken;

/**
 * @brief Unregister notification service.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)unregisterNotificationService;

/**
 * @brief Get notification service controller interface.
 * @return If the function succeeds, it will return a ZoomSDKZpnsServiceController object.
 */
- (ZoomSDKNotificationServiceController *)getNotificationServiceController;
@end


@protocol ZoomSDKAuthDelegate <NSObject>

@required
/**
 * @brief Specify to get the response of ZOOM SDK authorization. 
 * @param returnValue Notify user that the authentication status changes.
 *
 */
- (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue;

/**
 @brief Specify to get the response of ZOOM SDK authorization identity expired.
 */
 - (void)onZoomAuthIdentityExpired;

@optional
/**
 * @brief Specify to get the response of ZOOM SDK Login.
 * @param loginStatus Notify user of login status.
 * @param reason Notify user that the failed reason.
 */
- (void)onZoomSDKLoginResult:(ZoomSDKLoginStatus)loginStatus failReason:(ZoomSDKLoginFailReason)reason;
/**
 * @brief Specify to get the response of ZOOM SDK logout.
 */
- (void)onZoomSDKLogout;

/**
 * @brief Specify to get the response if ZOOM identity is expired.
 * @note User will be forced to logout once ZOOM SDK identity expired.
 */
- (void)onZoomIdentityExpired;

/**
 * @brief Notification service status changed callback.
 * @param status The value of transfer meeting service. For more details, see {@link ZoomSDKNotificationServiceStatus}.
 */
- (void)onNotificationServiceStatus:(ZoomSDKNotificationServiceStatus)status DEPRECATED_MSG_ATTRIBUTE("Use -onNotificationServiceStatus:error: instead");

/**
 * @brief Notification service status changed callback.
 * @param status The value of transfer meeting service. For more details, see {@link ZoomSDKNotificationServiceStatus}.
 * @param error Connection Notification service fail error code. For more details, see {@link ZoomSDKNotificationServiceError}.
 */
- (void)onNotificationServiceStatus:(ZoomSDKNotificationServiceStatus)status error:(ZoomSDKNotificationServiceError)error;
@end
