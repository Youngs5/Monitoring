
#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"


@interface ZoomSDKCustomImmersiveContainer : NSObject
@property(nonatomic, assign, readonly) NSView* containerView;

/**
 * @brief Resize the immersive container in the specified area and reset the parent window.
 * @param rect a new display area. The coordinate value of the structure is that of the parent window of immersive container.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)repositionContainer:(NSRect)rect;

/**
 * @brief Show the waiting area before start immersive.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)showWaitingArea;

/**
 * @brief Hide the waiting area before start immersive.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)hideWaitingArea;
@end

/**
 * @brief Type of immersive template.View more detailed structural descriptions.
 */
typedef enum
{
    ZoomSDKCustomImmersiveTemplateType_Default, //The default template.
    ZoomSDKCustomImmersiveTemplateType_CustomImage, //A template using a custom image.
    ZoomSDKCustomImmersiveTemplateType_MyVideo   //The my video template.
}ZoomSDKCustomImmersiveTemplateType;


/**
 * @brief Information of seat placement in a template.
 */
@interface ZoomSDKSeatPlacementInfo : NSObject
/**
 * @brief The seat ID.
 */
@property(nonatomic, copy, readonly) NSString* seatID;
/**
 * @brief The position of seat.
 */
@property(nonatomic, assign, readonly) NSRect position;
@end


/**
 * @brief Layout data for the immersive view.
 */
@interface ZoomSDKCustomImmersiveLayoutData : NSObject
/**
 * @brief Whether this user is in a seat.
 */
@property(nonatomic,assign) BOOL isSeatFree;
/**
 * @brief The seat ID.
 */
@property(nonatomic,copy) NSString* seatID;
/**
 * @brief The user ID.
 */
@property(nonatomic,assign) unsigned int userID;
/**
 * @brief The seat z order.
 */
@property(nonatomic,assign, readonly) unsigned int zOrder;
/**
 * @brief The seat position.
 */
@property(nonatomic,assign) NSRect position;
@end



/**
 * @brief Immersive template object interface.
 */
@interface ZoomSDKCustomImmersiveTemplate : NSObject
/**
 * @brief The name of template.
 */
@property(nonatomic,copy, readonly) NSString* templateName;
/**
 * @brief The bitmap of thumbnail.
 */
@property(nonatomic,retain, readonly) NSBitmapImageRep* thumbnailBitmap;
/**
 * @brief The capacity of template.
 */
@property(nonatomic,assign, readonly) unsigned int capacity;
/**
 * @brief Determine if the template is ready.
 */
@property(nonatomic,assign, readonly) BOOL isTemplateReady;
/**
 * @brief Determine if the template support free seat.
 */
@property(nonatomic,assign, readonly) BOOL isSupportFreeSeat;
/**
 * @brief The size of this template.
 */
@property(nonatomic,assign, readonly) NSSize canvasSize;
/**
 * @brief The type of this template.
 */
@property(nonatomic,assign, readonly) ZoomSDKCustomImmersiveTemplateType templateType;
/**
 * @brief The list of template seats.
 */
@property(nonatomic,retain, readonly) NSArray<ZoomSDKSeatPlacementInfo*>* seatList;
@end


@protocol ZoomSDKCustomImmersiveDelegate <NSObject>
/**
 * @brief Callback event that the immersive view was enabled/disabled.
 * @param isOn The status of immersive status.
 */
- (void)onImmersiveStatusChanged:(BOOL)isOn;

/**
 * @brief Callback event that the selected immersive template changed.
 * @param immersiveTemplate  The new template. For more details, see {@link ZoomSDKCustomImmersiveTemplate}.
 */
- (void)onSelectedImmersiveTemplateChanged:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate;

/**
 * @brief Callback event that the immersive seat layout changed.
 * @param data The list contains the seat layout of immersive.
 */
- (void)onImmersiveSeatLayoutUpdated:(NSArray<ZoomSDKCustomImmersiveLayoutData*>*)data;

/**
 * @brief Callback event for the immersive template download process.
 * @param immersiveTemplate  The new template. For more details, see {@link ZoomSDKCustomImmersiveTemplate}.
 * @param progress The process.
 */
- (void)onTemplateDownloadProgress:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate progress:(unsigned int)progress;

/**
 * @brief Callback event for the immersive template download end.
 * @param immersiveTemplate The new template. For more details, see {@link ZoomSDKCustomImmersiveTemplate}.
 * @param bSuccess The download result.
 */
- (void)onTemplateDownloadEnded:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate bSuccess:(BOOL)bSuccess;

/**
 * @brief Callback event that template thumbnails download end.
 * @param bSuccess YES means download success. Otherwise not.
 */
- (void)onTemplateThumbnailsDownloadEnded:(BOOL)bSuccess;

/**
 * @brief The callback will be triggered before the immersive container is destroyed.
 * @note The immersive container will be destroyed once the function calls end. The user should complete the operations related to the immersive container before the function calls end.
 */
- (void)onImmersiveContainerDestroyed;
@end


/**
 * @brief Meeting immersive controller interface. For more details on this feature, see https://support.zoom.us/hc/en-us/articles/360060220511-Immersive-View
 */
