

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZoomSDKSignInterpretationLanguageInfo : NSObject
/**
 @brief Get the sign language id.
 */
@property (copy,nonatomic,readonly) NSString *signLanguageID;
/**
 @brief Get the sign language name.
 */
@property (copy,nonatomic,readonly) NSString *signLanguageName;
@end

@interface ZoomSDKSignInterpreter : NSObject
/**
 @brief Get the user ID.
 */
@property (assign,nonatomic,readonly) unsigned int userID;
/**
 @brief Get the language id of the sign interpreter support.
 */
@property (copy,nonatomic,readonly) NSString *signLanguageID;

/**
 @brief Determine if sign interpreter is available.
 */
@property (assign,nonatomic,readonly) BOOL isAvailable;
@end

/**
 @brief Meeting sign interpretation callback event.
 */
@protocol ZoomSDKSignInterpretationControllerDelegate <NSObject>
@optional

/**
 @brief Sign interpretation staus change callback. This function is used to inform the user sign interpretation has been started or stopped, and all users in the meeting can get the event.
 @param status Specify current sign interpretation status.
 */
-(void)onSignInterpretationStatusChanged:(ZoomSDKSignInterpretationStatus)status;

/**
 @brief Sign interpreter list changed callback. When an interpreter leaves the meeting, preset interpreter joins the meeting, or the host adds or removes an interpreter, this will be triggered. Only the host can get the event.
 */
-(void)onSignInterpreterListChanged;

/**
 @brief Interpreters role changed callback. when myself role changed(participant <-> interpreter), and only myself in meeting can get the event.

 */
-(void)onSignInterpreterRoleChanged;

/**
 @brief Sign interpreter languages changed callback. when a sign interpreter's languages changed, and only the sign interpreter self can get the event.
 */
-(void)onSignInterpreterLanguageChanged;

/**
 @brief Available sign languages changed callback. When the available sign languages in a meeting change, all users in the meeting can get the event.
 @param availableSignLanguageList List the available sign languages.For more details, see {@link ZoomSDKSignInterpretationLanguageInfo} object.
 */
-(void)onAvailableSignLanguageListUpdated:(NSArray<ZoomSDKSignInterpretationLanguageInfo *> *)availableSignLanguageList;

/**
 @brief Callback event of the requirement to unmute the audio.
 */
-(void)onRequestSignInterpreterToTalk;

/**
 @brief Callback event for the user talk privilege changed. When the interpreter role changed, host changed, host allow or disallow interpreter talk, this will be triggered, and only the sign interpreter itself can get the event.
 @param hasPrivilege Specify whether the user has talk privilege or not.
 */
-(void)onTalkPrivilegeChanged:(BOOL)hasPrivilege;

/**
 @brief Callback event for the host to disallow the sign interpreter to talk.
 */
-(void)onDisallowSignInterpreterToTalk DEPRECATED_MSG_ATTRIBUTE("Use -onTalkPrivilegeChanged: instead");
@end

@interface ZoomSDKSignInterpretationController : NSObject
@property(nonatomic,assign)id<ZoomSDKSignInterpretationControllerDelegate>  delegate;

/**
 @brief Determine if the sign interpretation function is enabled.
 @return YES means sign interpretation function is enabled, otherwise it returns NO.
 */
-(BOOL)isSignInterpretationEnabled;

/**
 @brief Get the sign interpretation status of current meeting.
 @return If the function succeeds, the return value is the current meeting’s sign interpretation status.For more details, see {@link ZoomSDKSignInterpretationStatus}.
 */
-(ZoomSDKSignInterpretationStatus)getSignInterpretationStatus;

/**
 @brief Determine if myself is interpreter.
 @return YES means self is sign language interpreter, otherwise not.
 */
-(BOOL)isSignInterpreter;

/**
 @brief Get the sign language object of the specified sign language ID.
 @param signLanguageID Specify the sign language ID for which you want to get the information.
 @return If the function succeeds, the return value is ZoomSDKSignInterpretationLanguageInfo object.
 */
-(ZoomSDKSignInterpretationLanguageInfo *)getSignInterpretationLanguageInfoByID:(NSString *)signLanguageID;

/**
 @brief Get the available sign interpretation language list.
 @return If the function succeeds, the return array contain available language object.
 */
-(NSArray<ZoomSDKSignInterpretationLanguageInfo *> *)getAvailableSignLanguageInfoList;

/**
 @brief Get all supported sign interpretation language list.only for host.
 @return If the function succeeds, the return array contain support language object.
 */
-(NSArray<ZoomSDKSignInterpretationLanguageInfo *> *)getAllSupportedSignLanguageInfoList;

/**
 @brief Get the sign interpreters list.
 @return If the function succeeds, the return array contain sign interpreter object.
 */
-(NSArray<ZoomSDKSignInterpreter *> *)getSignInterpreterList;

/**
 @brief Add someone as a sign interpreter.
 @param userID The user’s ID.
 @param signLanguageId The sign language ID.
 @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.To get extended error information, see {@link ZoomSDKError}.
 */
-(ZoomSDKError)addSignInterpreter:(unsigned int)userID signLanguageId:(NSString *)signLanguageId;

/**
 @brief Remove someone from the list of sign interpreters.
 @param userID Specify the user.
 @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.To get extended error information, see {@link ZoomSDKError}.
 */
-(ZoomSDKError)removeSignInterpreter:(unsigned int)userID;

/**
 @brief Modify the language of some sign interpreter.
 @param userID The unique identity of the user.
 @param signLanguageId The id of sign language.
 @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.To get extended error information, see {@link ZoomSDKError}.
 */
-(ZoomSDKError)modifySignInterpreter:(unsigned int)userID signLanguageId:(NSString *)signLanguageId;

/**
 @brief Determine if I can start the sign interpretation in the meeting.
 */
-(BOOL)canStartSignInterpretation;

/**
 @brief Start sign interpretation.
 @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.To get extended error information, see {@link ZoomSDKError}.
 */
-(ZoomSDKError)startSignInterpretation;

/**
 @brief Stop sign interppretation.
 @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.To get extended error information, see {@link ZoomSDKError}.
 */
-(ZoomSDKError)stopSignInterpretation;

/**
 @brief Host allow sign language interpreter to talk.
 @param userID The user’s ID.
 @param allowToTalk YES indicates allow to talk, otherwise false.
 @return If the function succeeds, it will return ZoomSDKError_Success. Otherwise failed.To get extended error information, see {@link ZoomSDKError}.
 */
-(ZoomSDKError)requestSignLanuageInterpreterToTalk:(unsigned int)userID allowToTalk:(BOOL)allowToTalk;

/**
 @brief Determine if the sign language interpreter be allowed to talk.
 @param userID The unique identity of the user.
 @return YES indicates to allow to talk, otherwise not.
 */
-(BOOL)canSignLanguageInterpreterTalk:(unsigned int)userID;

/**
 @brief Get sign language id if myself is a sign interpreter.Only for interpreter.
 @return If the function succeeds, the return value is the current assigned sign language id, otherwise not.
 */
-(NSString *)getSignInterpreterAssignedLanID;

/**
 @brief Join a sign language channel if myself is not a sign interpreter.
 @param signLanguageId Specify the sign language channel ID.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
-(ZoomSDKError)joinSignLanguageChannel:(NSString *)signLanguageId;

/**
 @brief Off sign language if myself is not a sign interpreter.Only for non-interpreter.Available only for customized ui.
 @return If the function succeeds, it will return ZoomSDKError_Success, otherwise not.
 */
-(ZoomSDKError)leaveSignLanguageChannel;
@end

NS_ASSUME_NONNULL_END
