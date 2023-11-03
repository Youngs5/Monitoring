

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

/**
 @brief Live transcription message interface.
 */
@interface ZoomSDKLiveTranscriptionMessageInfo : NSObject
/**
 @brief Get the message ID of the current message.
 */
@property (nonatomic, copy, readonly) NSString *messageID;

/**
 @brief Get the speaker's ID.
 */
@property (nonatomic, assign, readonly) unsigned int speakerID;

/**
 @brief Get the speaker's name.
 */
@property (nonatomic, copy, readonly) NSString *speakerName;

/**
 @brief Get the content of the current message.
 */
@property (nonatomic, copy, readonly) NSString *messageContent;

/**
 @brief Get the time stamp of the current message.
 */
@property (nonatomic, assign, readonly) time_t timeStamp;

/**
 @brief Get the type of the current message.
 */
@property (nonatomic, assign, readonly) ZoomSDKLiveTranscriptionOperationType messageType;

@end


@interface ZoomSDKLiveTranscriptionLanguage : NSObject
@property(nonatomic, assign, readonly) int languageID;
@property(nonatomic, copy, readonly) NSString* languageName;
@end


@protocol ZoomSDKCloseCaptionControllerDelegate <NSObject>
@optional

/**
 * @brief Callback of getting the privilege of close caption. 
 */
- (void)onGetCCPrvilege;

/**
 * @brief Callback of losing privilege of close caption. 
 */
- (void)onLostCCPrvilege;

/**
 * @brief Notify the current user that close caption is received.
 * @param inString The content of the close caption message.
 * @param senderID The sender id of a closed caption message.
 * @note If the meeting supports multi- language transcription and the host sets manual captions to true, attendees must set the translation language id to -1 to receive closed captioned messages.
 */
- (void)onReceiveCCMessageWithString:(NSString*)inString senderID:(unsigned int)senderID;

/**
 * @brief Notify the current user of realtime message.
 * @param realtimeMessage The message that is being input.
 */
- (void)onReceiveCCRealtimeMessage:(NSString *)realtimeMessage;

/**
 * @brief Notify the live transcription status changed.
 * @param status The type of live transcription status.
 */
- (void)onLiveTranscriptionStatus:(ZoomSDKLiveTranscriptionStaus)status;

/**
 * @brief Notify the live transcription message received.
 * @param msgContent The content of message.
 * @param type The type of live transcription operation.
 * @param speakerID The id of live transcription spaker.
 */
- (void)onLiveTranscriptionMsgReceived:(NSString*)msgContent type:(ZoomSDKLiveTranscriptionOperationType)type speakerID:(unsigned int)speakerID DEPRECATED_MSG_ATTRIBUTE("Use -onLiveTranscriptionMsgInfoReceived: instead");

/**
 @brief Callback: Invoked when a live transcription message is received.
 @param messageInfo The live transcription message, refer to {@link ZoomSDKLiveTranscriptionMessageInfo}.
 */
- (void)onLiveTranscriptionMsgInfoReceived:(ZoomSDKLiveTranscriptionMessageInfo*)messageInfo;

/**
 @brief Callback: Original language message received callback.
 @param messageInfo messageInfo The spoken language message, refer to {@link ZoomSDKLiveTranscriptionMessageInfo}.
 */
- (void)onOriginalLanguageMsgReceived:(ZoomSDKLiveTranscriptionMessageInfo*)messageInfo;

/**
 * @brief The translation message error callback.
 * @param spokenLanguage An object of the spoken message language.
 * @param transcriptLanguage An object of the message language you want to translate.
 */
- (void)onLiveTranscriptionMsgError:(ZoomSDKLiveTranscriptionLanguage*)spokenLanguage transcriptLanguage:(ZoomSDKLiveTranscriptionLanguage*)transcriptLanguage;

/**
 * @brief Notify the request for live transcript received.
 * @param requesterID The user id of requester.
 * @param bAnonymous Request anonymously of not, if bAnonymous is YES, requesterID has no meanings.
 * @note only host can retrieve this callback
 */
- (void)onRequestForLiveTranscriptReceived:(unsigned int)requesterID anonymous:(BOOL)bAnonymous;

/**
 * @brief Notify the request for live transcript status changed.
 * @param bEnabled YES means enabled, otherwise not.
 */
- (void)onRequestLiveTransciptionStatusChange:(BOOL)bEnabled;

