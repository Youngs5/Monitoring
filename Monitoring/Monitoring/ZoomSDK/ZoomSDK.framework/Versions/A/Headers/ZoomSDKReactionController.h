

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

NS_ASSUME_NONNULL_BEGIN

@protocol ZoomSDKReactionControllerDelegate <NSObject>

/**
 * @brief Notify receive the emoji reaction.
 * @param userid The user id of the send emoji reaction.
 * @param type The send emoji reaction type.
 * @param skinTone The send emoji reaction skinstone.
 */
-(void)onEmojiReactionReceived:(unsigned int)userid reactionType:(ZoomSDKEmojiReactionType)type reactionSkinTone:(ZoomSDKEmojiReactionSkinTone)skinTone;

/**
 * @brief Emoji reaction callback. This callback notifies the user when an emoji is received in the webinar.
 * @param type Specify the type of the received reaction.
 */
-(void)onEmojiReactionReceivedInWebinar:(ZoomSDKEmojiReactionType)type;

/**
 * @brief Emoji feedback received callback. This function is used to inform the user once received the emoji feedback sent by others or user himself.
 *  @param userid Specify the user id of the emoji feedback sender.
 * @param type Specify the type of the received emoji feedback.
 */
-(void)onEmojiFeedbackReceived:(unsigned int)userid emojiFeedbackType:(ZoomSDKEmojiFeedbackType)type;

/**
 * @brief Emoji feedback canceled callback. This function is used to inform the user once the received emoji feedback sent by others or user himself was canceled.
 * @param userid Specify the user id of the emoji feedback sender.
 */
-(void)onEmojiFeedbackCanceled:(unsigned int)userid;

@end

@interface ZoomSDKReactionController : NSObject
{
    id<ZoomSDKReactionControllerDelegate> _delegate;
}
@property (assign, nonatomic) id<ZoomSDKReactionControllerDelegate> delegate;

/**
 * @brief Determine if the Reaction function is enabled.
 * @return YES means Reaction function is enable,otherwise not.
 */
-(BOOL)isEmojiReactionEnabled;

/**
 * @brief Send emoji reaction.
 * @param type The type of the emoji reaction.
 * @param skinTone The skintone of the emoji reaction
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
-(ZoomSDKError)sendEmojiReaction:(ZoomSDKEmojiReactionType)type reactionSkinTone:(ZoomSDKEmojiReactionSkinTone)skinTone DEPRECATED_MSG_ATTRIBUTE("Use -sendEmojiReaction: instead");

/**
 * @brief Send emoji reaction.
 * @param type The type of the emoji reaction.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
-(ZoomSDKError)sendEmojiReaction:(ZoomSDKEmojiReactionType)type;

/**
 * @brief Set emoji reaction display type in webinar.
 * @param type The display type of the emoji reaction. For more details see {@link ZoomSDKEmojiReactionDisplayType}.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise the function returns an error.
 */
-(ZoomSDKError)setWebinarEmojiReactionDisplayType:(ZoomSDKEmojiReactionDisplayType)type;

/**
 * @brief Get emoji reaction display type in webinar. For more details see {@link ZoomSDKEmojiReactionDisplayType}
 * @return If the function succeeds, it will return the display type of the emoji reaction. Otherwise, the function returns ZoomSDKEmojiReactionDisplayType_None.
 */
-(ZoomSDKEmojiReactionDisplayType)getWebinarEmojiReactionDisplayType;

/**
 * @brief Send the emoji feedback.
 * @param type Specify the emoji feedback type to be sent.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise the function returns an error.
 */
-(ZoomSDKError)sendEmojiFeedback:(ZoomSDKEmojiFeedbackType)type;

/**
 * @brief Cancel the emoji feedback.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise the function returns an error.
 */
-(ZoomSDKError)cancelEmojiFeedback;

@end

NS_ASSUME_NONNULL_END
