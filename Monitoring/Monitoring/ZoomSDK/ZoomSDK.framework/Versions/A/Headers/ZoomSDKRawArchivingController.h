//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZoomSDKRawArchivingController : NSObject

/**
 * @brief Start raw archiving, call this method can get rawdata receive privilege.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
-(ZoomSDKError)startRawArchiving;

/**
 * @brief Stop raw archiving, call this method reclaim rawdata receive privilege.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
-(ZoomSDKError)stopRawArchiving;
@end

NS_ASSUME_NONNULL_END