/**
 * @brief Sink the event of captions enabled status changed.
 * @param enable YES means the host enables the captions, otherwise means the host disables the captions.
 */
- (void)onCaptionStatusChanged:(BOOL)enable;
@end

@interface ZoomSDKCloseCaptionController : NSObject
{
    id<ZoomSDKCloseCaptionControllerDelegate> _delegate;
    
}
@property(nonatomic, assign)id<ZoomSDKCloseCaptionControllerDelegate> delegate;

/**
 * @brief Query if Close Caption is supported in the current meeting.
 * @return YES means supported, otherwise not.
 */
- (BOOL)isMeetingSupportCloseCaption;

/**
 * @brief Query if it is able to assign others to send Close Caption.
 * @return YES means able, otherwise not.
 */
- (BOOL)canAssignOthersToSendCC;

/**
 * @brief Query if the specified user can be assigned to send close caption.
 * @param userID The ID of user who you want to assign to send close caption
 * @return YES means able, otherwise not.
 */
- (BOOL)canBeAssignedToSendCC:(unsigned int)userID;

/**
 * @brief Query if the current user can send Close Caption.
 * @return YES means able, otherwise not.
 */
- (BOOL)canSendClosedCaption;

/**
 * @brief Query if user can save Close Caption.
 * @return YES means able, otherwise not.
 */
- (BOOL)isCanSaveClosedCaption;

/**
 * @brief Query if the third party close caption server is available.
 * @return YES means available, otherwise not.
 */
- (BOOL)is3rdPartCCServerAvailable;

/**
 * @brief This method is used for host to withdraw CC privilege from another user.
 * @param userID The ID of user that you want to withdraw CC privilege.
 * @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.
 */
- (ZoomSDKError)withdrawCCPriviledgeForUser:(unsigned int)userID;

/**
 * @brief This method is used for host to assign CC privilege to another user.
 * @param userID The ID of user whom you want to assign CC privilege to.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise failed.
 */
- (ZoomSDKError)assignCCPriviledgeTo:(unsigned int)userID;

/**
 * @brief Send CC message.
 * @param ccString The content of CC.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise failed.
 */
- (ZoomSDKError)sendClosedCaptionMessage:(NSString*)ccString;

/**
 * @brief Save CC.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise failed.
 */
- (ZoomSDKError)saveCCHistory;

/**
 * @brief Get the path where the CC is saved.
 * @return If the function succeeds, it will return a NSString, otherwise failed.
 */
- (NSString*)getClosedCaptionHistorySavedPath;

/**
 * @brief Get the third party URL which is used to input CC.
 * @param thirdPartyURL The URL of the third party service.
 * @return If the function succeeds, it will return ZoomSDKError_Success, otherwise failed.
 */
- (ZoomSDKError)getClosedCaptionUrlFor3rdParty:(NSString**)thirdPartyURL;

/**
 @brief Determine whether the legal notice for Live transcript is available.
 @return YES indicates the legal notice for Live transcript is available., otherwise not.
 */
- (BOOL)isLiveTranscriptLegalNoticeAvailable;

/**
 @brief Get the CC legal notices prompt.
 @return If the function succeeds, it will return the CC legal notices prompt, otherwise nil.
 */
- (NSString *)getLiveTranscriptLegalNoticesPrompt;

/**
 @brief Get the CC legal notices explained.
 @return If the function succeeds, it will return the CC legal notices explained, otherwise nil.
 */
- (NSString *)getLiveTranscriptLegalNoticesExplained;

/**
 @brief Determine whether the live transcription feature is enabled.
 @return YES means enabled, otherwise not.
 */
- (BOOL)isLiveTranscriptionFeatureEnabled;

/**
 @brief Determine whether the multi-language transcription feature is enabled.
 @return YES means enabled, otherwise not.
 */
- (BOOL)isMultiLanguageTranscriptionEnabled;

/**
 @brief Determine whether the translated captions feature is enabled.
 @return YES means enabled, otherwise not.
 */
- (BOOL)isTextLiveTranslationEnabled;

/**
 @brief Query the status of live transcription.
 @return If the function succeeds, it will return the status of live transcription with type ZoomSDKLiveTranscriptionStaus.
 */
- (ZoomSDKLiveTranscriptionStaus)getLiveTranscriptionStatus;

/**
 @brief Query if it is able to start live transcription.
 @return ZoomSDKError_Success means able, otherwise not.
 */