@interface ZoomSDKCustomImmersiveController : NSObject
@property(nonatomic,assign) id<ZoomSDKCustomImmersiveDelegate> delegate;

/**
 * @brief Determine if immersive view is active.
 * @return YES means the immersive view is active. Otherwise NO.
 */
- (BOOL)isImmersiveViewOn;

/**
 * @brief Determine if immersive is supported.
 * @return YES means support immersive. Otherwise NO.
 */
- (BOOL)isSupportImmersive;

/**
 * @brief Determine if the thumbnails are ready.
 * @return YES means the immersive thumbnails are ready, NO not.
 */
- (BOOL)isTemplateThumbnailsReady;

/**
 * @brief Determine if the immersive template can be started.
 * @param immersiveTemplate The selected template in immersive view. For more details, see {@link ZoomSDKCustomImmersiveTemplate}
 * @return YES means the immersive can be started, otherwise not.
 */
- (BOOL)canStartImmersiveView:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate;

/**
 * @brief Start immersive view.
 * @param immersiveTemplate The selected template in immersive view. For more details, see {@link ZoomSDKCustomImmersiveTemplate}.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)startImmersiveView:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate;

/**
 * @brief Change template in immersive view.
 * @param immersiveTemplate The selected template in immersive view. For more details, see {@link ZoomSDKCustomImmersiveTemplate}
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)changeTemplate:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate;

/**
 * @brief Exit immersive view.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}
 */
- (ZoomSDKError)endImmersiveView;

/**
 * @brief Determine if the user can be shown in immersive view.
 * @param userid The user ID.
 * @return YES means the user can be shown in immersive view, NO if they cannot.
 */
- (BOOL)canUserShowInImmersiveView:(unsigned int)userID;

/**
 * @brief Get the immersive seat layout data.
 * @return If the function succeeds, it will return the immersive seat layout data. Otherwise the function returns nil.
 */
- (NSArray<ZoomSDKCustomImmersiveLayoutData*>*)getLayoutData;

/**
 * @brief Update the layout data.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise the function returns an error.
 */
- (ZoomSDKError)updateLayoutData:(NSArray<ZoomSDKCustomImmersiveLayoutData*>*)dataArray;

/**
 * @brief Put the user in the seat.
 * @param userid The user ID.
 * @param seatID The seat ID.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)assignUser:(unsigned int)userID seatID:(NSString*)seatID;

/**
 * @brief Put the user in the free seat.
 * @param userid The user ID.
 * @param pos The position.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)putUserToFreeSeat:(unsigned int)userID pos:(NSRect)pos;

/**
 * @brief Remove user from immersive view.
 * @param userid The user ID.
 * @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)removeUser:(unsigned int)userID;

/**
 * @brief Determine if the user is in immersive view.
 * @param userid The user ID.
 * @return YES means the user is in immersive view, NO means that they are not.
 */
- (BOOL)isUserInImmersiveView:(unsigned int)userID;

/**
 * @brief Download the template thumbnails. See {@link ZoomSDKCustomImmersiveDelegate} for updates on the download.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.To get extended error information, see {@link ZoomSDKError}
 */
- (ZoomSDKError)downloadTemplateThumbnails;

/**
 * @brief Download complete template resource.
 * @param immersiveTemplate The template be downloaded. For more details, see @{@link ZoomSDKCustomImmersiveTemplate}.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}
 */
- (ZoomSDKError)downloadTemplate:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate;

/**
 * @brief Add a template based on a custom image.
 * @param filePath The image file path.
 * @param immersiveTemplate If the function succeeds, the object will be ZoomSDKCustomImmersiveTemplate, otherwise nil.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)addCustomImageTemplate:(NSString*)filePath template:(ZoomSDKCustomImmersiveTemplate**)immersiveTemplate;

/**
 * @brief Remove custom immersive template.
 * @param immersiveTemplate The custom image template that want to remove. For more details, see {@link ZoomSDKCustomImmersiveTemplate}.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed. To get extended error information, see {@link ZoomSDKError}.
 */
- (ZoomSDKError)removeCustomImageTemplate:(ZoomSDKCustomImmersiveTemplate*)immersiveTemplate;

/**
 * @brief Get the current template.
 * @return If the function succeeds, the return value is the current template. For more details, see {@link ZoomSDKCustomImmersiveTemplate}.
 */
- (ZoomSDKCustomImmersiveTemplate*)getCurrentTemplate;

/**
 * @brief Get the list of templates.
 * @return The list of templates. ZERO(0) indicates that there are no templates. For more details, see {@link ZoomSDKCustomImmersiveTemplate}.
 */
- (NSArray<ZoomSDKCustomImmersiveTemplate*>*)getTemplates;

/**
 * @brief Create the immersive container for customUI
 * @param rect Specify the position of client area of the immersive container.
 * @return If the function succeeds, it will return the object of ZoomSDKCustomImmersiveContainer. Otherwise nil.
 */
- (ZoomSDKCustomImmersiveContainer*)createImmersiveContainer:(NSRect)rect;

/**
 * @brief Destroy the immersive container. Once destroyed, the container can no longer be used.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)destroyImmersiveContainer;
@end
