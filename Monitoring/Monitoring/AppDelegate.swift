//
//  AppDelegate.swift
//  Monitoring
//
//  Created by 오영석 on 11/2/23.
//

import Cocoa
import ZoomSDK

@main
class AppDelegate: NSObject, NSApplicationDelegate {
    var window: NSWindow!

    func applicationDidFinishLaunching(_ aNotification: Notification) {
        let contentViewController = MainViewController()
        window = NSWindow(contentViewController: contentViewController)
        window.title = "Monitoring System"
        window.setContentSize(NSSize(width: 800, height: 600))
        window.center()
        window.makeKeyAndOrderFront(nil)
        
        // Zoom SDK 초기화
        let zoomSDK = MobileRTCSDKInitContext()
        zoomSDK.domain = "zoom.us" // Zoom 도메인
        zoomSDK.enableLog = true // 필요에 따라 로그를 활성화할 수 있습니다.
        let sdkInitialized = MobileRTC.shared().initialize(zoomSDK)

        if sdkInitialized {
            print("Zoom SDK 초기화 성공")
        } else {
            print("Zoom SDK 초기화 실패")
        }
    }

    func applicationWillTerminate(_ aNotification: Notification) {
    }
}

