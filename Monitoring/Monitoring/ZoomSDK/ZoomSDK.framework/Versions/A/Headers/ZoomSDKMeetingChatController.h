//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@class ZoomSDKChatInfo;
NS_ASSUME_NONNULL_BEGIN
@interface ZoomSDKRichTextStyleOffset : NSObject
/**
 * @brief Get a certain rich-text style’s start position.
 */
@property(nonatomic,assign,readonly)unsigned int  positionStart;
/**
 * @brief Get the end position of a certain style in rich text.
 */
@property(nonatomic,assign,readonly)unsigned int  positionEnd;
/**
 * @brief Get a certain rich-text style supplementary information.
 * @note If the style is TextStyle_FontSize, possible return values are FontSize_Small, FontSize_Medium, or FontSize_Large. If style is TextStyle_Paragraph, possible return values are Paragraph_H1, Paragraph_H2, or Paragraph_H3. If the style is TextStyle_FontColor, or TextStyle_BackgroundColor, possible return values are hex string representing standard RGB data.
 */
@property(nonatomic,copy,readonly)NSString* reserve;
@end

@interface ZoomSDKRichTextStyleItem : NSObject
/**
 * @brief Get the rich text type of a portion of the current message.
 */
@property(nonatomic,assign,readonly)ZoomSDKRichTextStyle textStyle;
/**
 * @brief Get the current message’s rich text position info list of a certain style.
 * @return If the function succeeds, the return value is the current message’s rich text position info list of a certain style.
 */
-(NSArray<ZoomSDKRichTextStyleOffset *> *)getTextStyleOffsetList;
@end

@interface ZoomSDKChatMsgInfoBuilder : NSObject
/**
 * @brief Set chat message content.
 * @param content The chat message’s content.
 * @return If the function succeeds, it will return object which ZoomSDKChatMessageBuilder.
 */
-(ZoomSDKChatMsgInfoBuilder*)setContent:(NSString*)content;
/**
 * @brief Set  who will receive the chat message.
 * @param receiver Specify the user ID to receive the chat message. The message is sent to all participants when the value is zero(0).
 * @return If the function succeeds, it will return object which ZoomSDKChatMessageBuilder.
 */
-(ZoomSDKChatMsgInfoBuilder*)setReceiver:(unsigned int)receiver;
/**
 * @brief Set  the ID of the thread where the message will be posted.
 * @param threadId  Specify the thread ID.
 * @return If the function succeeds, it will return object which ZoomSDKChatMessageBuilder.
 */
-(ZoomSDKChatMsgInfoBuilder*)setThreadId:(NSString*)threadId;
/**
 * @brief Set the chat message type.
 * @param type The chat message’s type.
 * @return If the function succeeds, it will return object which ZoomSDKChatMessageBuilder.
 */
-(ZoomSDKChatMsgInfoBuilder*)setMessageType:(ZoomSDKChatMessageType)type;
/**
 * @brief Set the chat message content quote style and position.
 * @param positionStart The segment start position.
 * @param positionEnd  The segment end position.
 * @return If the function succeeds, it will return object which ZoomSDKChatMessageBuilder.
 */
-(ZoomSDKChatMsgInfoBuilder*)setQuotePosition:(unsigned int)positionStart positionEnd:(unsigned int)positionEnd;
/**
 * @brief Build chat message entity.
 * @return If the function succeeds, the return value is message detail info.
 */
-(ZoomSDKChatInfo*)build;
@end

@protocol ZoomSDKMeetingChatControllerDelegate <NSObject>
/**
 * @brief In-meeting users receive the notification of chat messages.
 * @param chatInfo Chat information received by user.
 */
- (void)onChatMessageNotification:(ZoomSDKChatInfo*)chatInfo;
@end

@interface ZoomSDKMeetingChatController : NSObject

@property(nonatomic,assign) id<ZoomSDKMeetingChatControllerDelegate> delegate;
/**
 * @brief Get chat message by message ID.
 * @param messageID The message ID.
 * @return If the function succeeds, it will return object which ZoomSDKChatInfo.
 */
-(ZoomSDKChatInfo*)getChatMessageById:(NSString *)messageID;

/**
 * @brief Send a chat message.
 * @param message The message info.
 * @return If the function succeeds, it will return ZoomSDKError_Success.
 */
-(ZoomSDKError)sendChatMsgTo:(ZoomSDKChatInfo*)message;
@end

NS_ASSUME_NONNULL_END