- (ZoomSDKError)canStartLiveTranscription;

/**
 @brief Start live transcription.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 @note If the meeting allows multi- language transcription, all users can start live transcription. Otherwise, only the host can start it.
 */
- (ZoomSDKError)startLiveTranscription;

/**
 @brief Stop live transcription.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 @note If the meeting allows multi- language transcription, all users can stop live transcription. Otherwise only the host can stop it.
 */
- (ZoomSDKError)stopLiveTranscription;

/**
 @brief Enable or disable the ability for attendees to request live transcriptions.
 @param bEnable YES means enable, otherwise not.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 @note If the meeting allows multi- language transcription, the return value is ZoomSDKError_WrongUsage.
 */
- (ZoomSDKError)enableRequestLiveTranscription:(BOOL)bEnable;

/**
 @brief Determine whether the request to start live transcription is enabled.
 @return ZoomSDKError_Success means enabled, otherwise not.
 @note If the meeting allows multi-language transcription, the return value is ZoomSDKError_WrongUsage.
 */
- (ZoomSDKError)isRequestToStartLiveTranscriptionEnabled;

/**
 @brief Request the host to start ive transcription.
 @param bAnonymous YES indicates the user anonymous request.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 @note If the meeting allows multi-language transcription, the return value is ZoomSDKError_WrongUsage.
 */
- (ZoomSDKError)requestToStartLiveTranscription:(BOOL)bAnonymous;

/**
 @brief Enable or disable manual captions for the meeting.
 @param bEnable YES means enable, otherwise not.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
- (ZoomSDKError)enableMeetingManualCaption:(BOOL)bEnable;

/**
 @brief Determine whether manually added closed captions is enabled for the meeting.
 @return YES means enabled, otherwise not.
 */
- (BOOL)isMeetingManualCaptionEnabled;

/**
 @brief Get the list of all available spoken languages in a meeting.
 @return If the function succeeds, it will return an array contains the available spoken languages in a meeting, otherwise nil.
 */
- (NSArray<ZoomSDKLiveTranscriptionLanguage*>*)getAvailableMeetingSpokenLanguages;

/**
 @brief Set the spoken language of the current user.
 @param languageID The spoken language id.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
- (ZoomSDKError)setMeetingSpokenLanguage:(int)languageID;

/**
 @brief Get the spoken language of the current user.
 @return If the function succeeds, it will an object of ZoomSDKLiveTranscriptionLanguage, otherwise nil.
 */
- (ZoomSDKLiveTranscriptionLanguage*)getMeetingSpokenLanguage;

/**
 @brief Get the list of all available translation languages in a meeting.
 @return If the function succeeds, it will return an array contains all available translation languages in a meeting, otherwise nil.
 */
- (NSArray<ZoomSDKLiveTranscriptionLanguage*>*)getAvailableTranslationLanguages;

/**
 @brief Set the translation language of the current user.
 @param languageID The translation language id. If the language ID is set to -1, live translation will be disabled. You can reveive closed captions if the  host sets manual captions to true for the meeting.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
- (ZoomSDKError)setTranslationLanguage:(int)languageID;

/**
 @brief Get the translation language of the current user.
 @return If the function succeeds, it will an object of ZoomSDKLiveTranscriptionLanguage, otherwise nil.
 */
- (ZoomSDKLiveTranscriptionLanguage*)getTranslationLanguage;

/**
 @brief Enable or disable to receive original and translated content.If enable this feature,you need start live transcription.
 @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise not.
 */
- (ZoomSDKError)enableReceiveSpokenLanguageContent:(BOOL)enable;

/**
 @brief Determine whether receive original and translated is available.
 @return YES indicates receive original and translated is available. Otherwise NO.
 */
- (BOOL)isReceiveSpokenLanguageContentEnabled;

/**
 @brief Query if the user can disable captions.
 @return YES means that the host can disable captions.
 */
- (BOOL)canDisableCaptions;

/**
 @brief Enable or disable captions.
 @param enable YES means that captions are enabled; NO means that captions are disabled.
 @return If the function succeeds, the return value is ZoomSDKError_Success. Otherwise the function returns an error.
 */
- (ZoomSDKError)enableCaptions:(BOOL)enable;

/**
 @brief Query if the captions enabled.
 @return YES means that captions are enabled.
 */
- (BOOL)isCaptionsEnabled;
@end
